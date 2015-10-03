#include &lt;stdio.h&gt;
typedef unsigned long long ull;

ull binomial(ull m, ull n)
{
	ull r = 1, d = m - n;
	if (d &gt; n) { n = d; d = m - n; }

	while (m &gt; n) {
		r *= m--;
		while (d &gt; 1 &amp;&amp; ! (r%d) ) r /= d--;
	}

	return r;
}

ull catalan1(int n) {
	return binomial(2 * n, n) / (1 + n);
}

ull catalan2(int n) {
	int i;
	ull r = !n;

	for (i = 0; i &lt; n; i++)
		r += catalan2(i) * catalan2(n - 1 - i);
	return r;
}

ull catalan3(int n)
{
	return n ? 2 * (2 * n - 1) * catalan3(n - 1) / (1 + n) : 1;
}

int main(void)
{
	int i;
	puts(&quot;\tdirect\tsumming\tfrac&quot;);
	for (i = 0; i &lt; 16; i++) {
		printf(&quot;%d\t%llu\t%llu\t%llu\n&quot;, i,
			catalan1(i), catalan2(i), catalan3(i));
	}

	return 0;
}
