#include &lt;stdio.h&gt;
void bin(int x, char *s)
{
	char*_(int x){
		*(s = x ? _(x &gt;&gt; 1) : s) = (x &amp; 1) + '0';
		return ++s;
	}
	*_(x) = 0;
}

int main()
{
	char a[100];
	int i;
	for (i = 0; i &lt;= 1984; i += 31)
		bin(i, a), printf(&quot;%4d: %s\n&quot;, i, a);

	return 0;
}
