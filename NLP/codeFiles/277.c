#include &lt;stdio.h&gt;
int main(void)
{
  printf(&quot;%s\n&quot;,
         ( (727 == 0x2d7) &amp;&amp; 
           (727 == 01327)    ) ? &quot;true&quot; : &quot;false&quot;);

  return 0;
}
