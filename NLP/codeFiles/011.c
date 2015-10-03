#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

int m_bits, n_bits;
int *cache;

int ackermann(int m, int n)
{
        int idx, res;
        if (!m) return n + 1;

        if (n &gt;= 1&lt;&lt;n_bits) {
                printf(&quot;%d, %d\n&quot;, m, n);
                idx = 0;
        } else {
                idx = (m &lt;&lt; n_bits) + n;
                if (cache[idx]) return cache[idx];
        }

        if (!n) res = ackermann(m - 1, 1);
        else    res = ackermann(m - 1, ackermann(m, n - 1));

        if (idx) cache[idx] = res;
        return res;
}
int main()
{
        int m, n;

        m_bits = 3;
        n_bits = 20;  /* can save n values up to 2**20 - 1, that's 1 meg */
        cache = malloc(sizeof(int) * (1 &lt;&lt; (m_bits + n_bits)));
        memset(cache, 0, sizeof(int) * (1 &lt;&lt; (m_bits + n_bits)));

        for (m = 0; m &lt;= 4; m++)
                for (n = 0; n &lt; 6 - m; n++) {
                        printf(&quot;A(%d, %d) = %d\n&quot;, m, n, ackermann(m, n));

        return 0;
}
