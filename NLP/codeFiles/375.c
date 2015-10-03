#include &lt;stdio.h&gt;
#define D 32
int pascals(int *x, int *y, int d)
{
	int i;
	for (i = 1; i &lt; d; i++)
		printf(&quot;%d%c&quot;, y[i] = x[i - 1] + x[i],
			i &lt; d - 1 ? ' ' : '\n');

	return D &gt; d ? pascals(y, x, d + 1) : 0;
}

int main()
{
	int x[D] = {0, 1, 0}, y[D] = {0};
	return pascals(x, y, 0);
}
