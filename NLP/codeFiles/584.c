#include &lt;sys/types.h&gt;#include &lt;err.h&gt;
#include &lt;errno.h&gt;
#include &lt;fnmatch.h&gt;
#include &lt;fts.h&gt;
#include &lt;string.h&gt;
#include &lt;stdio.h&gt;

/* Compare files by name. */
int
entcmp(const FTSENT **a, const FTSENT **b)
{
	return strcmp((*a)-&gt;fts_name, (*b)-&gt;fts_name);
}

/*
 * Print all files in the directory tree that match the glob pattern.
 * Example: pmatch(&quot;/usr/src&quot;, &quot;*.c&quot;);
 */
void
pmatch(char *dir, const char *pattern)
{
	FTS *tree;
	FTSENT *f;
	char *argv[] = { dir, NULL };

	/*
	 * FTS_LOGICAL follows symbolic links, including links to other
	 * directories. It detects cycles, so we never have an infinite
	 * loop. FTS_NOSTAT is because we never use f-&gt;statp. It uses
	 * our entcmp() to sort files by name.
	 */
	tree = fts_open(argv, FTS_LOGICAL | FTS_NOSTAT, entcmp);
	if (tree == NULL)
		err(1, &quot;fts_open&quot;);

	/*
	 * Iterate files in tree. This iteration always skips
	 * &quot;.&quot; and &quot;..&quot; because we never use FTS_SEEDOT.
	 */
	while ((f = fts_read(tree))) {
		switch (f-&gt;fts_info) {
		case FTS_DNR:	/* Cannot read directory */
		case FTS_ERR:	/* Miscellaneous error */
		case FTS_NS:	/* stat() error */
			/* Show error, then continue to next files. */
			warn(&quot;%s&quot;, f-&gt;fts_path);
			continue;
		case FTS_DP:
			/* Ignore post-order visit to directory. */
			continue;
		}

		/*
		 * Check if name matches pattern. If so, then print
		 * path. This check uses FNM_PERIOD, so &quot;*.c&quot; will not
		 * match &quot;.invisible.c&quot;.
		 */
		if (fnmatch(pattern, f-&gt;fts_name, FNM_PERIOD) == 0)
			puts(f-&gt;fts_path);

		/*
		 * A cycle happens when a symbolic link (or perhaps a
		 * hard link) puts a directory inside itself. Tell user
		 * when this happens.
		 */
		if (f-&gt;fts_info == FTS_DC)
			warnx(&quot;%s: cycle in directory tree&quot;, f-&gt;fts_path);
	}

	/* fts_read() sets errno = 0 unless it has error. */
	if (errno != 0)
		err(1, &quot;fts_read&quot;);

	if (fts_close(tree) &lt; 0)
		err(1, &quot;fts_close&quot;);
}

int
main()
{
	pmatch(&quot;.&quot;, &quot;*.c&quot;);
	return 0;
}
