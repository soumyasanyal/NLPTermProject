#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* Flip a coin, 10 times. */
int
main()
{
	int i;
	srand(time(NULL));
	for (i = 0; i &lt; 10; i++)
		puts((rand() % 2) ? &quot;heads&quot; : &quot;tails&quot;);
	return 0;
}
