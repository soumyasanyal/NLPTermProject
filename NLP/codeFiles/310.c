#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* Make the data structure self-contained.  Element at row i and col j
   is x[i * w + j].  More often than not, though,  you might want
   to represent a matrix some other way */
typedef struct { int h, w; double *x;} matrix_t, *matrix;

inline double dot(double *a, double *b, int len, int step)
{
	double r = 0;
	while (len--) {
		r += *a++ * *b;
		b += step;
	}
	return r;
}

matrix mat_new(int h, int w)
{
	matrix r = malloc(sizeof(matrix) + sizeof(double) * w * h);
	r-&gt;h = h, r-&gt;w = w;
	r-&gt;x = (double*)(r + 1);
	return r;
}

matrix mat_mul(matrix a, matrix b)
{
	matrix r;
	double *p, *pa;
	int i, j;
	if (a-&gt;w != b-&gt;h) return 0;

	r = mat_new(a-&gt;h, b-&gt;w);
	p = r-&gt;x;
	for (pa = a-&gt;x, i = 0; i &lt; a-&gt;h; i++, pa += a-&gt;w)
		for (j = 0; j &lt; b-&gt;w; j++)
			*p++ = dot(pa, b-&gt;x + j, a-&gt;w, b-&gt;w);
	return r;
}

void mat_show(matrix a)
{
	int i, j;
	double *p = a-&gt;x;
	for (i = 0; i &lt; a-&gt;h; i++, putchar('\n'))
		for (j = 0; j &lt; a-&gt;w; j++)
			printf(&quot;\t%7.3f&quot;, *p++);
	putchar('\n');
}

int main()
{
	double da[] = {	1, 1,  1,   1,
			2, 4,  8,  16,
			3, 9, 27,  81,
			4,16, 64, 256	};
	double db[] = {     4.0,   -3.0,  4.0/3,
			-13.0/3, 19.0/4, -7.0/3,
			  3.0/2,   -2.0,  7.0/6,
			 -1.0/6,  1.0/4, -1.0/6};

	matrix_t a = { 4, 4, da }, b = { 4, 3, db };
	matrix c = mat_mul(&amp;a, &amp;b);

	/* mat_show(&amp;a), mat_show(&amp;b); */
	mat_show(c);
	/* free(c) */
	return 0;
}
