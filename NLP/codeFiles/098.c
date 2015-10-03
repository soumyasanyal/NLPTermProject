#include &lt;stdio.h&gt;#include &lt;string.h&gt;

// returns count of non-overlapping occurrences of 'sub' in 'str'
int countSubstring(const char *str, const char *sub)
{
    int length = strlen(sub);
    if (length == 0) return 0;
    int count = 0;
    for (str = strstr(str, sub); str; str = strstr(str + length, sub))
        ++count;
    return count;
}

int main()
{
    printf(&quot;%d\n&quot;, countSubstring(&quot;the three truths&quot;, &quot;th&quot;));
    printf(&quot;%d\n&quot;, countSubstring(&quot;ababababab&quot;, &quot;abab&quot;));
    printf(&quot;%d\n&quot;, countSubstring(&quot;abaabba*bbaba*bbab&quot;, &quot;a*b&quot;));

    return 0;
}
