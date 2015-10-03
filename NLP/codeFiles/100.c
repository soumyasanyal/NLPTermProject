#include &lt;stdio.h&gt;
int main() {
  FILE *fh = fopen(&quot;output.txt&quot;, &quot;w&quot;);
  fclose(fh);

  return 0;
}
