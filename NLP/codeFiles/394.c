#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* pick a random index from 0 to n-1, according to probablities listed
   in p[] which is assumed to have a sum of 1. The values in the probablity
   list matters up to the point where the sum goes over 1 */
int rand_idx(double *p, int n)
{
	double s = rand() / (RAND_MAX + 1.0);
	int i;
	for (i = 0; i &lt; n - 1 &amp;&amp; (s -= p[i]) &gt;= 0; i++);
	return i;
}

#define LEN 8
#define N 1000000
int main()
{
	char *names[LEN] = { &quot;aleph&quot;, &quot;beth&quot;, &quot;gimel&quot;, &quot;daleth&quot;,
			  &quot;he&quot;, &quot;waw&quot;, &quot;zayin&quot;, &quot;heth&quot; };
	double s, p[LEN] = { 1./5, 1./6, 1./7, 1./8, 1./9, 1./10, 1./11, 1e300 };
	int i, count[LEN] = {0};

	for (i = 0; i &lt; N; i++) count[rand_idx(p, LEN)] ++;

	printf(&quot;  Name  Count    Ratio Expected\n&quot;);
	for (i = 0, s = 1; i &lt; LEN; s -= p[i++])
		printf(&quot;%6s%7d %7.4f%% %7.4f%%\n&quot;,
			names[i], count[i],
			(double)count[i] / N * 100,
			((i &lt; LEN - 1) ? p[i] : s) * 100);

	return 0;
}
