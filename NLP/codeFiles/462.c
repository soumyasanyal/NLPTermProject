#include &lt;stdio.h&gt;
typedef unsigned int set_t; /* probably 32 bits; change according to need */

void show_set(set_t x, char *name)
{
	int i;
	printf(&quot;%s is:&quot;, name);
	for (i = 0; (1U &lt;&lt; i) &lt;= x; i++)
		if (x &amp; (1U &lt;&lt; i))
			printf(&quot; %d&quot;, i);
	putchar('\n');
}

int main(void)
{
	int i;
	set_t a, b, c;
	
	a = 0; /* empty set */
	for (i = 0; i &lt; 10; i += 3) /* add 0 3 6 9 to set a */
		a |= (1U &lt;&lt; i);
	show_set(a, &quot;a&quot;);

	for (i = 0; i &lt; 5; i++)
		printf(&quot;\t%d%s in set a\n&quot;, i, (a &amp; (1U &lt;&lt; i)) ? &quot;&quot;:&quot; not&quot;);

	b = a;
	b |= (1U &lt;&lt; 5); b |= (1U &lt;&lt; 10); /* b is a plus 5, 10 */
	b &amp;= ~(1U &lt;&lt; 0);	/* sans 0 */
	show_set(b, &quot;b&quot;);

	show_set(a | b, &quot;union(a, b)&quot;);
	show_set(c = a &amp; b, &quot;c = common(a, b)&quot;);
	show_set(a &amp; ~b, &quot;a - b&quot;); /* diff, not arithmetic minus */
	show_set(b &amp; ~a, &quot;b - a&quot;);
	printf(&quot;b is%s a subset of a\n&quot;, !(b &amp; ~a) ? &quot;&quot; : &quot; not&quot;);
	printf(&quot;c is%s a subset of a\n&quot;, !(c &amp; ~a) ? &quot;&quot; : &quot; not&quot;);

	printf(&quot;union(a, b) - common(a, b) %s union(a - b, b - a)\n&quot;,
		((a | b) &amp; ~(a &amp; b)) == ((a &amp; ~b) | (b &amp; ~a))
			? &quot;equals&quot; : &quot;does not equal&quot;);

	return 0;
}
