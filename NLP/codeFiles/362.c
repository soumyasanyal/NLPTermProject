#include &lt;stdio.h&gt;#include &lt;sys/mman.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;err.h&gt;
#include &lt;string.h&gt;

int ordered(char *s, char **end)
{
	int r = 1;
	while (*++s != '\n' &amp;&amp; *s != '\r' &amp;&amp; *s != '\0')
		if (s[0] &lt; s[-1]) r = 0;

	*end = s;
	return r;
}

int main()
{
	char *buf, *word, *end, *tail;
	struct stat st;
	int longest = 0, len, fd;

	if ((fd = open(&quot;unixdict.txt&quot;, O_RDONLY)) == -1) err(1, &quot;read error&quot;);

	fstat(fd, &amp;st);
	if (!(buf = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
		err(1, &quot;mmap&quot;);

	for (word = end = buf; end &lt; buf + st.st_size; word = end) {
		while (*word == '\r' || *word == '\n') word++;
		if (!ordered(word, &amp;end)) continue;
		if ((len = end - word + 1) &lt; longest) continue;
		if (len &gt; longest) {
			tail = buf;  /* longer words found; reset out buffer */
			longest = len;
		}
		/* use the same mmap'd region to store output.  because of MAP_PRIVATE,
		 * change will not go back to file.  mmap is copy on write, and we are using
		 * only the head space to store output, so kernel doesn't need to copy more
		 * than the words we saved--in this case, one page tops.
		 */
		memcpy(tail, word, len);
		tail += len;
		*tail = '\0';
	}
	printf(buf);

	munmap(buf, st.st_size);
	close(fd);
	return 0;
}
