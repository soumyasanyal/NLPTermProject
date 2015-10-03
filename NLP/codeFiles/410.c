#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdbool.h&gt;
 
#include &lt;sys/queue.h&gt;

/* #include &quot;fifolist.h&quot; */

int main()
{
  int i;
  FIFOList head;

  TAILQ_INIT(&amp;head);

  /* insert 20 integer values */
  for(i=0; i &lt; 20; i++) {
    m_enqueue(i, &amp;head);
  }

  /* dequeue and print */
  while( m_dequeue(&amp;i, &amp;head) )
    printf(&quot;%d\n&quot;, i);

  fprintf(stderr, &quot;FIFO list %s\n&quot;,
	  ( m_dequeue(&amp;i, &amp;head) ) ? 
	  &quot;had still an element&quot; :
	  &quot;is void!&quot;);

  exit(0);
}
