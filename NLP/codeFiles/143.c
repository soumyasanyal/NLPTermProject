#include &lt;setjmp.h&gt; 
enum { MY_EXCEPTION = 1 }; /* any non-zero number */
 
jmp_buf env;
 
void foo()
{
  longjmp(env, MY_EXCEPTION); /* throw MY_EXCEPTION */
}
 
void call_foo()
{
  switch (setjmp(env)) {
  case 0:                     /* try */
    foo();
    break;
  case MY_EXCEPTION:          /* catch MY_EXCEPTION */
    /* handle exceptions of type MY_EXCEPTION */
    break;
  default:
    /* handle any type of exception not handled by above catches */
    /* note: if this &quot;default&quot; section is not included, that would be equivalent to a blank &quot;default&quot; section */
    /* i.e. any exception not caught above would be caught and ignored */
    /* there is no way to &quot;let the exception through&quot; */
  }
}
