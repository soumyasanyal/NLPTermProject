#include &lt;stdio.h&gt;
int main()
{
  int i;
  for (i = 1; i &lt;= 10; i++) {
    printf(&quot;%d&quot;, i);
    printf(i == 10 ? &quot;\n&quot; : &quot;, &quot;);
  }
  return 0;
}
