#include &lt;stdio.h&gt;#include &lt;limits.h&gt;

typedef unsigned long ULONG;

ULONG binomial(ULONG n, ULONG k)
{
	ULONG r = 1, d = n - k;

	/* choose the smaller of k and n - k */
	if (d &gt; k) { k = d; d = n - k; }

	while (n &gt; k) {
		if (r &gt;= UINT_MAX / n) return 0; /* overflown */
		r *= n--;

		/* divide (n - k)! as soon as we can to delay overflows */
		while (d &gt; 1 &amp;&amp; !(r % d)) r /= d--;
	}
	return r;
}

int main()
{
	printf(&quot;%lu\n&quot;, binomial(5, 3));
	return 0;
}
