#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;math.h&gt;

typedef double (*f_dbl)(double);
#define TAGF (f_dbl)0xdeadbeef
#define TAGG (f_dbl)0xbaddecaf

double dummy(double x)
{
	f_dbl f = TAGF;
	f_dbl g = TAGG;
	return f(g(x));
}

f_dbl composite(f_dbl f, f_dbl g)
{
	size_t len = (void*)composite - (void*)dummy;
	f_dbl ret = malloc(len);
	char *ptr;
	memcpy(ret, dummy, len);
	for (ptr = (char*)ret; ptr &lt; (char*)ret + len - sizeof(f_dbl); ptr++) {
		if (*(f_dbl*)ptr == TAGF)      *(f_dbl*)ptr = f;
		else if (*(f_dbl*)ptr == TAGG) *(f_dbl*)ptr = g;
	}
	return ret;
}

double cube(double x)
{
	return x * x * x;
}

/* uncomment next line if your math.h doesn't have cbrt() */
/* double cbrt(double x) { return pow(x, 1/3.); } */

int main()
{
	int i;
	double x;

	f_dbl A[3] = { cube, exp, sin };
	f_dbl B[3] = { cbrt, log, asin}; /* not sure about availablity of cbrt() */
	f_dbl C[3];

	for (i = 0; i &lt; 3; i++)
		C[i] = composite(A[i], B[i]);

	for (i = 0; i &lt; 3; i++) {
		for (x = .2; x &lt;= 1; x += .2)
			printf(&quot;C%d(%g) = %g\n&quot;, i, x, C[i](x));
		printf(&quot;\n&quot;);
	}
	return 0;
}
