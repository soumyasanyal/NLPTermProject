#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

int main(int argc, char* argv[])
{
  int i;
  (void) printf(&quot;This program is named %s.\n&quot;, argv[0]);
  for (i = 1; i &lt; argc; ++i)
    (void) printf(&quot;the argument #%d is %s\n&quot;, i, argv[i]);
  return EXIT_SUCCESS;
}
