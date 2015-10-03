#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;openssl/sha.h&gt;

int main()
{
  int i;
  unsigned char result[SHA_DIGEST_LENGTH];
  const char *string = &quot;Rosetta Code&quot;;
 
  SHA1(string, strlen(string), result);
 
  for(i = 0; i &lt; SHA_DIGEST_LENGTH; i++)
    printf(&quot;%02x%c&quot;, result[i], i &lt; (SHA_DIGEST_LENGTH-1) ? ' ' : '\n');
 
  return EXIT_SUCCESS;
}
