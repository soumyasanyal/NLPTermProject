#include &lt;unistd.h&gt;#include &lt;fcntl.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;

/* we just return a yes/no status; caller can check errno */
int copy_file(char *in, char *out)
{
	int ret = 0;
	int fin, fout;
	ssize_t len;
	char *buf[4096]; /* buffer size, some multiple of block size preferred */
	struct stat st;

	if ((fin  = open(in,  O_RDONLY)) == -1) return 0;
	if (fstat(fin, &amp;st)) goto bail;

	/* open output with same permission */
	fout = open(out, O_WRONLY|O_CREAT|O_TRUNC, st.st_mode &amp; 0777);
	if (fout == -1) goto bail;

	while ((len = read(fin, buf, 4096)) &gt; 0)
		write(fout, buf, len);

	ret = len ? 0 : 1; /* last read should be 0 */

bail:	if (fin != -1)  close(fin);
	if (fout != -1) close(fout);
	return ret;
}

int main()
{
	copy_file(&quot;infile&quot;, &quot;outfile&quot;);
	return 0;
}
