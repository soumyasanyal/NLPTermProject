#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int hailstone(int n, int *arry)
{
    int hs = 1;

    while (n!=1) {
        hs++;
        if (arry) *arry++ = n;
        n = (n&amp;1) ? (3*n+1) : (n/2);
    }
    if (arry) *arry++ = n;
    return hs;
}

int main()
{
    int j, hmax = 0;
    int jatmax, n;
    int *arry;

    for (j=1; j&lt;100000; j++) {
       n = hailstone(j, NULL);
       if (hmax &lt; n) {
           hmax = n;
           jatmax = j;
       }
    }
    n = hailstone(27, NULL);
    arry = malloc(n*sizeof(int));
    n = hailstone(27, arry);

    printf(&quot;[ %d, %d, %d, %d, ...., %d, %d, %d, %d] len=%d\n&quot;,
        arry[0],arry[1],arry[2],arry[3],
        arry[n-4], arry[n-3], arry[n-2], arry[n-1], n);
    printf(&quot;Max %d at j= %d\n&quot;, hmax, jatmax);
    free(arry);

    return 0;
}
