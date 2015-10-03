#include &lt;math.h&gt;#include &lt;stdio.h&gt;
#include &lt;assert.h&gt;

int nonsqr(int n) {
    return n + (int)(0.5 + sqrt(n));
    /* return n + (int)round(sqrt(n)); in C99 */
}

int main() {
    int i;
    
    /* first 22 values (as a list) has no squares: */
    for (i = 1; i &lt; 23; i++)
        printf(&quot;%d &quot;, nonsqr(i));
    printf(&quot;\n&quot;);
    
    /* The following check shows no squares up to one million: */
    for (i = 1; i &lt; 1000000; i++) {
        double j = sqrt(nonsqr(i));
        assert(j != floor(j));
    }
    return 0;
}
