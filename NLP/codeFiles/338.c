#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* let us declare our functions; indeed here we need
   really only M declaration, so that F can &quot;see&quot; it
   and the compiler won't complain with a warning */
int F(const int n);
int M(const int n);

int F(const int n)
{
  return (n == 0) ? 1 : n - M(F(n - 1));
}

int M(const int n)
{
  return (n == 0) ? 0 : n - F(M(n - 1));
}

int main(void)
{
  int i;
  for (i = 0; i &lt; 20; i++)
    printf(&quot;%2d &quot;, F(i));
  printf(&quot;\n&quot;);
  for (i = 0; i &lt; 20; i++)
    printf(&quot;%2d &quot;, M(i));
  printf(&quot;\n&quot;);
  return EXIT_SUCCESS;
}
