#include &lt;stdio.h&gt;#include &lt;tgmath.h&gt;

#define VERBOSE 0
#define for3 for(int i = 0; i &lt; 3; i++)

typedef complex double vec;
typedef struct { vec c; double r; } circ;

#define re(x) creal(x)
#define im(x) cimag(x)
#define cp(x) re(x), im(x)
#define CPLX &quot;(%6.3f,%6.3f)&quot;
#define CPLX3 CPLX&quot; &quot;CPLX&quot; &quot;CPLX

double cross(vec a, vec b) { return re(a) * im(b) - im(a) * re(b); }
double abs2(vec a) { return a * conj(a); }
 
int apollonius_in(circ aa[], int ss[], int flip, int divert)
{
	vec n[3], x[3], t[3], a, b, center;
	int s[3], iter = 0, res = 0;
	double diff = 1, diff_old = -1, axb, d, r;
 
	for3 {
		s[i] = ss[i] ? 1 : -1;
		x[i] = aa[i].c;
	}
 
	while (diff &gt; 1e-20) {
		a = x[0] - x[2], b = x[1] - x[2];
		diff = 0;
		axb = -cross(a, b);
		d = sqrt(abs2(a) * abs2(b) * abs2(a - b));

		if (VERBOSE) {
			char *z = 1 + &quot;-0+&quot;;
			printf(&quot;%c%c%c|%c%c|&quot;,
				z[s[0]], z[s[1]], z[s[2]], z[flip], z[divert]);
			printf(CPLX3, cp(x[0]), cp(x[1]), cp(x[2]));
		}

		/* r and center represent an arc through points x[i].  Each step,
		   we'll deform this arc by pushing or pulling some point on it
		   towards the edge of each given circle. */
		r = fabs(d / (2 * axb));
		center = (abs2(a)*b - abs2(b)*a) / (2 * axb) * I + x[2];
 
 		/* maybe the &quot;arc&quot; is actually straight line; then we have two
		   choices in defining &quot;push&quot; and &quot;pull&quot;, so try both */
		if (!axb &amp;&amp; flip != -1 &amp;&amp; !divert) {
			if (!d) { /* generally means circle centers overlap */
				printf(&quot;Given conditions confused me.\n&quot;);
				return 0;
			}

			if (VERBOSE) puts(&quot;\n[divert]&quot;);
			divert = 1;
			res = apollonius_in(aa, ss, -1, 1);
		}

 		/* if straight line, push dir is its norm; else it's away from center */
		for3 n[i] = axb ? aa[i].c - center : a * I * flip;
		for3 t[i] = aa[i].c + n[i] / cabs(n[i]) * aa[i].r * s[i];

		/* diff: how much tangent points have moved since last iteration */
		for3 diff += abs2(t[i] - x[i]), x[i] = t[i];

		if (VERBOSE) printf(&quot; %g\n&quot;, diff);
 
 		/* keep an eye on the total diff: failing to converge means no solution */
		if (diff &gt;= diff_old &amp;&amp; diff_old &gt;= 0)
			if (iter++ &gt; 20) return res;

		diff_old = diff;
	}

	printf(&quot;found: &quot;);
	if (axb) printf(&quot;circle &quot;CPLX&quot;, r = %f\n&quot;, cp(center), r);
	else	 printf(&quot;line &quot;CPLX3&quot;\n&quot;, cp(x[0]), cp(x[1]), cp(x[2]));

	return res + 1;
}
 
int apollonius(circ aa[])
{
	int s[3], i, sum = 0;
	for (i = 0; i &lt; 8; i++) {
		s[0] = i &amp; 1, s[1] = i &amp; 2, s[2] = i &amp; 4;

		/* internal or external results of a zero-radius circle are the same */
		if (s[0] &amp;&amp; !aa[0].r) continue;
		if (s[1] &amp;&amp; !aa[1].r) continue;
		if (s[2] &amp;&amp; !aa[2].r) continue;
		sum += apollonius_in(aa, s, 1, 0);
	}
	return sum;
}
 
int main()
{
	circ a[3] = {{0, 1}, {4, 1}, {2 + 4 * I, 1}};
	circ b[3] = {{-3, 2}, {0, 1}, {3, 2}};
	circ c[3] = {{-2, 1}, {0, 1}, {2 * I, 1}};
	//circ c[3] = {{0, 1}, {0, 2}, {0, 3}}; &lt;-- a fun one
 
	puts(&quot;set 1&quot;); apollonius(a);
	puts(&quot;set 2&quot;); apollonius(b);
	puts(&quot;set 3&quot;); apollonius(c);
}
