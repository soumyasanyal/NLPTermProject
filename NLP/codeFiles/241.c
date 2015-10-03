#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;limits.h&gt;
#include &lt;unistd.h&gt;
 
int main(void)
{
 char name[_POSIX_HOST_NAME_MAX + 1];
 return gethostname(name, sizeof name) == -1 || printf(&quot;%s\n&quot;, name) &lt; 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
