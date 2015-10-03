#include &lt;stdio.h&gt;
double horner(double *coeffs, int s, double x)
{
  int i;
  double res = 0.0;
  
  for(i=s-1; i &gt;= 0; i--)
  {
    res = res * x + coeffs[i];
  }
  return res;
}


int main()
{
  double coeffs[] = { -19.0, 7.0, -4.0, 6.0 };
  
  printf(&quot;%5.1f\n&quot;, horner(coeffs, sizeof(coeffs)/sizeof(double), 3.0));
  return 0;
}
