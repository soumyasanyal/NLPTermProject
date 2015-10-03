#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

#define STACK_TRACE_ON /* compile in these &quot;stack_trace&quot; routines */
#include &quot;stack_trace.h&quot;

void inner(int k)
BEGIN(inner)
   print_indent(); printf(&quot;*** Now dump the stack ***\n&quot;);
   print_stack_trace();
END
 
void middle(int x, int y)
BEGIN(middle)
  inner(x*y);
END
 
void outer(int a, int b, int c)
BEGIN(outer)
  middle(a+b, b+c);
END
 
int main()
BEGIN(main)
  stack_trace.on = TRUE; /* turn on runtime tracing */
  outer(2,3,5);
  stack_trace.on = FALSE;
  RETURN(EXIT_SUCCESS);
END
