#include &lt;stdio.h&gt;#include &lt;float.h&gt;

inline double abs_(double x) { return x &gt;= 0 ? x : -x; }
double pow_(double x, int e)
{
	double ret = 1;
	for (ret = 1; e; x *= x, e &gt;&gt;= 1)
		if ((e &amp; 1)) ret *= x;
	return ret;
}

double root(double a, int n)
{
	double x0, x1 = 1;
	if (!a) return 0;
	if (n &lt; 1 || (a &lt; 0 &amp;&amp; !(n&amp;1))) return 0./0.; /* NaN */

	do {	x0 = x1;
		x1 = ((n - 1) * x1 + a / pow_(x1, (n - 1))) / n;
	} while (abs_(x0 - x1) &gt;= abs_(x1) * (DBL_EPSILON * 10));

	return x1;
}

int main()
{
	double x = pow_(-3.14159, 15);
	printf(&quot;root(%g, 15) = %g\n&quot;, x, root(x, 15));
	return 0;
}
