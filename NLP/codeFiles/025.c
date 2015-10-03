#include &lt;complex.h&gt;#include &lt;stdio.h&gt;

void cprint(double complex c)
{
  printf(&quot;%f%+fI&quot;, creal(c), cimag(c));
}
void complex_operations() {
  double complex a = 1.0 + 1.0I;
  double complex b = 3.14159 + 1.2I;

  double complex c;

  printf(&quot;\na=&quot;); cprint(a);
  printf(&quot;\nb=&quot;); cprint(b);

  // addition
  c = a + b;
  printf(&quot;\na+b=&quot;); cprint(c);
  // multiplication
  c = a * b;
  printf(&quot;\na*b=&quot;); cprint(c);
  // inversion
  c = 1.0 / a;
  printf(&quot;\n1/c=&quot;); cprint(c);
  // negation
  c = -a;
  printf(&quot;\n-a=&quot;); cprint(c);
  // conjugate
  c = conj(a);
  printf(&quot;\nconj a=&quot;); cprint(c); printf(&quot;\n&quot;);
}
