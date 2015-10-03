#include &lt;stdio.h&gt;
long fib(long x)
{
        long fib_i(long n) { return n &lt; 2 ? n : fib_i(n - 2) + fib_i(n - 1); };
        if (x &lt; 0) {
                printf(&quot;Bad argument: fib(%ld)\n&quot;, x);
                return -1;
        }
        return fib_i(x);
}

long fib_i(long n) /* just to show the fib_i() inside fib() has no bearing outside it */
{
        printf(&quot;This is not the fib you are looking for\n&quot;);
        return -1;
}

int main()
{
        long x;
        for (x = -1; x &lt; 4; x ++)
                printf(&quot;fib %ld = %ld\n&quot;, x, fib(x));

        printf(&quot;calling fib_i from outside fib:\n&quot;);
        fib_i(3);

        return 0;
}
