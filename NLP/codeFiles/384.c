#include &lt;stdio.h&gt;#include &lt;math.h&gt;
#include &lt;string.h&gt;

#define N 40
double x[N], y[N];

void minmax(double x[], int len, double *base, double *step, int *nstep)
{
	int i;
	double diff, minv, maxv;
	*step = 1;

	minv = maxv = x[0];
	for (i = 1; i &lt; len; i++) {
		if (minv &gt; x[i]) minv = x[i];
		if (maxv &lt; x[i]) maxv = x[i];
	}
	if (minv == maxv) {
		minv = floor(minv);
		maxv =  ceil(maxv);
		if (minv == maxv) {
			minv--;
			maxv++;
		}
	} else {
		diff = maxv - minv;
		while (*step &lt; diff) *step *= 10;
		while (*step &gt; diff)	   *step /= 10;
		if (*step &gt; diff / 2)	   *step /= 5;
		else if (*step &gt; diff / 5) *step /= 2;
	}

	*base = floor(minv / *step) * *step;
	*nstep =  ceil(maxv / *step) - floor(minv / *step);
}

/* writes an eps with 400 x 300 dimention, using 12 pt font */
#define CHARH 12
#define CHARW 6
#define DIMX 398
#define DIMY (300 - CHARH)
#define BOTY 20.
int plot(double x[], double y[], int len, char *spec)
{
	int nx, ny, i;
	double sx, sy, x0, y0;
	char buf[100];
	int dx, dy, lx, ly;
	double ofs_x, ofs_y, grid_x;

	minmax(x, len, &amp;x0, &amp;sx, &amp;nx);
	minmax(y, len, &amp;y0, &amp;sy, &amp;ny);

	dx = -log10(sx);
	dy = -log10(sy);

	ly = 0;
	for (i = 0; i &lt;= ny; i++) {
		sprintf(buf, &quot;%g\n&quot;, y0 + i * sy);
		if (strlen(buf) &gt; ly) ly = strlen(buf);
	}
	ofs_x = ly * CHARW;

	printf(&quot;%%!PS-Adobe-3.0\n%%%%BoundingBox: 0 0 400 300\n&quot;
		&quot;/TimesRoman findfont %d scalefont setfont\n&quot;
		&quot;/rl{rlineto}def /l{lineto}def /s{setrgbcolor}def &quot;
		&quot;/rm{rmoveto}def /m{moveto}def /st{stroke}def\n&quot;,
		CHARH);
	for (i = 0; i &lt;= ny; i++) {
		ofs_y = BOTY + (DIMY - BOTY) / ny * i;
		printf(&quot;0 %g m (%*.*f) show\n&quot;,
			ofs_y - 4, ly, dy, y0 + i * sy);
		if (i) printf(&quot;%g %g m 7 0 rl st\n&quot;,
			ofs_x, ofs_y);
	}
	printf(&quot;%g %g m %g %g l st\n&quot;, ofs_x, BOTY, ofs_x, ofs_y);

	for (i = 0; i &lt;= nx; i++) {
		sprintf(buf, &quot;%g&quot;, x0 + i * sx);
		lx = strlen(buf);
		grid_x = ofs_x + (DIMX - ofs_x) / nx * i;

		printf(&quot;%g %g m (%s) show\n&quot;, grid_x - CHARW * lx / 2,
			BOTY - 12, buf);
		if (i) printf(&quot;%g %g m 0 7 rl st\n&quot;, grid_x, BOTY);
	}
	printf(&quot;%g %g m %g %g l st\n&quot;, ofs_x, BOTY, grid_x, BOTY);
		
	if (strchr(spec, 'r'))		printf(&quot;1 0 0 s\n&quot;);
	else if (strchr(spec, 'b'))	printf(&quot;0 0 1 s\n&quot;);
	else if (strchr(spec, 'g'))	printf(&quot;0 1 0 s\n&quot;);
	else if (strchr(spec, 'm'))	printf(&quot;1 0 1 s\n&quot;);

	if (strchr(spec, 'o'))
		printf(&quot;/o { m 0 3 rm 3 -3 rl -3 -3 rl -3 3 rl closepath st} def &quot;
			&quot;.5 setlinewidth\n&quot;);

	if (strchr(spec, '-')) {
		for (i = 0; i &lt; len; i++) {
			printf(&quot;%g %g %s &quot;,
				(x[i] - x0) / (sx * nx) * (DIMX - ofs_x) + ofs_x,
				(y[i] - y0) / (sy * ny) * (DIMY - BOTY) + BOTY,
				i ? &quot;l&quot; : &quot;m&quot;);
		}
		printf(&quot;st\n&quot;);
	}

	if (strchr(spec, 'o'))
		for (i = 0; i &lt; len; i++) {
			printf(&quot;%g %g o &quot;,
				(x[i] - x0) / (sx * nx) * (DIMX - ofs_x) + ofs_x,
				(y[i] - y0) / (sy * ny) * (DIMY - BOTY) + BOTY);
		}

	printf(&quot;showpage\n%%EOF&quot;);
	
	return 0;
}

int main()
{
	int i;
	for (i = 0; i &lt; N; i++) {
		x[i] = (double)i / N * 3.14159 * 6;
		y[i] = -1337 + (exp(x[i] / 10) + cos(x[i])) / 100;
	}
	/* string parts: any of &quot;rgbm&quot;: color; &quot;-&quot;: draw line; &quot;o&quot;: draw symbol */
	plot(x, y, N, &quot;r-o&quot;);
	return 0;
}
