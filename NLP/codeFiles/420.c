#include &lt;err.h&gt;	/* err */#include &lt;stdio.h&gt;	/* fopen, fgetln, fputs, fwrite */

/*
 * Read a file line by line.
 * http://rosettacode.org/wiki/Read_a_file_line_by_line
 */
int
main()
{
	FILE *f;
	size_t len;
	char *line;

	f = fopen(&quot;foobar.txt&quot;, &quot;r&quot;);
	if (f == NULL)
		err(1, &quot;foobar.txt&quot;);

	/*
	 * This loop reads each line.
	 * Remember that line is not a C string.
	 * There is no terminating '\0'.
	 */
	while (line = fgetln(f, &amp;len)) {
		/*
		 * Do something with line.
		 */
		fputs(&quot;LINE: &quot;, stdout);
		fwrite(line, len, 1, stdout);
	}
	if (!feof(f))
		err(1, &quot;fgetln&quot;);

	return 0;
}
