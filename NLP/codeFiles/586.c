#include &lt;stdio.h&gt;#include &lt;string.h&gt;
#include &lt;curl/curl.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;regex.h&gt;

#define BUFSIZE 16384

size_t lr = 0;

size_t filterit(void *ptr, size_t size, size_t nmemb, void *stream)
{
  if ( (lr + size*nmemb) &gt; BUFSIZE ) return BUFSIZE;
  memcpy(stream+lr, ptr, size*nmemb);
  lr += size*nmemb;
  return size*nmemb;
}

int main()
{
  CURL *curlHandle;
  char buffer[BUFSIZE];
  regmatch_t amatch;
  regex_t cregex;

  curlHandle = curl_easy_init();
  curl_easy_setopt(curlHandle, CURLOPT_URL, &quot;http://tycho.usno.navy.mil/cgi-bin/timer.pl&quot;);
  curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, filterit);
  curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, buffer);
  int success = curl_easy_perform(curlHandle);
  curl_easy_cleanup(curlHandle);

  buffer[lr] = 0;
  
  regcomp(&amp;cregex, &quot; UTC&quot;, REG_NEWLINE);
  regexec(&amp;cregex, buffer, 1, &amp;amatch, 0);
  int bi = amatch.rm_so;
  while ( bi-- &gt; 0 )
    if ( memcmp(&amp;buffer[bi], &quot;&lt;BR&gt;&quot;, 4) == 0 ) break;

  buffer[amatch.rm_eo] = 0;

  printf(&quot;%s\n&quot;, &amp;buffer[bi+4]);

  regfree(&amp;cregex);
  return 0;
}
