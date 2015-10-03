#include &lt;stdio.h&gt;typedef unsigned long long ulong;
 
int main(void)
{
	ulong x2;
	int x, t, a, b, c;
	const int base = 10;

	for (c = x = t = 1; x &lt; 100000000; x++) {
		if (x == t) t *= base;

		x2 = (ulong)x * x;
		if ((x2 - x) % (base - 1)) continue;

		b = x2 % t;
		if (b &gt; x || !b) continue;

		a = x2 / t;
		do {
			if (a + b == x) {
				printf(&quot;%2d: %d\n&quot;, c++, x);
				break;
			}
		} while (!(a % base) &amp;&amp; (a /= base));
	}

	return 0;
}
