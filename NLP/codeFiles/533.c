#include &lt;stddef.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char *substring(const char *s, size_t n, ptrdiff_t m)
{
  char *result;
  /* check for null s */
  if (NULL == s)
    return NULL;
  /* negative m to mean 'up to the mth char from right' */
  if (m &lt; 0) 
    m = strlen(s) + m - n + 1;

  /* n &lt; 0 or m &lt; 0 is invalid */
  if (n &lt; 0 || m &lt; 0)
    return NULL;

  /* make sure string does not end before n 
   * and advance the &quot;s&quot; pointer to beginning of substring */
  for ( ; n &gt; 0; s++, n--)
    if (*s == '\0')
      /* string ends before n: invalid */
      return NULL;

  result = malloc(m+1);
  if (NULL == result)
    /* memory allocation failed */
    return NULL;
  result[0]=0;
  strncat(result, s, m); /* strncat() will automatically add null terminator
                          * if string ends early or after reading m characters */
  return result;
}

char *str_wholeless1(const char *s)
{
  return substring(s, 0, strlen(s) - 1);
}

char *str_fromch(const char *s, int ch, ptrdiff_t m)
{
  return substring(s, strchr(s, ch) - s, m);
}

char *str_fromstr(const char *s, char *in, ptrdiff_t m)
{
  return substring(s, strstr(s, in) - s , m);
}


#define TEST(A) do {		\
    char *r = (A);		\
    if (NULL == r)		\
      puts(&quot;--error--&quot;);	\
    else {			\
      puts(r);			\
      free(r);			\
    }				\
  } while(0)

int main()
{
  const char *s = &quot;hello world shortest program&quot;;

  TEST( substring(s, 12, 5) );		// get &quot;short&quot;
  TEST( substring(s, 6, -1) );		// get &quot;world shortest program&quot;
  TEST( str_wholeless1(s) );		// &quot;... progra&quot;
  TEST( str_fromch(s, 'w', 5) );	// &quot;world&quot;
  TEST( str_fromstr(s, &quot;ro&quot;, 3) );	// &quot;rog&quot;

  return 0;
}
