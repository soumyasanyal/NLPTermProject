#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;

int main()
{
  struct tm ts;
  time_t t;
  const char *d = &quot;March 7 2009 7:30pm EST&quot;;
  
  strptime(d, &quot;%B %d %Y %I:%M%p %Z&quot;, &amp;ts);
  /* ts.tm_hour += 12; instead of t += 12*60*60
     works too. */
  t = mktime(&amp;ts);
  t += 12*60*60;
  printf(&quot;%s&quot;, ctime(&amp;t));

  return EXIT_SUCCESS;
}
