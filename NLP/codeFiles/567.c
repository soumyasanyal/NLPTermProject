#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;locale.h&gt;

/* wchar_t is the standard type for wide chars; what it is internally
 * depends on the compiler.
 */
wchar_t poker[] = L&quot;♥♦♣♠&quot;;
wchar_t four_two[] = L&quot;\x56db\x5341\x4e8c&quot;;

int main() {
	/* Set the locale to alert C's multibyte output routines */
	if (!setlocale(LC_CTYPE, &quot;&quot;)) {
		fprintf(stderr, &quot;Locale failure, check your env vars\n&quot;);
		return 1;
	}

#ifdef __STDC_ISO_10646__
	/* C99 compilers should understand these */
	printf(&quot;%lc\n&quot;, 0x2708);	/* ✈ */
	printf(&quot;%ls\n&quot;, poker);		/* ♥♦♣♠ */
	printf(&quot;%ls\n&quot;, four_two);	/* 四十二 */
#else
	/* oh well */
	printf(&quot;airplane\n&quot;);
	printf(&quot;club diamond club spade\n&quot;);
	printf(&quot;for ty two\n&quot;);
#endif
	return 0;
}
