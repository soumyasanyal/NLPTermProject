#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef double half_truth, maybe;

inline maybe not3(maybe a) { return 1 - a; }

inline maybe
and3(maybe a, maybe b) { return a * b; }

inline maybe
or3(maybe a, maybe b) { return a + b - a * b; }

inline maybe
eq3(maybe a, maybe b) { return 1 - a - b + 2 * a * b; }

inline maybe
imply3(maybe a, maybe b) { return or3(not3(a), b); }

#define true3(x) ((x) * RAND_MAX &gt; rand())
#define if3(x) if (true3(x))

int main()
{
	maybe roses_are_red = 0.25; /* they can be white or black, too */
	maybe violets_are_blue = 1; /* aren't they just */
	int i;

	puts(&quot;Verifying flowery truth for 40 times:\n&quot;);

	puts(&quot;Rose is NOT red:&quot;); /* chance: .75 */
	for (i = 0; i &lt; 40 || !puts(&quot;\n&quot;); i++)
		printf( true3( not3(roses_are_red) ) ? &quot;T&quot; : &quot;_&quot;);

	/* pick a rose and a violet; */
	puts(&quot;Rose is red AND violet is blue:&quot;);
	/* chance of rose being red AND violet being blue is .25 */
	for (i = 0; i &lt; 40 || !puts(&quot;\n&quot;); i++)
		printf( true3( and3(roses_are_red, violets_are_blue) )
			? &quot;T&quot; : &quot;_&quot;);

	/* chance of rose being red OR violet being blue is 1 */
	puts(&quot;Rose is red OR violet is blue:&quot;);
	for (i = 0; i &lt; 40 || !puts(&quot;\n&quot;); i++)
		printf( true3( or3(roses_are_red, violets_are_blue) )
			? &quot;T&quot; : &quot;_&quot;);

	/* pick two roses; chance of em being both red or both not red is .625 */
	puts(&quot;This rose is as red as that rose:&quot;);
	for (i = 0; i &lt; 40 || !puts(&quot;\n&quot;); i++)
		if3(eq3(roses_are_red, roses_are_red)) putchar('T');
		else putchar('_');

	return 0;
}
