#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;assert.h&gt;

int main()
{
  int num;
  char *endptr;

  num = strtol(&quot;123459&quot;, &amp;endptr, 0);
  assert(*endptr == '\0');
  printf(&quot;%d\n&quot;, num); /* prints 123459 */

  num = strtol(&quot;0xabcf123&quot;, &amp;endptr, 0);
  assert(*endptr == '\0');
  printf(&quot;%d\n&quot;, num); /* prints 180154659 */

  num = strtol(&quot;07651&quot;, &amp;endptr, 0);
  assert(*endptr == '\0');
  printf(&quot;%d\n&quot;, num); /* prints 4009 */

  /* binary not supported */

  return 0;
}
