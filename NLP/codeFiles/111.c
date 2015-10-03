#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#include &lt;complex.h&gt;
 
double PI;
typedef double complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step &lt; n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i &lt; n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i &lt; n; i++) out[i] = buf[i];
	_fft(buf, out, n, 1);
}

/* pad array length to power of two */
cplx *pad_two(double g[], int len, int *ns)
{
	int n = 1;
	if (*ns) n = *ns;
	else while (n &lt; len) n *= 2;

	cplx *buf = calloc(sizeof(cplx), n);
	for (int i = 0; i &lt; len; i++) buf[i] = g[i];
	*ns = n;
	return buf;
}

void deconv(double g[], int lg, double f[], int lf, double out[]) {
	int ns = 0;
	cplx *g2 = pad_two(g, lg, &amp;ns);
	cplx *f2 = pad_two(f, lf, &amp;ns);

	fft(g2, ns);
	fft(f2, ns);

	cplx h[ns];
	for (int i = 0; i &lt; ns; i++) h[i] = g2[i] / f2[i];
	fft(h, ns);

	for (int i = 0; i &gt;= lf - lg; i--)
		out[-i] = h[(i + ns) % ns]/32;
	free(g2);
	free(f2);
}

int main()
{
	PI = atan2(1,1) * 4;
	double g[] = {24,75,71,-34,3,22,-45,23,245,25,52,25,-67,-96,96,31,55,36,29,-43,-7};
	double f[] = { -3,-6,-1,8,-6,3,-1,-9,-9,3,-2,5,2,-2,-7,-1 };
	double h[] = { -8,-9,-3,-1,-6,7 };

	int lg = sizeof(g)/sizeof(double);
	int lf = sizeof(f)/sizeof(double);
	int lh = sizeof(h)/sizeof(double);

	double h2[lh];
	double f2[lf];

	printf(&quot;f[] data is : &quot;);
	for (int i = 0; i &lt; lf; i++) printf(&quot; %g&quot;, f[i]);
	printf(&quot;\n&quot;);

	printf(&quot;deconv(g, h): &quot;);
	deconv(g, lg, h, lh, f2);
	for (int i = 0; i &lt; lf; i++) printf(&quot; %g&quot;, f2[i]);
	printf(&quot;\n&quot;);

	printf(&quot;h[] data is : &quot;);
	for (int i = 0; i &lt; lh; i++) printf(&quot; %g&quot;, h[i]);
	printf(&quot;\n&quot;);

	printf(&quot;deconv(g, f): &quot;);
	deconv(g, lg, f, lf, h2);
	for (int i = 0; i &lt; lh; i++) printf(&quot; %g&quot;, h2[i]);
	printf(&quot;\n&quot;);
}
