#include &lt;stdlib.h&gt;	/* malloc(), realloc(), free() */#include &lt;stdio.h&gt;	/* fopen(), fgetc(), fwrite(), printf() */

#include &lt;libco.h&gt;	/* co_create(), co_switch() */

void
fail(const char *message) {
	perror(message);
	exit(1);
}

/*
 * These are global variables of this process. All cothreads of this
 * process will share these global variables.
 */
cothread_t reader;
cothread_t printer;
struct {
	char	*buf;	/* Not a C string. No terminating '\0'. */
	size_t	len;	/* Length of line in buffer. */
	size_t	cap;	/* Maximum capacity of buffer. */
} line;
size_t count;		/* Number of lines printed. */

/*
 * The reader cothread reads every line of an input file, passes each
 * line to the printer cothread, and reports the number of lines.
 */
void
reader_entry(void)
{
	FILE *input;
	size_t newcap;
	int c, eof, eol;
	char *newbuf;

	input = fopen(&quot;input.txt&quot;, &quot;r&quot;);
	if (input == NULL)
		fail(&quot;fopen&quot;);

	line.buf = malloc(line.cap = 4096);  /* New buffer. */
	if (line.buf == NULL)
		fail(&quot;malloc&quot;);
	line.len = 0;  /* Start with an empty line. */

	do {
		c = fgetc(input);  /* Read next character. */
		if (ferror(input))
			fail(&quot;fgetc&quot;);

		eof = (c == EOF);
		if (eof) {
			/*
			 * End of file is also end of line,
		`	 * unless the line would be empty.
			 */
			eol = (line.len &gt; 0);
		} else {
			/* Append c to the buffer. */
			if (line.len == line.cap) {
				/* Need a bigger buffer! */
				newcap = line.cap * 2;
				newbuf = realloc(line.buf, newcap);
				if (newbuf == NULL)
					fail(&quot;realloc&quot;);
				line.buf = newbuf;
				line.cap = newcap;
			}
			line.buf[line.len++] = c;

			/* '\n' is end of line. */
			eol = (c == '\n');
		}

		if (eol) {
			/* Pass our complete line to the printer. */
			co_switch(printer);
			line.len = 0;  /* Destroy our line. */
		}
	} while (!eof);

	free(line.buf);
	line.buf = NULL;  /* Stops a loop in the printer. */

	printf(&quot;Printed %zu lines.\n&quot;, count);
	co_switch(printer);
}

/*
 * The printer cothread starts the reader cothread, prints every line
 * line from the reader cothread, and counts the number of lines.
 */
int
main()
{
	reader = co_create(4096, reader_entry);
	printer = co_active();
	count = 0;

	for (;;) {
		co_switch(reader);
		if (line.buf == NULL)
			break;

		/* Print this line. Count it. */
		fwrite(line.buf, 1, line.len, stdout);
		count++;
	}

	co_delete(reader);
	return 0;
}
