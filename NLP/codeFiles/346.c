#include &lt;stdio.h&gt;
int main()
{
  int i;

  for(i=1; i &lt;= 33; i++)
    printf(&quot;%6d %6x %6o\n&quot;, i, i, i);

  return 0;
}
