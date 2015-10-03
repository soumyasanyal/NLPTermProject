#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main(int argc, char *argv[])
{
  int a, b;
  if (argc &lt; 3) exit(1);
  b = atoi(argv[--argc]);
  if (b == 0) exit(2);
  a = atoi(argv[--argc]);
  printf(&quot;a+b = %d\n&quot;, a+b);
  printf(&quot;a-b = %d\n&quot;, a-b);
  printf(&quot;a*b = %d\n&quot;, a*b);
  printf(&quot;a/b = %d\n&quot;, a/b); /* truncates towards 0 (in C99) */
  printf(&quot;a%%b = %d\n&quot;, a%b); /* same sign as first operand (in C99) */
  return 0;
}
