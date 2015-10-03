#include &lt;sys/types.h&gt;#include &lt;sys/stat.h&gt;
#include &lt;unistd.h&gt;
#include &lt;dirent.h&gt;
#include &lt;regex.h&gt;
#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;errno.h&gt;
#include &lt;err.h&gt;

enum {
	WALK_OK = 0,
	WALK_BADPATTERN,
	WALK_NAMETOOLONG,
	WALK_BADIO,
};

#define WS_NONE		0
#define WS_RECURSIVE	(1 &lt;&lt; 0)
#define WS_DEFAULT	WS_RECURSIVE
#define WS_FOLLOWLINK	(1 &lt;&lt; 1)	/* follow symlinks */
#define WS_DOTFILES	(1 &lt;&lt; 2)	/* per unix convention, .file is hidden */
#define WS_MATCHDIRS	(1 &lt;&lt; 3)	/* if pattern is used on dir names too */

int walk_recur(char *dname, regex_t *reg, int spec)
{
	struct dirent *dent;
	DIR *dir;
	struct stat st;
	char fn[FILENAME_MAX];
	int res = WALK_OK;
	int len = strlen(dname);
	if (len &gt;= FILENAME_MAX - 1)
		return WALK_NAMETOOLONG;

	strcpy(fn, dname);
	fn[len++] = '/';

	if (!(dir = opendir(dname))) {
		warn(&quot;can't open %s&quot;, dname);
		return WALK_BADIO;
	}

	errno = 0;
	while ((dent = readdir(dir))) {
		if (!(spec &amp; WS_DOTFILES) &amp;&amp; dent-&gt;d_name[0] == '.')
			continue;
		if (!strcmp(dent-&gt;d_name, &quot;.&quot;) || !strcmp(dent-&gt;d_name, &quot;..&quot;))
			continue;

		strncpy(fn + len, dent-&gt;d_name, FILENAME_MAX - len);
		if (lstat(fn, &amp;st) == -1) {
			warn(&quot;Can't stat %s&quot;, fn);
			res = WALK_BADIO;
			continue;
		}

		/* don't follow symlink unless told so */
		if (S_ISLNK(st.st_mode) &amp;&amp; !(spec &amp; WS_FOLLOWLINK))
			continue;

		/* will be false for symlinked dirs */
		if (S_ISDIR(st.st_mode)) {
			/* recursively follow dirs */
			if ((spec &amp; WS_RECURSIVE))
				walk_recur(fn, reg, spec);

			if (!(spec &amp; WS_MATCHDIRS)) continue;
		}

		/* pattern match */
		if (!regexec(reg, fn, 0, 0, 0)) puts(fn);
	}

	if (dir) closedir(dir);
	return res ? res : errno ? WALK_BADIO : WALK_OK;
}

int walk_dir(char *dname, char *pattern, int spec)
{
	regex_t r;
	int res;
	if (regcomp(&amp;r, pattern, REG_EXTENDED | REG_NOSUB))
		return WALK_BADPATTERN;
	res = walk_recur(dname, &amp;r, spec);
	regfree(&amp;r);

	return res;
}

int main()
{
	int r = walk_dir(&quot;.&quot;, &quot;.\\.c$&quot;, WS_DEFAULT|WS_MATCHDIRS);
	switch(r) {
	case WALK_OK:		break;
	case WALK_BADIO:	err(1, &quot;IO error&quot;);
	case WALK_BADPATTERN:	err(1, &quot;Bad pattern&quot;);
	case WALK_NAMETOOLONG:	err(1, &quot;Filename too long&quot;);
	default:
		err(1, &quot;Unknown error?&quot;);
	}
	return 0;
}
