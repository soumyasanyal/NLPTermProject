#include &lt;stdio.h&gt;
#define SIZE (1 &lt;&lt; 4)
int main()
{
	int x, y, i;
	for (y = SIZE - 1; y &gt;= 0; y--, putchar('\n')) {
		for (i = 0; i &lt; y; i++) putchar(' ');
		for (x = 0; x + y &lt; SIZE; x++)
			printf((x &amp; y) ? &quot;  &quot; : &quot;* &quot;);
	}
	return 0;
}
