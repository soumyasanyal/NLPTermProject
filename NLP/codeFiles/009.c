#include &lt;stdio.h&gt;//~ Take a number n and return a function that takes a number i
#define ACCUMULATOR(name,n) __typeof__(n) name (__typeof__(n) i) { \
    static __typeof__(n) _n=n; LOGIC; }
//~ have it return n incremented by the accumulation of i
#define LOGIC return _n+=i
ACCUMULATOR(x,1.0)
ACCUMULATOR(y,3)
ACCUMULATOR(z,'a')
#undef LOGIC
int main (void) {
    printf (&quot;%f\n&quot;, x(5));   /* 6.000000 */
    printf (&quot;%f\n&quot;, x(2.3)); /* 8.300000 */
    printf (&quot;%i\n&quot;, y(5.0)); /* 8 */
    printf (&quot;%i\n&quot;, y(3.3)); /* 11 */
    printf (&quot;%c\n&quot;, z(5));   /* f */
    return 0;
}
