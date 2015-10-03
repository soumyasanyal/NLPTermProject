#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;time.h&gt;
#define MAX_BUF 50

int main(void)
{
  char buf[MAX_BUF];
  time_t seconds = time(NULL);
  struct tm *now = localtime(&amp;seconds);
  const char *months[] = {&quot;January&quot;, &quot;February&quot;, &quot;March&quot;, &quot;April&quot;, &quot;May&quot;, &quot;June&quot;,
                          &quot;July&quot;, &quot;August&quot;, &quot;September&quot;, &quot;October&quot;, &quot;November&quot;, &quot;December&quot;};

  const char *days[] = {&quot;Sunday&quot;, &quot;Monday&quot;, &quot;Tuesday&quot;, &quot;Wednesday&quot;,&quot;Thursday&quot;,&quot;Friday&quot;,&quot;Saturday&quot;};

  (void) printf(&quot;%d-%d-%d\n&quot;, now-&gt;tm_year + 1900, now-&gt;tm_mon + 1, now-&gt;tm_mday);
  (void) printf(&quot;%s, %s %d, %d\n&quot;,days[now-&gt;tm_wday], months[now-&gt;tm_mon],
               now-&gt;tm_mday, now-&gt;tm_year + 1900);
  /* using the strftime (the result depends on the locale) */
  (void) strftime(buf, MAX_BUF, &quot;%A, %B %e, %Y&quot;, now);
  (void) printf(&quot;%s\n&quot;, buf);
  return EXIT_SUCCESS;
}
