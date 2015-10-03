#include &lt;stdio.h&gt;
/* returns 0 if no match, 1 if matched, -1 if matched and at end */
int s_cmp(char *a, char *b)
{
        char c1 = 0, c2 = 0;
        while (c1 == c2) {
                c1 = *(a++);
                if ('\0' == (c2 = *(b++)))
                        return c1 == '\0' ? -1 : 1;
        }
        return 0;
}

/* returns times matched */
int s_match(char *a, char *b)
{
        int i = 0, count = 0;
        printf(&quot;matching `%s' with `%s':\n&quot;, a, b);

        while (a[i] != '\0') {
                switch (s_cmp(a + i, b)) {
                case -1:
                        printf(&quot;matched: pos %d (at end)\n\n&quot;, i);
                        return ++count;
                case 1:
                        printf(&quot;matched: pos %d\n&quot;, i);
                        ++count;
                        break;
                }
                i++;
        }
        printf(&quot;end match\n\n&quot;);
        return count;
}

int main()
{
        s_match(&quot;A Short String&quot;, &quot;ort S&quot;);
        s_match(&quot;aBaBaBaBa&quot;, &quot;aBa&quot;);
        s_match(&quot;something random&quot;, &quot;Rand&quot;);

        return 0;
}
