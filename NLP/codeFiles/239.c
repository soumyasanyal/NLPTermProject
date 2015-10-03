#include &lt;stdio.h&gt;#include &lt;stddef.h&gt; /* for size_t */
#include &lt;limits.h&gt; /* for CHAR_BIT */

int main() {
    int one = 1;

    /*
     * Best bet: size_t typically is exactly one word.
     */
    printf(&quot;word size = %d bits\n&quot;, (int)(CHAR_BIT * sizeof(size_t)));

    /*
     * Check if the least significant bit is located
     * in the lowest-address byte.
     */
    if (*(char *)&amp;one)
        printf(&quot;little endian\n&quot;);
    else
        printf(&quot;big endian\n&quot;);
    return 0;
}
