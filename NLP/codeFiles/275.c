#include &lt;stdio.h&gt;#include &lt;string.h&gt;

/* s, t: two strings; ls, lt: their respective length */
int levenshtein(char *s, int ls, char *t, int lt)
{
        int a, b, c;

        /* if either string is empty, difference is inserting all chars 
         * from the other
         */
        if (!ls) return lt;
        if (!lt) return ls;

        /* if first letters are the same, the difference is whatever is
         * required to edit the rest of the strings
         */
        if (s[ls] == t[lt])
                return levenshtein(s, ls - 1, t, lt - 1);

        /* else try:
         *      changing first letter of s to that of t; or
         *      remove first letter of s; or
         *      remove first letter of t,
         * any of which is 1 edit plus editing the rest of the strings
         */
        a = levenshtein(s, ls - 1, t, lt - 1);
        b = levenshtein(s, ls,     t, lt - 1);
        c = levenshtein(s, ls - 1, t, lt    );

        if (a &gt; b) a = b;
        if (a &gt; c) a = c;

        return a + 1;
}

int main()
{
        char *s1 = &quot;rosettacode&quot;;
        char *s2 = &quot;raisethysword&quot;;
        printf(&quot;distance betweeh `%s' and `%s': %d\n&quot;, s1, s2,
                levenshtein(s1, strlen(s1), s2, strlen(s2)));

        return 0;
}
