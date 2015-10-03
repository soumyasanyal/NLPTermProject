#include &lt;math.h&gt;#include &lt;stdio.h&gt;

double f(double x)
{
    return x*x*x-3.0*x*x +2.0*x;
}

double secant( double xA, double xB, double(*f)(double) )
{
    double e = 1.0e-12;
    double fA, fB;
    double d;
    int i;
    int limit = 50;

    fA=(*f)(xA);
    for (i=0; i&lt;limit; i++) {
        fB=(*f)(xB);
        d = (xB - xA) / (fB - fA) * fB;
        if (fabs(d) &lt; e) 
            break;
        xA = xB;
        fA = fB;
        xB -= d;
    }
    if (i==limit) {
        printf(&quot;Function is not converging near (%7.4f,%7.4f).\n&quot;, xA,xB);
        return -99.0;
    }
    return xB;
}    

int main(int argc, char *argv[])
{
    double step = 1.0e-2;
    double e = 1.0e-12;
    double x = -1.032;		// just so we use secant method
    double xx, value;

    int s = (f(x)&gt; 0.0);

    while (x &lt; 3.0) {
        value = f(x);
        if (fabs(value) &lt; e) {
            printf(&quot;Root found at x= %12.9f\n&quot;, x);
            s = (f(x+.0001)&gt;0.0);
        }
        else if ((value &gt; 0.0) != s) {
            xx = secant(x-step, x,&amp;f);
            if (xx != -99.0)   // -99 meaning secand method failed
                printf(&quot;Root found at x= %12.9f\n&quot;, xx);
            else
                printf(&quot;Root found near x= %7.4f\n&quot;, x);
            s = (f(x+.0001)&gt;0.0);
        }
        x += step;
    }
    return 0;
}
