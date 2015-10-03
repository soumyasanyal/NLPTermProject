#include &lt;stdio.h&gt;
int main()
{
  int a, b;
  scanf(&quot;%d %d&quot;, &amp;a, &amp;b);

  if (a &lt; b)
    printf(&quot;%d is less than %d\n&quot;, a, b);

  if (a == b)
    printf(&quot;%d is equal to %d\n&quot;, a, b);

  if (a &gt; b)
    printf(&quot;%d is greater than %d\n&quot;, a, b);

  return 0;
}
