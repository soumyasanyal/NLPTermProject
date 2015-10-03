#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;openssl/md5.h&gt;

const char *string = &quot;The quick brown fox jumped over the lazy dog's back&quot;;

int main()
{
  int i;
  unsigned char result[MD5_DIGEST_LENGTH];

  MD5(string, strlen(string), result);

  // output
  for(i = 0; i &lt; MD5_DIGEST_LENGTH; i++)
    printf(&quot;%02x&quot;, result[i]);
  printf(&quot;\n&quot;);

  return EXIT_SUCCESS;
}
