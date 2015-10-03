#include &lt;string.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

  /* removes all chars from string */
char *strip_chars(char *string, char *chars)
{
  char * newstr = malloc(strlen(string) + 1);
  int counter = 0;

  for ( ; *string; string++) {
    if (!strchr(chars, *string)) {
      newstr[ counter ] = *string;
      ++ counter;
    }
  }

  newstr[counter] = 0;
  return newstr;
}

int main(void)
{
  char *new = strip_chars(&quot;She was a soul stripper. She took my heart!&quot;, &quot;aei&quot;);
  printf(&quot;%s\n&quot;, new);

  free(new);
  return 0;
}
