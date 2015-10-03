#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
 
typedef struct frame
{
  int (*fn)(struct frame*);
  union { int constant; int* k; } u;
  struct frame *x1, *x2, *x3, *x4, *x5;
} FRAME;

FRAME* Frame(FRAME* f, int* k, FRAME* x1, FRAME* x2, FRAME *x3, FRAME *x4, FRAME *x5)
{
  f-&gt;u.k = k;
  f-&gt;x1 = x1;
  f-&gt;x2 = x2;
  f-&gt;x3 = x3;
  f-&gt;x4 = x4;
  f-&gt;x5 = x5;
  return f;
}

int F(FRAME* a) { return a-&gt;u.constant; }
 
int eval(FRAME* a) { return a-&gt;fn(a); }
 
int A(FRAME*);
 
int B(FRAME* a)
{
  int k = (*a-&gt;u.k -= 1);
  FRAME b = { B };
  return A(Frame(&amp;b, &amp;k, a, a-&gt;x1, a-&gt;x2, a-&gt;x3, a-&gt;x4));
}
 
int A(FRAME* a)
{
  return *a-&gt;u.k &lt;= 0 ? eval(a-&gt;x4) + eval(a-&gt;x5) : B(a);
}

int main(int argc, char** argv)
{
  int k = argc == 2 ? strtol(argv[1], 0, 0) : 10;
  FRAME a = { B }, f1 = { F, { 1 } }, f0 = { F, { 0 } }, fn1 = { F, { -1 } };

  printf(&quot;%d\n&quot;, A(Frame(&amp;a, &amp;k, &amp;f1, &amp;fn1, &amp;fn1, &amp;f1, &amp;f0)));
  return 0;
}
