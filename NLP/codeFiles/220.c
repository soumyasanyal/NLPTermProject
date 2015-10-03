#include &lt;stdio.h&gt;
#define CACHE 256
enum { h_unknown = 0, h_yes, h_no };
unsigned char buf[CACHE] = {0, h_yes, 0};

int happy(int n)
{
	int sum = 0, x, nn;
	if (n &lt; CACHE) {
		if (buf[n]) return 2 - buf[n];
		buf[n] = h_no;
	}

	for (nn = n; nn; nn /= 10) x = nn % 10, sum += x * x;

	x = happy(sum);
	if (n &lt; CACHE) buf[n] = 2 - x;
	return x;
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
