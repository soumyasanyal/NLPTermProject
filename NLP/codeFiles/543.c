#include &lt;stdio.h&gt;#include &lt;time.h&gt;

#define note_file &quot;NOTES.TXT&quot;

int main(int argc, char**argv)
{
	FILE *note = 0;
	time_t tm;
	int i;
	char *p;

	if (argc &lt; 2) {
		if ((note = fopen(note_file, &quot;r&quot;)))
			while ((i = fgetc(note)) != EOF)
				putchar(i);

	} else if ((note = fopen(note_file, &quot;a&quot;)))
		tm = time(0);
		p = ctime(&amp;tm);

		/* skip the newline */
		while (*p) fputc(*p != '\n'?*p:'\t', note), p++;

		for (i = 1; i &lt; argc; i++)
			fprintf(note, &quot;%s%c&quot;, argv[i], 1 + i - argc ? ' ' : '\n');
	}

	if (note) fclose(note);
	return 0;
}
