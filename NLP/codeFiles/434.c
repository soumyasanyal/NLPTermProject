#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char * char_repeat( int n, char c ) {
  char * dest = malloc(n+1);
  memset(dest, c, n);
  dest[n] = '\0';
  return dest;
}

int main() {
  char * result = char_repeat(5, '*');
  puts(result);
  free(result);
  return 0;
}
