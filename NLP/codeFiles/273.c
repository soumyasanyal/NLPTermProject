#include &lt;stdio.h&gt;
int gcd(int m, int n)
{
        int tmp;
        while(m) { tmp = m; m = n % m; n = tmp; }       
        return n;
}

int lcm(int m, int n)
{
        return m / gcd(m, n) * n;
}

int main()
{
        printf(&quot;lcm(35, 21) = %d\n&quot;, lcm(21,35));
        return 0;
}
