#include &lt;ctype.h&gt;#include &lt;stdlib.h&gt;
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &amp;p);
    return *p == '\0';
}
