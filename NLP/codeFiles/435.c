#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;locale.h&gt;
#include &lt;wchar.h&gt;

char *sa = &quot;abcdef&quot;;
char *su = &quot;as⃝df̅&quot;; /* Should be in your native locale encoding. Mine is UTF-8 */

int is_comb(wchar_t c)
{
	if (c &gt;= 0x300 &amp;&amp; c &lt;= 0x36f) return 1;
	if (c &gt;= 0x1dc0 &amp;&amp; c &lt;= 0x1dff) return 1;
	if (c &gt;= 0x20d0 &amp;&amp; c &lt;= 0x20ff) return 1;
	if (c &gt;= 0xfe20 &amp;&amp; c &lt;= 0xfe2f) return 1;
	return 0;
}

wchar_t* mb_to_wchar(char *s)
{
	wchar_t *u;
	size_t len = mbstowcs(0, s, 0) + 1;
	if (!len) return 0;

	u = malloc(sizeof(wchar_t) * len);
	mbstowcs(u, s, len);
	return u;
}

wchar_t* ws_reverse(wchar_t* u)
{
	size_t len, i, j;
	wchar_t *out;
	for (len = 0; u[len]; len++);
	out = malloc(sizeof(wchar_t) * (len + 1));
	out[len] = 0;
	j = 0;
	while (len) {
		for (i = len - 1; i &amp;&amp; is_comb(u[i]); i--);
		wcsncpy(out + j, u + i, len - i);
		j += len - i;
		len = i;
	}
	return out;
}

char *mb_reverse(char *in)
{
	size_t len;
	char *out;
	wchar_t *u = mb_to_wchar(in);
	wchar_t *r = ws_reverse(u);
	len = wcstombs(0, r, 0) + 1;
	out = malloc(len);
	wcstombs(out, r, len);
	free(u);
	free(r);
	return out;
}

int main(void)
{
	setlocale(LC_CTYPE, &quot;&quot;);

	printf(&quot;%s =&gt; %s\n&quot;, sa, mb_reverse(sa));
	printf(&quot;%s =&gt; %s\n&quot;, su, mb_reverse(su));
	return 0;
}
