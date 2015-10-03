void roots_quadratic_eq2(double a, double b, double c, complex double *x){
  b /= a;
  c /= a;
  double delta = b*b - 4*c;
  if ( delta &lt; 0 ) {
    x[0] = -b/2 + I*sqrt(-delta)/2.0;
    x[1] = -b/2 - I*sqrt(-delta)/2.0;
  } else {
    double root = sqrt(delta);
    double sol = (b&gt;0) ? (-b - root)/2.0 : (-b + root)/2.0;
    x[0] = sol;
    x[1] = c/sol;
  }
}
