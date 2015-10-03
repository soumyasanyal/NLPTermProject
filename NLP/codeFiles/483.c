#include &lt;stdio.h&gt;#include &lt;string.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/socket.h&gt;
#include &lt;netdb.h&gt;

const char *msg = &quot;hello socket world&quot;;

int main()
{
   int i, sock, len, slen;

   struct addrinfo hints, *addrs;  
   memset(&amp;hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   
   if (0 == getaddrinfo(&quot;localhost&quot;, &quot;256&quot;, &amp;hints, &amp;addrs))
   {
       sock = socket(addrs-&gt;ai_family, addrs-&gt;ai_socktype, addrs-&gt;ai_protocol);
       if ( sock &gt;= 0 )
       {
           if ( connect(sock, addrs-&gt;ai_addr, addrs-&gt;ai_addrlen) &gt;= 0 )
           {
               const char *pm = msg;
               do
               {
                  len = strlen(pm);
                  slen = send(sock, pm, len, 0);
                  pm += slen;
               } while ((0 &lt;= slen) &amp;&amp; (slen &lt; len));
           }
           close(sock);
       }
       freeaddrinfo(addrs);
   }
}
