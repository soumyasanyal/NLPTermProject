#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

#define N 100000
int main()
{
	int i, flip, *q = (int*)malloc(sizeof(int) * N) - 1;

	q[1] = q[2] = 1;

	for (i = 3; i &lt;= N; i++)
		q[i] = q[i - q[i - 1]] + q[i - q[i - 2]];
		
	for (i = 1; i &lt;= 10; i++)
		printf(&quot;%d%c&quot;, q[i], i == 10 ? '\n' : ' ');

	printf(&quot;%d\n&quot;, q[1000]);

	for (flip = 0, i = 1; i &lt; N; i++)
		flip += q[i] &gt; q[i + 1];

	printf(&quot;flips: %d\n&quot;, flip);
	return 0;
}
