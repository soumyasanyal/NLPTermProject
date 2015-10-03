#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

inline int irand(int n)
{
	int r, randmax = RAND_MAX/n * n;
	while ((r = rand()) &gt;= randmax);
	return r / (randmax / n);
}

inline int one_of_n(int n)
{
	int i, r = 0;
	for (i = 1; i &lt; n; i++) if (!irand(i + 1)) r = i;
	return r;
}

int main(void)
{
	int i, r[10] = {0};

	for (i = 0; i &lt; 1000000; i++, r[one_of_n(10)]++);
	for (i = 0; i &lt; 10; i++)
		printf(&quot;%d%c&quot;, r[i], i == 9 ? '\n':' ');

	return 0;
}
