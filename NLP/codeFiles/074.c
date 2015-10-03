#include &lt;string.h&gt;#include &lt;stdio.h&gt;

int startsWith(char* container, char* target)
{
  size_t clen = strlen(container), tlen = strlen(target);
  if (clen &lt; tlen)
    return 0;
  return strncmp(container, target, tlen) == 0;
}

int endsWith(char* container, char* target)
{
  size_t clen = strlen(container), tlen = strlen(target);
  if (clen &lt; tlen)
    return 0;
  return strncmp(container + clen - tlen, target, tlen) == 0;
}

int doesContain(char* container, char* target)
{
  return strstr(container, target) != 0;
}

int main(void)
{
  printf(&quot;Starts with Test ( Hello,Hell ) : %d\n&quot;, startsWith(&quot;Hello&quot;,&quot;Hell&quot;));
  printf(&quot;Ends with Test ( Code,ode ) : %d\n&quot;, endsWith(&quot;Code&quot;,&quot;ode&quot;));
  printf(&quot;Contains Test ( Google,msn ) : %d\n&quot;, doesContain(&quot;Google&quot;,&quot;msn&quot;));

  return 0;
}
