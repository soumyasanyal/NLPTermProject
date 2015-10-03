#include&lt;stdio.h&gt; 
int main ()
{
	int i;
	char *s[] = { &quot;%d\n&quot;, &quot;Fizz\n&quot;, s[3] + 4, &quot;FizzBuzz\n&quot; };
	for (i = 1; i &lt;= 100; i++)
		printf(s[!(i % 3) + 2 * !(i % 5)], i);

	return 0;
}
