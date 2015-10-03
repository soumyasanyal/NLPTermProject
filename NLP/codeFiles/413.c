#include &lt;inttypes.h&gt;	/* PRIu32 */#include &lt;stdlib.h&gt;	/* arc4random */
#include &lt;stdio.h&gt;	/* printf */

int
main()
{
	printf(&quot;%&quot; PRIu32 &quot;\n&quot;, arc4random());
	return 0;
}
