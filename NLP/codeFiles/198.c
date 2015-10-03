#include &lt;stdio.h&gt;
#define Swap(X,Y)  do{ __typeof__ (X) _T = X; X = Y; Y = _T; }while(0)

struct test
{
  int a, b, c;
};


int main()
{
  struct test t = { 1, 2, 3 };
  struct test h = { 4, 5, 6 };
  double alfa = 0.45, omega = 9.98;
  
  struct test *pt = &amp;t;
  struct test *th = &amp;h;
  
  printf(&quot;%d %d %d\n&quot;, t.a, t.b, t.c );
  Swap(t, h);
  printf(&quot;%d %d %d\n&quot;, t.a, t.b, t.c );
  printf(&quot;%d %d %d\n&quot;, h.a, h.b, h.c );
  
  printf(&quot;%lf\n&quot;, alfa);
  Swap(alfa, omega);
  printf(&quot;%lf\n&quot;, alfa);
  
  printf(&quot;%d\n&quot;, pt-&gt;a);
  Swap(pt, th);
  printf(&quot;%d\n&quot;, pt-&gt;a);
}
