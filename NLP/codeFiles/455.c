#include &lt;stdio.h&gt;#include &lt;string.h&gt;

const char *haystack[] = {
  &quot;Zig&quot;, &quot;Zag&quot;, &quot;Wally&quot;, &quot;Ronald&quot;, &quot;Bush&quot;, &quot;Krusty&quot;, &quot;Charlie&quot;,
  &quot;Bush&quot;, &quot;Boz&quot;, &quot;Zag&quot;, NULL
};

int search_needle(const char *needle, const char **hs)
{
  int i = 0;
  while( hs[i] != NULL ) {
    if ( strcmp(hs[i], needle) == 0 ) return i;
    i++;
  }
  return -1;
}

int search_last_needle(const char *needle, const char **hs)
{
  int i, last=0;
  i = last = search_needle(needle, hs);
  if ( last &lt; 0 ) return -1;
  while( hs[++i] != NULL ) {
    if ( strcmp(needle, hs[i]) == 0 ) {
      last = i;
    }
  }
  return last;
}

int main()
{
  printf(&quot;Bush is at %d\n&quot;, search_needle(&quot;Bush&quot;, haystack));
  if ( search_needle(&quot;Washington&quot;, haystack) == -1 )
    printf(&quot;Washington is not in the haystack\n&quot;);
  printf(&quot;First index for Zag: %d\n&quot;, search_needle(&quot;Zag&quot;, haystack));
  printf(&quot;Last index for Zag: %d\n&quot;, search_last_needle(&quot;Zag&quot;, haystack));
  return 0;
}
