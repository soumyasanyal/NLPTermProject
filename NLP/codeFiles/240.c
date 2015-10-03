#include &lt;stdio.h&gt;#include &lt;arpa/inet.h&gt;

int main()
{
  if (htonl(1) == 1)
    printf(&quot;big endian\n&quot;);
  else
    printf(&quot;little endian\n&quot;);
}
