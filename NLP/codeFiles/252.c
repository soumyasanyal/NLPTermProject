#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

char *get_line(FILE* fp)
{
	int len = 0, got = 0, c;
	char *buf = 0;

	while ((c = fgetc(fp)) != EOF) {
		if (got + 1 &gt;= len) {
			len *= 2;
			if (len &lt; 4) len = 4;
			buf = realloc(buf, len);
		}
		buf[got++] = c;
		if (c == '\n') break;
	}
	if (c == EOF &amp;&amp; !got) return 0;

	buf[got++] = '\0';
	return buf;
}

int main()
{
	char *s;
	while ((s = get_line(stdin))) {
		printf(&quot;%s&quot;,s);
		free(s);
	}
	return 0;
}
