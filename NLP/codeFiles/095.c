#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef unsigned long long ULONG;

ULONG get_prime(int idx)
{
        static long n_primes = 0, alloc = 0;
        static ULONG *primes = 0;
        ULONG last, p;
        int i;

        if (idx &gt;= n_primes) {
                if (n_primes &gt;= alloc) {
                        alloc += 16; /* be conservative */
                        primes = realloc(primes, sizeof(ULONG) * alloc);
                }
                if (!n_primes) {
                        primes[0] = 2;
                        primes[1] = 3;
                        n_primes = 2;
                }

                last = primes[n_primes-1];
                while (idx &gt;= n_primes) {
                        last += 2;
                        for (i = 0; i &lt; n_primes; i++) {
                                p = primes[i];
                                if (p * p &gt; last) {
                                        primes[n_primes++] = last;
                                        break;
                                }
                                if (last % p == 0) break;
                        }
                }
        }
        return primes[idx];
}

int main()
{
        ULONG n, x, p;
        int i, first;

        for (x = 1; ; x++) {
                printf(&quot;%lld = &quot;, n = x);

                for (i = 0, first = 1; ; i++) {
                        p = get_prime(i);
                        while (n % p == 0) {
                                n /= p;
                                if (!first) printf(&quot; x &quot;);
                                first = 0;
                                printf(&quot;%lld&quot;, p);
                        }
                        if (n &lt;= p * p) break;
                }

                if (first)      printf(&quot;%lld\n&quot;, n);
                else if (n &gt; 1) printf(&quot; x %lld\n&quot;, n);
                else            printf(&quot;\n&quot;);
        }
        return 0;
}
