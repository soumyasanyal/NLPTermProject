/* man-or-boy.c */#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// --- thunks
typedef struct arg
{
  int       (*fn)(struct arg*);
  int        *k;
  struct arg *x1, *x2, *x3, *x4, *x5;
} ARG;

// --- lambdas
int f_1 (ARG* _) { return -1; }
int f0  (ARG* _) { return  0; }
int f1  (ARG* _) { return  1; }

// --- helper
int eval(ARG* a) { return a-&gt;fn(a); }
#define MAKE_ARG(...) (&amp;(ARG){__VA_ARGS__})
#define FUN(...) MAKE_ARG(B, &amp;k, __VA_ARGS__)

int A(ARG*);

// --- functions
int B(ARG* a)
{
  int k = *a-&gt;k -= 1;
  return A(FUN(a, a-&gt;x1, a-&gt;x2, a-&gt;x3, a-&gt;x4));
}

int A(ARG* a)
{
  return *a-&gt;k &lt;= 0 ? eval(a-&gt;x4) + eval(a-&gt;x5) : B(a);
}

int main(int argc, char **argv)
{
  int k = argc == 2 ? strtol(argv[1], 0, 0) : 10;
  printf(&quot;%d\n&quot;, A(FUN(MAKE_ARG(f1), MAKE_ARG(f_1), MAKE_ARG(f_1),
                       MAKE_ARG(f1), MAKE_ARG(f0))));
  return 0;
}
