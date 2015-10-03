#include &lt;stdio.h&gt;#include &lt;unistd.h&gt;

int main()
{
  unsigned int seconds;
  scanf(&quot;%u&quot;, &amp;seconds);
  printf(&quot;Sleeping...\n&quot;);
  sleep(seconds);
  printf(&quot;Awake!\n&quot;);
  return 0;
}
