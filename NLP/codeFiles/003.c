#include &lt;stdio.h&gt;
int main()
{
	int i;
	for (i = 1; i * i &lt;= 100; i++)
		printf(&quot;door %d open\n&quot;, i * i);

	return 0;
}
