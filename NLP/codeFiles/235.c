#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int a_list[1&lt;&lt;20 + 1];

int doSqnc( int m)
{
    int max_df = 0;
    int p2_max = 2;
    int v, n;
    int k1 = 2;
    int lg2 = 1;
    double amax = 0;
    a_list[0] = -50000;
    a_list[1] = a_list[2] = 1;
    v = a_list[2];

    for (n=3; n &lt;= m;  n++) {
        v = a_list[n] = a_list[v] + a_list[n-v];
        if ( amax &lt; v*1.0/n) amax = v*1.0/n;
        if ( 0 == (k1&amp;n)) {
            printf(&quot;Maximum between 2^%d and 2^%d was %f\n&quot;, lg2,lg2+1, amax);
            amax = 0;
            lg2++;
        }
        k1 = n;
    }
    return 1;
}
