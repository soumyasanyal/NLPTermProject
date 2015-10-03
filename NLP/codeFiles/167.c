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

int
setmodtime(const wchar_t *path)
{
	FILETIME modtime;
	SYSTEMTIME st;
	HANDLE fh;
	wchar_t date[80], time[80];

	fh = CreateFileW(path, GENERIC_READ | FILE_WRITE_ATTRIBUTES,
	    0, NULL, OPEN_EXISTING, 0, NULL);
	if (fh == INVALID_HANDLE_VALUE) {
		oops(path);
		return 1;
	}

	/*
	 * Use GetFileTime() to get the file modification time.
	 */
	if (GetFileTime(fh, NULL, NULL, &amp;modtime) == 0)
		goto fail;
	FileTimeToSystemTime(&amp;modtime, &amp;st);
	if (GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, &amp;st, NULL,
	    date, sizeof date / sizeof date[0]) == 0 ||
	    GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &amp;st, NULL,
	    time, sizeof time / sizeof time[0]) == 0)
		goto fail;
	wprintf(L&quot;%ls: Last modified at %s at %s (UTC).\n&quot;,
	    path, date, time);

	/*
	 * Use SetFileTime() to change the file modification time
	 * to the current time.
	 */
	GetSystemTime(&amp;st);
	if (GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, &amp;st, NULL,
	    date, sizeof date / sizeof date[0]) == 0 ||
	    GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &amp;st, NULL,
	    time, sizeof time / sizeof time[0]) == 0)
		goto fail;
	SystemTimeToFileTime(&amp;st, &amp;modtime);
	if (SetFileTime(fh, NULL, NULL, &amp;modtime) == 0)
		goto fail;
	wprintf(L&quot;%ls: Changed to %s at %s (UTC).\n&quot;, path, date, time);

	CloseHandle(fh);
	return 0;

fail:
	oops(path);
	CloseHandle(fh);
	return 1;
}

/*
 * Show the file modification time, and change it to the current time.
 */
int
main()
{
	int argc, i, r;
	wchar_t **argv;

	/* MinGW never provides wmain(argc, argv). */
	argv = CommandLineToArgvW(GetCommandLineW(), &amp;argc);
	if (argv == NULL) {
		oops(L&quot;CommandLineToArgvW&quot;);
		exit(1);
	}

	if (argc &lt; 2) {
		fwprintf(stderr, L&quot;usage: %ls file...\n&quot;, argv[0]);
		exit(1);
	}

	r = 0;
	for (i = 1; argv[i] != NULL; i++)
		if (setmodtime(argv[i])) r = 1;
	return r;
}
