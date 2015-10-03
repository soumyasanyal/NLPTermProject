#include &quot;stdio.h&quot;#include &quot;math.h&quot;

int perfect(int n) {
    int max = (int)sqrt((double)n) + 1;
    int tot = 1;
    int i;

    for (i = 2; i &lt; max; i++)
        if ( (n % i) == 0 ) {
            tot += i;
            int q = n / i;
            if (q &gt; i)
                tot += q;
        }

    return tot == n;
}

int main() {
    int n;
    for (n = 2; n &lt; 33550337; n++)
        if (perfect(n))
            printf(&quot;%d\n&quot;, n);

    return 0;
}
