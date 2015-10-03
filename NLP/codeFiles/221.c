#include &lt;stdio.h&gt;
int dsum(int n)
{
	int sum, x;
	for (sum = 0; n; n /= 10) x = n % 10, sum += x * x;
	return sum;
}

int happy(int n)
{
	int nn;
	while (n &gt; 999) n = dsum(n); /* 4 digit numbers can't cycle */
	nn = dsum(n);
	while (nn != n &amp;&amp; nn != 1)
		n = dsum(n), nn = dsum(dsum(nn));
	return n == 1;
}

int main()
{
	int i, cnt = 8;
	for (i = 1; cnt || !printf(&quot;\n&quot;); i++)
		if (happy(i)) --cnt, printf(&quot;%d &quot;, i);

	printf(&quot;The %dth happy number: &quot;, cnt = 1000000);
	for (i = 1; cnt; i++)
		if (happy(i)) --cnt || printf(&quot;%d\n&quot;, i);

	return 0;
}
