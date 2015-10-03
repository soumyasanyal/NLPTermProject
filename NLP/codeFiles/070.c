#include &lt;stdio.h&gt;/* gcc -shared -nostartfiles fakeimglib.c -o fakeimglib.so */
int openimage(const char *s)
{
  static int handle = 100;
  fprintf(stderr, &quot;opening %s\n&quot;, s);
  return handle++;
}
