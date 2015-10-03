#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char *sconcat(const char *s1, const char *s2)
{
  char *s0 = (char *)malloc(strlen(s1)+strlen(s2)+1);
  strcpy(s0, s1);
  strcat(s0, s2);
  return s0;
}

int main()
{
   const char *s = &quot;hello&quot;;
   char *s2;
   
   printf(&quot;%s literal\n&quot;, s);
   /* or */
   printf(&quot;%s%s\n&quot;, s, &quot; literal&quot;);
   
   s2 = sconcat(s, &quot; literal&quot;);
   puts(s2);
   free(s2);
}
