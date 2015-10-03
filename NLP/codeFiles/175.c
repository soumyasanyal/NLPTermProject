#include &lt;stdio.h&gt;
char * base;
void get_diff()
{
	char x;
	if (base - &amp;x &lt; 200)
		printf(&quot;%p %d\n&quot;, &amp;x, base - &amp;x);
}

void recur()
{
	get_diff();
	recur();
}

int main()
{
	char v = 32;
	printf(&quot;pos of v: %p\n&quot;, base = &amp;v);
	recur();
	return 0;
}
