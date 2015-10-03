#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char * string_repeat( int n, const char * s ) {
  size_t slen = strlen(s);
  char * dest = malloc(n*slen+1);

  int i; char * p;
  for ( i=0, p = dest; i &lt; n; ++i, p += slen ) {
    memcpy(p, s, slen);
  }
  *p = '\0';
  return dest;
}

int main() {
  char * result = string_repeat(5, &quot;ha&quot;)
  puts(result);
  free(result);
  return 0;
}
