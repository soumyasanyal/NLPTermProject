#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;

char *rtrim(const char *s)
{
  while( isspace(*s) || !isprint(*s) ) ++s;
  return strdup(s);
}

char *ltrim(const char *s)
{
  char *r = strdup(s);
  if (r != NULL)
  {
    char *fr = r + strlen(s) - 1;
    while( (isspace(*fr) || !isprint(*fr) || *fr == 0) &amp;&amp; fr &gt;= r) --fr;
    *++fr = 0;
  }
  return r;
}

char *trim(const char *s)
{
  char *r = rtrim(s);
  char *f = ltrim(r);
  free(r);
  return f;
}

const char *a = &quot;     this is a string      &quot;;

int main()
{
  char *b = rtrim(a);
  char *c = ltrim(a);
  char *d = trim(a);

  printf(&quot;'%s'\n'%s'\n'%s'\n&quot;, b, c, d);
  
  free(b);
  free(c);
  free(d);
  return 0;
}
