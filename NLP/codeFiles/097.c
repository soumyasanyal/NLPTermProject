#include &lt;stdio.h&gt;#include &lt;string.h&gt;

int match(const char *s, const char *p, int overlap)
{
        int c = 0, l = strlen(p);

        while (*s != '\0') {
                if (strncmp(s++, p, l)) continue;
                if (!overlap) s += l - 1;
                c++;
        }
        return c;
}

int main()
{
        printf(&quot;%d\n&quot;, match(&quot;the three truths&quot;, &quot;th&quot;, 0));
        printf(&quot;overlap:%d\n&quot;, match(&quot;abababababa&quot;, &quot;aba&quot;, 1));
        printf(&quot;not:    %d\n&quot;, match(&quot;abababababa&quot;, &quot;aba&quot;, 0));
        return 0;
}
