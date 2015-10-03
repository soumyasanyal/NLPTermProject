#include &lt;stdio.h&gt;
int main()
{
  int num;

  sscanf(&quot;0123459&quot;, &quot;%d&quot;, &amp;num);
  printf(&quot;%d\n&quot;, num); /* prints 123459 */

  sscanf(&quot;abcf123&quot;, &quot;%x&quot;, &amp;num);
  printf(&quot;%d\n&quot;, num); /* prints 180154659 */

  sscanf(&quot;7651&quot;, &quot;%o&quot;, &amp;num);
  printf(&quot;%d\n&quot;, num); /* prints 4009 */

  /* binary not supported */

  return 0;
}
