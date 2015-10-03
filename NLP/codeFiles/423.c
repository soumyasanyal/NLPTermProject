#include &lt;unistd.h&gt;#include &lt;sys/types.h&gt;
#include &lt;sys/mman.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;err.h&gt;

/* following code assumes all file operations succeed. In practice,
 * return codes from open, close, fstat, mmap, munmap all need to be
 * checked for error.
*/
int read_file_line(char *path, int line_no)
{
	struct stat s;
	char *buf;
	off_t start = -1, end = -1;
	size_t i;
	int ln, fd, ret = 1;

	if (line_no == 1) start = 0;
	else if (line_no &lt; 1){
		warn(&quot;line_no too small&quot;);
		return 0; /* line_no starts at 1; less is error */
	}

	line_no--; /* back to zero based, easier */

	fd = open(path, O_RDONLY);
	fstat(fd, &amp;s);

	/* Map the whole file.  If the file is huge (up to GBs), OS will swap
	 * pages in and out, and because search for lines goes sequentially
	 * and never accesses more than one page at a time, penalty is low.
	 * If the file is HUGE, such that OS can't find an address space to map
	 * it, we got a real problem.  In practice one would repeatedly map small
	 * chunks, say 1MB at a time, and find the offsets of the line along the
	 * way.  Although, if file is really so huge, the line itself can't be
	 * garanteed small enough to be &quot;stored in memory&quot;, so there.
	 */
	buf = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	/* optional; if the file is large, tell OS to read ahead */
	madvise(buf, s.st_size, MADV_SEQUENTIAL);

	for (i = ln = 0; i &lt; s.st_size &amp;&amp; ln &lt;= line_no; i++) {
		if (buf[i] != '\n') continue;

		if (++ln == line_no) start = i + 1;
		else if (ln == line_no + 1) end = i + 1;
	}

	if (start &gt;= s.st_size || start &lt; 0) {
		warn(&quot;file does not have line %d&quot;, line_no + 1);
		ret = 0;
	} else {
		/* 	do something with the line here, like
		write(STDOUT_FILENO, buf + start, end - start);
			or copy it out, or something
		*/
	}

	munmap(buf, s.st_size);
	close(fd);

	return ret;
}
