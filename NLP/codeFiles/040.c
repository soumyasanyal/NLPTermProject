#include &lt;stdio.h&gt;
double mean(double *v, int len)
{
	double sum = 0;
	int i;
	for (i = 0; i &lt; len; i++)
		sum += v[i];
	return sum / len;
}

int main(void)
{
	double v[] = {1, 2, 2.718, 3, 3.142};
	int i, len;
	for (len = 5; len &gt;= 0; len--) {
		printf(&quot;mean[&quot;);
		for (i = 0; i &lt; len; i++)
			printf(i ? &quot;, %g&quot; : &quot;%g&quot;, v[i]);
		printf(&quot;] = %g\n&quot;, mean(v, len));
	}

	return 0;
}
