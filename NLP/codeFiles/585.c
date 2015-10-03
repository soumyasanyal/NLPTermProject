#include &lt;windows.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;wchar.h&gt;

/* Print &quot;message: last Win32 error&quot; to stderr. */
void
oops(const wchar_t *message)
{
	wchar_t *buf;
	DWORD error;

	buf = NULL;
	error = GetLastError();
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL, error, 0, (wchar_t *)&amp;buf, 0, NULL);

	if (buf) {
		fwprintf(stderr, L&quot;%ls: %ls&quot;, message, buf);
		LocalFree(buf);
	} else {
		/* FormatMessageW failed. */
		fwprintf(stderr, L&quot;%ls: unknown error 0x%x\n&quot;,
		    message, error);
	}
}

/*
 * Print all files in a given directory tree that match a given wildcard
 * pattern.
 */
int
main()
{
	struct stack {
		wchar_t			*path;
		size_t			 pathlen;
		size_t			 slashlen;
		HANDLE			 ffh;
		WIN32_FIND_DATAW	 ffd;
		struct stack		*next;
	} *dir, dir0, *ndir;
	size_t patternlen;
	int argc;
	wchar_t **argv, *buf, c, *pattern;

	/* MinGW never provides wmain(argc, argv). */
	argv = CommandLineToArgvW(GetCommandLineW(), &amp;argc);
	if (argv == NULL) {
		oops(L&quot;CommandLineToArgvW&quot;);
		exit(1);
	}

	if (argc != 3) {
		fwprintf(stderr, L&quot;usage: %ls dir pattern\n&quot;, argv[0]);
		exit(1);
	}

	dir0.path = argv[1];
	dir0.pathlen = wcslen(dir0.path);
	pattern = argv[2];
	patternlen = wcslen(pattern);

	if (patternlen == 0 ||
	    wcscmp(pattern, L&quot;.&quot;) == 0 ||
	    wcscmp(pattern, L&quot;..&quot;) == 0 ||
	    wcschr(pattern, L'/') ||
	    wcschr(pattern, L'\\')) {
		fwprintf(stderr, L&quot;%ls: invalid pattern\n&quot;, pattern);
		exit(1);
	}

	/*
	 * Must put backslash between path and pattern, unless
	 * last character of path is slash or colon.
	 *
	 *   'dir' =&gt; 'dir\*'
	 *   'dir\' =&gt; 'dir\*'
	 *   'dir/' =&gt; 'dir/*'
	 *   'c:' =&gt; 'c:*'
	 *
	 * 'c:*' and 'c:\*' are different files!
	 */
	c = dir0.path[dir0.pathlen - 1];
	if (c == ':' || c == '/' || c == '\\')
		dir0.slashlen = dir0.pathlen;
	else
		dir0.slashlen = dir0.pathlen + 1;

	/* Allocate space for path + backslash + pattern + \0. */
	buf = calloc(dir0.slashlen + patternlen + 1, sizeof buf[0]);
	if (buf == NULL) {
		perror(&quot;calloc&quot;);
		exit(1);
	}
	dir0.path = wmemcpy(buf, dir0.path, dir0.pathlen + 1);

	dir0.ffh = INVALID_HANDLE_VALUE;
	dir0.next = NULL;
	dir = &amp;dir0;

	/* Loop for each directory in linked list. */
loop:
	while (dir) {
		/*
		 * At first visit to directory:
		 *   Print the matching files. Then, begin to find
		 *   subdirectories.
		 *
		 * At later visit:
		 *   dir-&gt;ffh is the handle to find subdirectories.
		 *   Continue to find them.
		 */
		if (dir-&gt;ffh == INVALID_HANDLE_VALUE) {
			/* Append backslash + pattern + \0 to path. */
			dir-&gt;path[dir-&gt;pathlen] = '\\';
			wmemcpy(dir-&gt;path + dir-&gt;slashlen,
			    pattern, patternlen + 1);

			/* Find all files to match pattern. */
			dir-&gt;ffh = FindFirstFileW(dir-&gt;path, &amp;dir-&gt;ffd);
			if (dir-&gt;ffh == INVALID_HANDLE_VALUE) {
				/* Check if no files match pattern. */
				if (GetLastError() == ERROR_FILE_NOT_FOUND)
					goto subdirs;

				/* Bail out from other errors. */
				dir-&gt;path[dir-&gt;pathlen] = '\0';
				oops(dir-&gt;path);
				goto popdir;
			}

			/* Remove pattern from path; keep backslash. */
			dir-&gt;path[dir-&gt;slashlen] = '\0';

			/* Print all files to match pattern. */
			do {
				wprintf(L&quot;%ls%ls\n&quot;,
				    dir-&gt;path, dir-&gt;ffd.cFileName);
			} while (FindNextFileW(dir-&gt;ffh, &amp;dir-&gt;ffd) != 0);
			if (GetLastError() != ERROR_NO_MORE_FILES) {
				dir-&gt;path[dir-&gt;pathlen] = '\0';
				oops(dir-&gt;path);
			}
			FindClose(dir-&gt;ffh);

subdirs:
			/* Append * + \0 to path. */
			dir-&gt;path[dir-&gt;slashlen] = '*';
			dir-&gt;path[dir-&gt;slashlen + 1] = '\0';

			/* Find first possible subdirectory. */
			dir-&gt;ffh = FindFirstFileExW(dir-&gt;path,
			    FindExInfoStandard, &amp;dir-&gt;ffd,
			    FindExSearchLimitToDirectories, NULL, 0);
			if (dir-&gt;ffh == INVALID_HANDLE_VALUE) {
				dir-&gt;path[dir-&gt;pathlen] = '\0';
				oops(dir-&gt;path);
				goto popdir;
			}
		} else {
			/* Find next possible subdirectory. */
			if (FindNextFileW(dir-&gt;ffh, &amp;dir-&gt;ffd) == 0)
				goto closeffh;				
		}

		/* Enter subdirectories. */
		do {
			const wchar_t *fn = dir-&gt;ffd.cFileName;
			const DWORD attr = dir-&gt;ffd.dwFileAttributes;
			size_t buflen, fnlen;

			/*
			 * Skip '.' and '..', because they are links to
			 * the current and parent directories, so they
			 * are not subdirectories.
			 *
			 * Skip any file that is not a directory.
			 *
			 * Skip all reparse points, because they might
			 * be symbolic links. They might form a cycle,
			 * with a directory inside itself.
			 */
			if (wcscmp(fn, L&quot;.&quot;) == 0 ||
			    wcscmp(fn, L&quot;..&quot;) == 0 ||
			    (attr &amp; FILE_ATTRIBUTE_DIRECTORY) == 0 ||
			    (attr &amp; FILE_ATTRIBUTE_REPARSE_POINT))
				continue;

			ndir = malloc(sizeof *ndir);
			if (ndir == NULL) {
				perror(&quot;malloc&quot;);
				exit(1);
			}

			/*
			 * Allocate space for path + backslash +
			 *     fn + backslash + pattern + \0.
			 */
			fnlen = wcslen(fn);
			buflen = dir-&gt;slashlen + fnlen + patternlen + 2;
			buf = calloc(buflen, sizeof buf[0]);
			if (buf == NULL) {
				perror(&quot;malloc&quot;);
				exit(1);
			}

			/* Copy path + backslash + fn + \0. */
			wmemcpy(buf, dir-&gt;path, dir-&gt;slashlen);
			wmemcpy(buf + dir-&gt;slashlen, fn, fnlen + 1);

			/* Push dir to list. Enter dir. */
			ndir-&gt;path = buf;
			ndir-&gt;pathlen = dir-&gt;slashlen + fnlen;
			ndir-&gt;slashlen = ndir-&gt;pathlen + 1;
			ndir-&gt;ffh = INVALID_HANDLE_VALUE;
			ndir-&gt;next = dir;
			dir = ndir;
			goto loop; /* Continue outer loop. */
		} while (FindNextFileW(dir-&gt;ffh, &amp;dir-&gt;ffd) != 0);
closeffh:
		if (GetLastError() != ERROR_NO_MORE_FILES) {
			dir-&gt;path[dir-&gt;pathlen] = '\0';
			oops(dir-&gt;path);
		}
		FindClose(dir-&gt;ffh);

popdir:
		/* Pop dir from list, free dir, but never free dir0. */
		free(dir-&gt;path);
		if (ndir = dir-&gt;next)
			free(dir);
		dir = ndir;
	}

	return 0;
}
