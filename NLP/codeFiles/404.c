#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdbool.h&gt;
#include &lt;math.h&gt;

typedef struct quaternion
{
  double q[4];
} quaternion_t;


quaternion_t *quaternion_new(void)
{
  return malloc(sizeof(quaternion_t));
}

quaternion_t *quaternion_new_set(double q1,
				 double q2,
				 double q3,
				 double q4)
{
  quaternion_t *q = malloc(sizeof(quaternion_t));
  if (q != NULL) {
    q-&gt;q[0] = q1; q-&gt;q[1] = q2; q-&gt;q[2] = q3; q-&gt;q[3] = q4;
  }
  return q;
}


void quaternion_copy(quaternion_t *r, quaternion_t *q)
{
  size_t i;

  if (r == NULL || q == NULL) return;
  for(i = 0; i &lt; 4; i++) r-&gt;q[i] = q-&gt;q[i];
}


double quaternion_norm(quaternion_t *q)
{
  size_t i;
  double r = 0.0;
  
  if (q == NULL) {
    fprintf(stderr, &quot;NULL quaternion in norm\n&quot;);
    return 0.0;
  }

  for(i = 0; i &lt; 4; i++) r += q-&gt;q[i] * q-&gt;q[i];
  return sqrt(r);
}


void quaternion_neg(quaternion_t *r, quaternion_t *q)
{
  size_t i;

  if (q == NULL || r == NULL) return;
  for(i = 0; i &lt; 4; i++) r-&gt;q[i] = -q-&gt;q[i];
}


void quaternion_conj(quaternion_t *r, quaternion_t *q)
{
  size_t i;

  if (q == NULL || r == NULL) return;
  r-&gt;q[0] = q-&gt;q[0];
  for(i = 1; i &lt; 4; i++) r-&gt;q[i] = -q-&gt;q[i];
}


void quaternion_add_d(quaternion_t *r, quaternion_t *q, double d)
{
  if (q == NULL || r == NULL) return;
  quaternion_copy(r, q);
  r-&gt;q[0] += d;
}


void quaternion_add(quaternion_t *r, quaternion_t *a, quaternion_t *b)
{
  size_t i;

  if (r == NULL || a == NULL || b == NULL) return;
  for(i = 0; i &lt; 4; i++) r-&gt;q[i] = a-&gt;q[i] + b-&gt;q[i];
}


void quaternion_mul_d(quaternion_t *r, quaternion_t *q, double d)
{
  size_t i;

  if (r == NULL || q == NULL) return;
  for(i = 0; i &lt; 4; i++) r-&gt;q[i] = q-&gt;q[i] * d;
}

bool quaternion_equal(quaternion_t *a, quaternion_t *b)
{
  size_t i;
  
  for(i = 0; i &lt; 4; i++) if (a-&gt;q[i] != b-&gt;q[i]) return false;
  return true;
}


#define A(N) (a-&gt;q[(N)])
#define B(N) (b-&gt;q[(N)])
#define R(N) (r-&gt;q[(N)])
void quaternion_mul(quaternion_t *r, quaternion_t *a, quaternion_t *b)
{
  size_t i;
  double ri = 0.0;

  if (r == NULL || a == NULL || b == NULL) return;
  R(0) = A(0)*B(0) - A(1)*B(1) - A(2)*B(2) - A(3)*B(3);
  R(1) = A(0)*B(1) + A(1)*B(0) + A(2)*B(3) - A(3)*B(2);
  R(2) = A(0)*B(2) - A(1)*B(3) + A(2)*B(0) + A(3)*B(1);
  R(3) = A(0)*B(3) + A(1)*B(2) - A(2)*B(1) + A(3)*B(0);
}
#undef A
#undef B
#undef R


void quaternion_print(quaternion_t *q)
{
  if (q == NULL) return;
  printf(&quot;(%lf, %lf, %lf, %lf)\n&quot;, 
	 q-&gt;q[0], q-&gt;q[1], q-&gt;q[2], q-&gt;q[3]);
}
