#include &lt;stdio.h&gt;
int main()
{
	fprintf(stderr, &quot;Goodbye, &quot;);
	fputs(&quot;World!\n&quot;, stderr);

	return 0;
}
