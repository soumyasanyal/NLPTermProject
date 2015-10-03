#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
 
typedef unsigned long long xint;
typedef unsigned long ulong;

inline ulong gcd(ulong m, ulong n)
{
	ulong t;
	while (n) { t = n; n = m % n; m = t; }
	return m;
}
 
int main()
{
	ulong a, b, c, pytha = 0, prim = 0, max_p = 100;
	xint aa, bb, cc;

	for (a = 1; a &lt;= max_p / 3; a++) {
		aa = (xint)a * a;
		printf(&quot;a = %lu\r&quot;, a); /* show that we are working */
		fflush(stdout);

		/*  max_p/2: valid limit, because one side of triangle
		 *  must be less than the sum of the other two
		 */
		for (b = a + 1; b &lt; max_p/2; b++) {
			bb = (xint)b * b;
			for (c = b + 1; c &lt; max_p/2; c++) {
				cc = (xint)c * c;
				if (aa + bb &lt; cc) break;
				if (a + b + c &gt; max_p) break;

				if (aa + bb == cc) {
					pytha++;
					if (gcd(a, b) == 1) prim++;
				}
			}
		}
	}
 
	printf(&quot;Up to %lu, there are %lu triples, of which %lu are primitive\n&quot;,
		max_p, pytha, prim);

	return 0;
}
