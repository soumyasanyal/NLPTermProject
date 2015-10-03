// Input file: input.txt// Output file: output.txt
#include &lt;stdio.h&gt;
int main()
{
   freopen(&quot;input.txt&quot;, &quot;rt&quot;, stdin);
   freopen(&quot;output.txt&quot;, &quot;wt&quot;, stdout);
   int a, b;
   scanf(&quot;%d%d&quot;, &amp;a, &amp;b);
   printf(&quot;%d\n&quot;, a + b);
   return 0;
}
