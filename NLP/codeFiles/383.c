#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#include &lt;plot.h&gt;

#define NP 10
double x[NP] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
double y[NP] = {2.7, 2.8, 31.4, 38.1, 58.0, 76.2, 100.5, 130.0, 149.3, 180.0};

void minmax(double *x, double *y,
	    double *minx, double *maxx, 
	    double *miny, double *maxy, int n)
{
  int i;

  *minx = *maxx = x[0];
  *miny = *maxy = y[0];
  for(i=1; i &lt; n; i++) {
    if ( x[i] &lt; *minx ) *minx = x[i];
    if ( x[i] &gt; *maxx ) *maxx = x[i];
    if ( y[i] &lt; *miny ) *miny = y[i];
    if ( y[i] &gt; *maxy ) *maxy = y[i];
  }
}

/* likely we must play with this parameter to make the plot looks better
   when using different set of data */
#define YLAB_HEIGHT_F 0.1
#define XLAB_WIDTH_F 0.2  
#define XDIV (NP*1.0)
#define YDIV (NP*1.0)
#define EXTRA_W 0.01
#define EXTRA_H 0.01
#define DOTSCALE (1.0/150.0)

#define MAXLABLEN 32

#define PUSHSCALE(X,Y) pl_fscale((X),(Y))
#define POPSCALE(X,Y)  pl_fscale(1.0/(X), 1.0/(Y))
#define FMOVESCALE(X,Y) pl_fmove((X)/sx, (Y)/sy)

int main()
{
  int plotter, i;
  double minx, miny, maxx, maxy;
  double lx, ly;
  double xticstep, yticstep, nx, ny;
  double sx, sy;
  
  char labs[MAXLABLEN+1];

  plotter = pl_newpl(&quot;png&quot;, NULL, stdout, NULL);
  if ( plotter &lt; 0 ) exit(1);
  pl_selectpl(plotter);
  if ( pl_openpl() &lt; 0 ) exit(1);

  /* determines minx, miny, maxx, maxy */
  minmax(x, y, &amp;minx, &amp;maxx, &amp;miny, &amp;maxy, NP);

  lx = maxx - minx;
  ly = maxy - miny;
  pl_fspace(floor(minx) - XLAB_WIDTH_F * lx, floor(miny) - YLAB_HEIGHT_F * ly,
	    ceil(maxx) + EXTRA_W * lx, ceil(maxy) + EXTRA_H * ly);
  
  /* compute x,y-ticstep */
  xticstep = (ceil(maxx) - floor(minx)) / XDIV;
  yticstep = (ceil(maxy) - floor(miny)) / YDIV;

  pl_flinewidth(0.25);

  /* compute scale factors to adjust aspect */
  if ( lx &lt; ly ) {
    sx = lx/ly;
    sy = 1.0;
  } else {
    sx = 1.0;
    sy = ly/lx;
  }

  pl_erase();

  /* a frame... */
  pl_fbox(floor(minx), floor(miny),
	  ceil(maxx), ceil(maxy));

  /* labels and &quot;tics&quot; */
  pl_fontname(&quot;HersheySerif&quot;);
  for(ny=floor(miny); ny &lt; ceil(maxy); ny += yticstep) {
    pl_fline(floor(minx), ny, ceil(maxx), ny);
    snprintf(labs, MAXLABLEN, &quot;%6.2lf&quot;, ny);
    FMOVESCALE(floor(minx) - XLAB_WIDTH_F * lx, ny);
    PUSHSCALE(sx,sy);
    pl_label(labs);
    POPSCALE(sx,sy);
  }
  for(nx=floor(minx); nx &lt; ceil(maxx); nx += xticstep) {
    pl_fline(nx, floor(miny), nx, ceil(maxy));
    snprintf(labs, MAXLABLEN, &quot;%6.2lf&quot;, nx);
    FMOVESCALE(nx, floor(miny));
    PUSHSCALE(sx,sy);
    pl_ftextangle(-90);
    pl_alabel('l', 'b', labs);
    POPSCALE(sx,sy);
  }

  /* plot data &quot;point&quot; */
  pl_fillcolorname(&quot;red&quot;);
  pl_filltype(1);
  for(i=0; i &lt; NP; i++)
  {
    pl_fbox(x[i] - lx * DOTSCALE, y[i] - ly * DOTSCALE,
            x[i] + lx * DOTSCALE, y[i] + ly * DOTSCALE);
  }

  pl_flushpl();
  pl_closepl();
}
