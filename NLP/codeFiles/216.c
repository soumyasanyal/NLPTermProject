#include &lt;stdio.h&gt;
#define N 10000000
#define CS N	/* cache size */

typedef unsigned long ulong;
ulong cache[CS] = {0};

ulong hailstone(ulong n)
{
	int x;
	if (n == 1) return 1;
	if (n &lt; CS &amp;&amp; cache[n]) return cache[n];

	x = 1 + hailstone((n &amp; 1) ? 3 * n + 1 : n / 2);
	if (n &lt; CS) cache[n] = x;
	return x;
}

int main()
{
	int i, l, max = 0, mi;
	for (i = 1; i &lt; N; i++) {
		if ((l = hailstone(i)) &gt; max) {
			max = l;
			mi = i;
		}
	}
	printf(&quot;max below %d: %d, length %d\n&quot;, N, mi, max);
	return 0;
}
