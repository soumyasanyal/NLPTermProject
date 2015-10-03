#include &lt;fcntl.h&gt;#include &lt;signal.h&gt;
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
/* unistd for sleep */

void sigint_handler(int sig)
{
   fprintf(stderr, &quot;Caught signal %d.\n&quot;, sig);
   unlink(&quot;/tmp/MyUniqueName&quot;);
   /* exit() is not safe in a signal handler, use _exit() */
   _exit(1);
}

int main()
{
   struct sigaction act;
   int myfd;
   
   myfd = open(&quot;/tmp/MyUniqueName&quot;, O_CREAT|O_EXCL);
   if ( myfd &lt; 0 )
   {
      fprintf(stderr, &quot;I am already running!\n&quot;);
      exit(1);
   }
   act.sa_handler = sigint_handler;
   sigemptyset(&amp;act.sa_mask);
   act.sa_flags = 0;
   sigaction(SIGINT, &amp;act, NULL);
   /* here the real code of the app*/
   sleep(20);
   /* end of the app */
   unlink(&quot;/tmp/MyUniqueName&quot;); close(myfd);
   return 0;
}
