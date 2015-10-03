#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#include &lt;gsl/gsl_sf_gamma.h&gt;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* very simple approximation */
double st_gamma(double x)
{
  return sqrt(2.0*M_PI/x)*pow(x/M_E, x);
}

#define A 12
double sp_gamma(double z)
{
  const int a = A;
  static double c_space[A];
  static double *c = NULL;
  int k;
  double accm;
 
  if ( c == NULL ) {
    double k1_factrl = 1.0; /* (k - 1)!*(-1)^k with 0!==1*/
    c = c_space;
    c[0] = sqrt(2.0*M_PI);
    for(k=1; k &lt; a; k++) {
      c[k] = exp(a-k) * pow(a-k, k-0.5) / k1_factrl;
	  k1_factrl *= -k;
    }
  }
  accm = c[0];
  for(k=1; k &lt; a; k++) {
    accm += c[k] / ( z + k );
  }
  accm *= exp(-(z+a)) * pow(z+a, z+0.5); /* Gamma(z+1) */
  return accm/z;
}

int main()
{
  double x;


  printf(&quot;%15s%15s%15s%15s\n&quot;, &quot;Stirling&quot;, &quot;Spouge&quot;, &quot;GSL&quot;, &quot;libm&quot;);
  for(x=1.0; x &lt;= 10.0; x+=1.0) {
    printf(&quot;%15.8lf%15.8lf%15.8lf%15.8lf\n&quot;, st_gamma(x/3.0), sp_gamma(x/3.0), 
	   gsl_sf_gamma(x/3.0), tgamma(x/3.0));
  }
  return 0;
}
