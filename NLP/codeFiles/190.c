#include &lt;stdlib.h&gt;#include &lt;string.h&gt;
#include &lt;stdio.h&gt;

double* fwd_diff(double* x, unsigned int len, unsigned int order)
{
	unsigned int i, j;
	double* y;

	/* handle two special cases */
	if (order &gt;= len) return 0;

	y = malloc(sizeof(double) * len);
	if (!order) {
		memcpy(y, x, sizeof(double) * len);
		return y;
	}

	/* first order diff goes from x-&gt;y, later ones go from y-&gt;y */
	for (j = 0; j &lt; order; j++, x = y)
		for (i = 0, len--; i &lt; len; i++)
			y[i] = x[i + 1] - x[i];

	y = realloc(y, sizeof(double) * len);
	return y;
}

int main(void)
{
	double *y, x[] = {90, 47, 58, 29, 22, 32, 55, 5, 55, 73};
	int i, len = sizeof(x) / sizeof(x[0]);

	y = fwd_diff(x, len, 1);
	for (i = 0; i &lt; len - 1; i++)
		printf(&quot;%g &quot;, y[i]);
	putchar('\n');

	return 0;
}
