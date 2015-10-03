#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;sys/stat.h&gt;

int main(void)
{
  struct stat foo;
  stat(&quot;input.txt&quot;, &amp;foo);
  printf(&quot;%ld\n&quot;, foo.st_size);
  stat(&quot;/input.txt&quot;, &amp;foo);
  printf(&quot;%ld\n&quot;, foo.st_size);
  return 0;
}
