#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

inline
int randn(int m)
{
	int rand_max = RAND_MAX - (RAND_MAX % m);
	int r;
	while ((r = rand()) &gt; rand_max);
	return r / (rand_max / m);
}

int main()
{
	int i, x, y, r2;
	unsigned long buf[31] = {0}; /* could just use 2d array */

	for (i = 0; i &lt; 100; ) {
		x = randn(31) - 15;
		y = randn(31) - 15;
		r2 = x * x + y * y;
		if (r2 &gt;= 100 &amp;&amp; r2 &lt;= 225) {
			buf[15 + y] |= 1 &lt;&lt; (x + 15);
			i++;
		}
	}

	for (y = 0; y &lt; 31; y++) {
		for (x = 0; x &lt; 31; x++)
			printf((buf[y] &amp; 1 &lt;&lt; x) ? &quot;. &quot; : &quot;  &quot;);
		printf(&quot;\n&quot;);
	}

	return 0;
}
