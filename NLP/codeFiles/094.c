#include &lt;stdlib.h&gt;	/* exit() */#include &lt;stdio.h&gt;	/* fputs(), printf() */
#include &lt;string.h&gt;

int
main()
{
	char src[] = &quot;Hello&quot;;
	char dst[80];

	/* Use strlcpy() from &lt;string.h&gt;. */
	if (strlcpy(dst, src, sizeof dst) &gt;= sizeof dst) {
		fputs(&quot;The buffer is too small!\n&quot;, stderr);
		exit(1);
	}

	memset(src, '-', 5);
	printf(&quot;src: %s\n&quot;, src);  /* src: ----- */
	printf(&quot;dst: %s\n&quot;, dst);  /* dst: Hello */

	return 0;
}
