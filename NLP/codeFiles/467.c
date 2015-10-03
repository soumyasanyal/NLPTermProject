#include &lt;stdio.h&gt;
int main()
{
	int i, j, dim, d;
	int depth = 3;

	for (i = 0, dim = 1; i &lt; depth; i++, dim *= 3);

	for (i = 0; i &lt; dim; i++) {
		for (j = 0; j &lt; dim; j++) {
			for (d = dim / 3; d; d /= 3)
				if ((i % (d * 3)) / d == 1 &amp;&amp; (j % (d * 3)) / d == 1)
					break;
			printf(d ? &quot;  &quot; : &quot;##&quot;);
		}
		printf(&quot;\n&quot;);
	}

	return 0;
}
