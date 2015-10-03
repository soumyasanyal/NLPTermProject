#include &lt;stdio.h&gt;
int main(int argc, char **argv) {
  FILE *in, *out;
  int c;

  in = fopen(&quot;input.txt&quot;, &quot;r&quot;);
  if (!in) {
    fprintf(stderr, &quot;Error opening input.txt for reading.\n&quot;);
    return 1;
  }

  out = fopen(&quot;output.txt&quot;, &quot;w&quot;);
  if (!out) {
    fprintf(stderr, &quot;Error opening output.txt for writing.\n&quot;);
    fclose(in);
    return 1;
  }

  while ((c = fgetc(in)) != EOF) {
    fputc(c, out);
  }

  fclose(out);
  fclose(in);
  return 0;
}
