#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

long getFileSize(const char *filename)
{
  long result;
  FILE *fh = fopen(filename, &quot;rb&quot;);
  fseek(fh, 0, SEEK_END);
  result = ftell(fh);
  fclose(fh);
  return result;
}

int main(void)
{
  printf(&quot;%ld\n&quot;, getFileSize(&quot;input.txt&quot;));
  printf(&quot;%ld\n&quot;, getFileSize(&quot;/input.txt&quot;));
  return 0;
}
