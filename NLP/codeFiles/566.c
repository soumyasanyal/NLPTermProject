#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main()
{
	int junk, *junkp;

	/* Print an unitialized variable! */
	printf(&quot;junk: %d\n&quot;, junk);

	/* Follow a pointer to unitialized memory! */
	junkp = malloc(sizeof *junkp);
	if (junkp)
		printf(&quot;*junkp: %d\n&quot;, *junkp);
	return 0;
}
