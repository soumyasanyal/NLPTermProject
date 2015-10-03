#include &lt;stdio.h&gt;#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;sys/mman.h&gt;
#include &lt;err.h&gt;
#include &lt;string.h&gt;

int main()
{
	struct stat s;
	int fd = open(&quot;mlijobs.txt&quot;, O_RDONLY);
	int cnt, max_cnt, occur;
	char *buf, *ptr;

	if (fd == -1) err(1, &quot;open&quot;);
	fstat(fd, &amp;s);
	ptr = buf = mmap(0, s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	cnt = max_cnt = 0;
	while(ptr - buf &lt; s.st_size - 33) {
		if (!strncmp(ptr, &quot;License OUT&quot;, 11) &amp;&amp; ++cnt &gt;= max_cnt) {
			if (cnt &gt; max_cnt) {
				max_cnt = cnt;
				occur = 0;
			}
			/* can't sprintf time stamp: might overlap */
			memmove(buf + 26 * occur, ptr + 14, 19);
			sprintf(buf + 26 * occur + 19, &quot;%6d\n&quot;, cnt);
			occur++;
		} else if (!strncmp(ptr, &quot;License IN &quot;, 11)) cnt --;

		while (ptr &lt; buf + s.st_size &amp;&amp; *ptr++ != '\n');
	}

	printf(buf);
	munmap(buf, s.st_size);
	return close(fd);
}
