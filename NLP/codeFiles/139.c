#include &lt;stdio.h&gt;#include &lt;math.h&gt;

typedef double (*deriv_f)(double, double);
#define FMT &quot; %7.3f&quot;

void ivp_euler(deriv_f f, double y, int step, int end_t)
{
	int t = 0;

	printf(&quot; Step %2d: &quot;, (int)step);
	do {
		if (t % 10 == 0) printf(FMT, y);
		y += step * f(t, y);
	} while ((t += step) &lt;= end_t);
	printf(&quot;\n&quot;);
}

void analytic()
{
	double t;
	printf(&quot;    Time: &quot;);
	for (t = 0; t &lt;= 100; t += 10) printf(&quot; %7g&quot;, t);
	printf(&quot;\nAnalytic: &quot;);

	for (t = 0; t &lt;= 100; t += 10)
		printf(FMT, 20 + 80 * exp(-0.07 * t));
	printf(&quot;\n&quot;);
}

double cooling(double t, double temp)
{
	return -0.07 * (temp - 20);
}

int main()
{
	analytic();
	ivp_euler(cooling, 100, 2, 100);
	ivp_euler(cooling, 100, 5, 100);
	ivp_euler(cooling, 100, 10, 100);

	return 0;
}
