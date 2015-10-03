#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;

/* for ASCII only */
static char code[128] = { 0 };
void add_code(const char *s, int c)
{
	while (*s) {
		code[(int)*s] = code[0x20 ^ (int)*s] = c;
		s++;
	}
}

void init()
{
	static const char *cls[] =
		{ &quot;AEIOU&quot;, &quot;&quot;, &quot;BFPV&quot;, &quot;CGJKQSXZ&quot;, &quot;DT&quot;, &quot;L&quot;, &quot;MN&quot;, &quot;R&quot;, 0};
	int i;
	for (i = 0; cls[i]; i++)
		add_code(cls[i], i - 1);
}

static char out[5];
/* returns a static buffer; user must copy if want to save
   result across calls */
char* soundex(char *s)
{
	int c, prev, i;

	out[0] = out[4] = 0;
	if (!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for (i = 1; *s &amp;&amp; i &lt; 4; s++) {
		if ((c = code[(int)*s]) == prev) continue;

		if (c == -1) prev = 0;	/* vowel as separator */
		else if (c &gt; 0) {
			out[i++] = c + '0';
			prev = c;
		}
	}
	while (i &lt; 4) out[i++] = '0';
	return out;
}

int main()
{
	int i;
	char *sdx, *names[][2] = {
		{&quot;Soundex&quot;,	&quot;S532&quot;},
		{&quot;Example&quot;,	&quot;E251&quot;},
		{&quot;Sownteks&quot;,	&quot;S532&quot;},
		{&quot;Ekzampul&quot;,	&quot;E251&quot;},
		{&quot;Euler&quot;,	&quot;E460&quot;},
		{&quot;Gauss&quot;,	&quot;G200&quot;},
		{&quot;Hilbert&quot;,	&quot;H416&quot;},
		{&quot;Knuth&quot;,	&quot;K530&quot;},
		{&quot;Lloyd&quot;,	&quot;L300&quot;},
		{&quot;Lukasiewicz&quot;,	&quot;L222&quot;},
		{&quot;Ellery&quot;,	&quot;E460&quot;},
		{&quot;Ghosh&quot;,	&quot;G200&quot;},
		{&quot;Heilbronn&quot;,	&quot;H416&quot;},
		{&quot;Kant&quot;,	&quot;K530&quot;},
		{&quot;Ladd&quot;,	&quot;L300&quot;},
		{&quot;Lissajous&quot;,	&quot;L222&quot;},
		{&quot;Wheaton&quot;,	&quot;W350&quot;},
		{&quot;Burroughs&quot;,	&quot;B620&quot;},
		{&quot;Burrows&quot;,	&quot;B620&quot;},
		{&quot;O'Hara&quot;,	&quot;O600&quot;},
		{&quot;Washington&quot;,	&quot;W252&quot;},
		{&quot;Lee&quot;,		&quot;L000&quot;},
		{&quot;Gutierrez&quot;,	&quot;G362&quot;},
		{&quot;Pfister&quot;,	&quot;P236&quot;},
		{&quot;Jackson&quot;,	&quot;J250&quot;},
		{&quot;Tymczak&quot;,	&quot;T522&quot;},
		{&quot;VanDeusen&quot;,	&quot;V532&quot;},
		{&quot;Ashcraft&quot;,	&quot;A261&quot;},
		{0, 0}
	};

	init();

	puts(&quot;  Test name  Code  Got\n----------------------&quot;);
	for (i = 0; names[i][0]; i++) {
		sdx = soundex(names[i][0]);
		printf(&quot;%11s  %s  %s &quot;, names[i][0], names[i][1], sdx);
		printf(&quot;%s\n&quot;, strcmp(sdx, names[i][1]) ? &quot;not ok&quot; : &quot;ok&quot;);
	}

	return 0;
}
