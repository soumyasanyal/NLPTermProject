#include &lt;stdio.h&gt;#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;fcntl.h&gt;

typedef struct { char *s; int ln, bad; } rec_t;
int cmp_rec(const void *aa, const void *bb)
{
	const rec_t *a = aa, *b = bb;
	return a-&gt;s == b-&gt;s ? 0 : !a-&gt;s ? 1 : !b-&gt;s ? -1 : strncmp(a-&gt;s, b-&gt;s, 10);
}

int read_file(char *fn)
{
	int fd = open(fn, O_RDONLY);
	if (fd == -1) return 0;

	struct stat s;
	fstat(fd, &amp;s);

	char *txt = malloc(s.st_size);
	read(fd, txt, s.st_size);
	close(fd);

	int i, j, lines = 0, k, di, bad;
	for (i = lines = 0; i &lt; s.st_size; i++)
		if (txt[i] == '\n') {
			txt[i] = '\0';
			lines++;
		}

	rec_t *rec = calloc(sizeof(rec_t), lines);
	char *ptr, *end;
	rec[0].s = txt;
	rec[0].ln = 1;
	for (i = 0; i &lt; lines; i++) {
		if (i + 1 &lt; lines) {
			rec[i + 1].s = rec[i].s + strlen(rec[i].s) + 1;
			rec[i + 1].ln = i + 2;
		}
		if (sscanf(rec[i].s, &quot;%4d-%2d-%2d&quot;, &amp;di, &amp;di, &amp;di) != 3) {
			printf(&quot;bad line %d: %s\n&quot;, i, rec[i].s);
			rec[i].s = 0;
			continue;
		}
		ptr = rec[i].s + 10;

		for (j = k = 0; j &lt; 25; j++) {
			if (!strtod(ptr, &amp;end) &amp;&amp; end == ptr) break;
			k++, ptr = end;
			if (!(di = strtol(ptr, &amp;end, 10)) &amp;&amp; end == ptr) break;
			k++, ptr = end;
			if (di &lt; 1) rec[i].bad = 1;
		}

		if (k != 48) {
			printf(&quot;bad format at line %d: %s\n&quot;, i, rec[i].s);
			rec[i].s = 0;
		}
	}

	qsort(rec, lines, sizeof(rec_t), cmp_rec);
	for (i = 1, bad = rec[0].bad, j = 0; i &lt; lines &amp;&amp; rec[i].s; i++) {
		if (rec[i].bad) bad++;
		if (strncmp(rec[i].s, rec[j].s, 10)) {
			j = i;
		} else
			printf(&quot;dup line %d: %.10s\n&quot;, rec[i].ln, rec[i].s);
	}

	free(rec);
	free(txt);
	printf(&quot;\n%d out %d lines good\n&quot;, lines - bad, lines);
	return 0;
}

int main()
{
	read_file(&quot;readings.txt&quot;);
	return 0;
}
