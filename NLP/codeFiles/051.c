#include &lt;stdio.h&gt;#include &lt;string.h&gt;

#define FOR(x, y) for(x = 0; x &lt; y; x++)
char *best_shuffle(char *s, int *diff)
{
	int i, j = 0, max = 0, l = strlen(s), cnt[128] = {0};
	char buf[256] = {0}, *r;

	FOR(i, l) if (++cnt[(int)s[i]] &gt; max) max = cnt[(int)s[i]];
	FOR(i, 128) while (cnt[i]--) buf[j++] = i;

	r = strdup(s);
	FOR(i, l) FOR(j, l)
		if (r[i] == buf[j]) {
			r[i] = buf[(j + max) % l] &amp; ~128;
			buf[j] |= 128;
			break;
		}

	*diff = 0;
	FOR(i, l) *diff += r[i] == s[i];

	return r;
}

int main()
{
	int i, d;
	char *r, *t[] = {&quot;abracadabra&quot;, &quot;seesaw&quot;, &quot;elk&quot;, &quot;grrrrrr&quot;, &quot;up&quot;, &quot;a&quot;, 0};
	for (i = 0; t[i]; i++) {
		r = best_shuffle(t[i], &amp;d);
		printf(&quot;%s %s (%d)\n&quot;, t[i], r, d);
	}
	return 0;
}
