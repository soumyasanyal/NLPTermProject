#include &lt;stdio.h&gt;main(){
  float r=7.125;
  printf(&quot; %9.3f\n&quot;,-r);
  printf(&quot; %9.3f\n&quot;,r);
  printf(&quot; %-9.3f\n&quot;,r);
  printf(&quot; %09.3f\n&quot;,-r);
  printf(&quot; %09.3f\n&quot;,r);
  printf(&quot; %-09.3f\n&quot;,r);
  return 0;
}
