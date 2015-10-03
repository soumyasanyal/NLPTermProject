#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdint.h&gt;

typedef uint32_t uint;
uint full, *qs, count = 0, nn;

void solve(uint d, uint c, uint l, uint r)
{
	uint b, a, *s;
	if (!d) {
		count++;
#if 0
		printf(&quot;\nNo. %d\n===========\n&quot;, count);
		for (a = 0; a &lt; nn; a++, putchar('\n'))
			for (b = 0; b &lt; nn; b++, putchar(' '))
				putchar(&quot; -QQ&quot;[((b == qs[a])&lt;&lt;1)|((a + b)&amp;1)]);
#endif
		return;
	}

	a = (c | (l &lt;&lt;= 1) | (r &gt;&gt;= 1)) &amp; full;
	if (a != full)
		for (*(s = qs + --d) = 0, b = 1; b &lt;= full; (*s)++, b &lt;&lt;= 1)
			if (!(b &amp; a)) solve(d, b|c, b|l, b|r);
}

int main(int n, char **argv)
{
	if (n &lt;= 1 || (nn = atoi(argv[1])) &lt;= 0) nn = 8;

	qs = calloc(nn, sizeof(int));
	full = (1U &lt;&lt; nn) - 1;

	solve(nn, 0, 0, 0);
	printf(&quot;\nSolutions: %d\n&quot;, count);
	return 0;
}
