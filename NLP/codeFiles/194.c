#include &lt;stdlib.h&gt;
/* generic interface for functors from double to double */
typedef struct double_to_double {
  double (*fn)(struct double_to_double *, double);
} double_to_double;

#define CALL(f, x) f-&gt;fn(f, x)


/* functor returned by compose */
typedef struct compose_functor {
  double (*fn)(struct compose_functor *, double);
  double_to_double *f;
  double_to_double *g;
} compose_functor;
/* function to be used in &quot;fn&quot; in preceding functor */
double compose_call(compose_functor *this, double x) {
  return CALL(this-&gt;f, CALL(this-&gt;g, x));
}
/* returns functor that is the composition of functors
   f &amp; g. caller is responsible for deallocating memory */
double_to_double *compose(double_to_double *f,
                          double_to_double *g) {
  compose_functor *result = malloc(sizeof(compose_functor));
  result-&gt;fn = &amp;compose_call;
  result-&gt;f = f;
  result-&gt;g = g;
  return (double_to_double *)result;
}



#include &lt;math.h&gt;

/* we can make functors for sin and asin by using 
   the following as &quot;fn&quot; in a functor */
double sin_call(double_to_double *this, double x) {
  return sin(x);
}
double asin_call(double_to_double *this, double x) {
  return asin(x);
}



#include &lt;stdio.h&gt;

int main() {
  double_to_double *my_sin = malloc(sizeof(double_to_double));
  my_sin-&gt;fn = &amp;sin_call;
  double_to_double *my_asin = malloc(sizeof(double_to_double));
  my_asin-&gt;fn = &amp;asin_call;

  double_to_double *sin_asin = compose(my_sin, my_asin);

  printf(&quot;%f\n&quot;, CALL(sin_asin, 0.5)); /* prints &quot;0.500000&quot; */

  free(sin_asin);
  free(my_sin);
  free(my_asin);

  return 0;
}
