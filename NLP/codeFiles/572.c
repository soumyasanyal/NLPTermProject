#include &lt;stdio.h&gt;
void vc(int n, int base, int *num, int *denom)
{
        int p = 0, q = 1;

        while (n) {
                p = p * base + (n % base);
                q *= base;
                n /= base;
        }

        *num = p;  
        *denom = q;

        while (p) { n = p; p = q % p; q = n; }
        *num /= q;
        *denom /= q;
}

int main()
{
        int d, n, i, b;
        for (b = 2; b &lt; 6; b++) {
                printf(&quot;base %d:&quot;, b);
                for (i = 0; i &lt; 10; i++) {
                        vc(i, b, &amp;n, &amp;d);
                        if (n) printf(&quot;  %d/%d&quot;, n, d);
                        else   printf(&quot;  0&quot;);
                }
                printf(&quot;\n&quot;);
        }

        return 0;
}
