#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

int main(void)
{
  char filename[] = &quot;/tmp/prefixXXXXXX&quot;;
  int fd = mkstemp(filename);
  puts(filename);
  /* do stuff with file descriptor &quot;fd&quot; */
  close(fd);
  return 0;
}
