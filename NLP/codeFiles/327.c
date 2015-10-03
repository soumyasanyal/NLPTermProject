#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
 
double pi(double tolerance)
{
	double x, y, val, error;
	unsigned long sampled = 0, hit = 0, i;

	do {
		/* don't check error every turn, make loop tight */
		for (i = 1000000; i; i--, sampled++) {
			x = rand() / (RAND_MAX + 1.0);
			y = rand() / (RAND_MAX + 1.0);
			if (x * x + y * y &lt; 1) hit ++;
		}

		val = (double) hit / sampled;
		error = val * sqrt(val * (1 - val) / sampled) * 4;
		val *= 4;

		/* some feedback, or user gets bored */
		fprintf(stderr, &quot;Pi = %f +/- %5.3e at %ldM samples.\r&quot;,
			val, error, sampled/1000000);
	} while (!hit || error &gt; tolerance);
              /* !hit is for completeness's sake; if no hit after 1M samples,
                 your rand() is BROKEN */

	return val;
}

int main()
{
	printf(&quot;Pi is %f\n&quot;, pi(3e-4)); /* set to 1e-4 for some fun */
	return 0;
}
