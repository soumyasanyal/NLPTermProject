#include &lt;stdio.h&gt;
int main()
{
  rename(&quot;input.txt&quot;, &quot;output.txt&quot;);
  rename(&quot;docs&quot;, &quot;mydocs&quot;);
  rename(&quot;/input.txt&quot;, &quot;/output.txt&quot;);
  rename(&quot;/docs&quot;, &quot;/mydocs&quot;);
  return 0;
}
