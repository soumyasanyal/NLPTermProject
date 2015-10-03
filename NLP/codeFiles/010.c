#include &lt;stdio.h&gt;
int ackermann(int m, int n)
{
        if (!m) return n + 1;
        if (!n) return ackermann(m - 1, 1);
        return ackermann(m - 1, ackermann(m, n - 1));
}

int main()
{
        int m, n;
        for (m = 0; m &lt;= 4; m++)
                for (n = 0; n &lt; 6 - m; n++)
                        printf(&quot;A(%d, %d) = %d\n&quot;, m, n, ackermann(m, n));

        return 0;
}
