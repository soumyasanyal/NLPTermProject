#include &lt;stdio.h&gt;
int main()
{
    double inf = 1/0.0;
    double minus_inf = -1/0.0;
    double minus_zero = -1/ inf ;
    double nan = 0.0/0.0;

    printf(&quot;positive infinity: %f\n&quot;,inf);
    printf(&quot;negative infinity: %f\n&quot;,minus_inf);
    printf(&quot;negative zero: %f\n&quot;,minus_zero);
    printf(&quot;not a number: %f\n&quot;,nan);

    /* some arithmetic */

    printf(&quot;+inf + 2.0 = %f\n&quot;,inf + 2.0);
    printf(&quot;+inf - 10.1 = %f\n&quot;,inf - 10.1);
    printf(&quot;+inf + -inf = %f\n&quot;,inf + minus_inf);
    printf(&quot;0.0 * +inf = %f\n&quot;,0.0 * inf);
    printf(&quot;1.0/-0.0 = %f\n&quot;,1.0/minus_zero);
    printf(&quot;NaN + 1.0 = %f\n&quot;,nan + 1.0);
    printf(&quot;NaN + NaN = %f\n&quot;,nan + nan);

    /* some comparisons */

    printf(&quot;NaN == NaN = %s\n&quot;,nan == nan ? &quot;true&quot; : &quot;false&quot;);
    printf(&quot;0.0 == -0.0 = %s\n&quot;,0.0 == minus_zero ? &quot;true&quot; : &quot;false&quot;);

    return 0;
}
