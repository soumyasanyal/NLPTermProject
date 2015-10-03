#include &lt;fcntl.h&gt;	/* fcntl, open */#include &lt;stdlib.h&gt;	/* atexit, getenv, malloc */
#include &lt;stdio.h&gt;	/* fputs, printf, puts, snprintf */
#include &lt;string.h&gt;	/* memcpy */
#include &lt;unistd.h&gt;	/* sleep, unlink */

/* Filename for only_one_instance() lock. */
#define INSTANCE_LOCK &quot;rosetta-code-lock&quot;

void
fail(const char *message)
{
	perror(message);
	exit(1);
}

/* Path to only_one_instance() lock. */
static char *ooi_path;

void
ooi_unlink(void)
{
	unlink(ooi_path);
}

/* Exit if another instance of this program is running. */
void
only_one_instance(void)
{
	struct flock fl;
	size_t dirlen;
	int fd;
	char *dir;

	/*
	 * Place the lock in the home directory of this user;
	 * therefore we only check for other instances by the same
	 * user (and the user can trick us by changing HOME).
	 */
	dir = getenv(&quot;HOME&quot;);
	if (dir == NULL || dir[0] != '/') {
		fputs(&quot;Bad home directory.\n&quot;, stderr);
		exit(1);
	}
	dirlen = strlen(dir);

	ooi_path = malloc(dirlen + sizeof(&quot;/&quot; INSTANCE_LOCK));
	if (ooi_path == NULL)
		fail(&quot;malloc&quot;);
	memcpy(ooi_path, dir, dirlen);
	memcpy(ooi_path + dirlen, &quot;/&quot; INSTANCE_LOCK,
	    sizeof(&quot;/&quot; INSTANCE_LOCK));  /* copies '\0' */

	fd = open(ooi_path, O_RDWR | O_CREAT, 0600);
	if (fd &lt; 0)
		fail(ooi_path);

	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	if (fcntl(fd, F_SETLK, &amp;fl) &lt; 0) {
		fputs(&quot;Another instance of this program is running.\n&quot;,
		    stderr);
		exit(1);
	}

	/*
	 * Run unlink(ooi_path) when the program exits. The program
	 * always releases locks when it exits.
	 */
	atexit(ooi_unlink);
}

/*
 * Demo for Rosetta Code.
 * http://rosettacode.org/wiki/Determine_if_only_one_instance_is_running
 */
int
main()
{
	int i;

	only_one_instance();

	/* Play for 10 seconds. */
	for(i = 10; i &gt; 0; i--) {
		printf(&quot;%d...%s&quot;, i, i % 5 == 1 ? &quot;\n&quot; : &quot; &quot;);
		fflush(stdout);
		sleep(1);
	}
	puts(&quot;Fin!&quot;);
	return 0;
}
