#include &lt;stdio.h&gt;#include &lt;stdbool.h&gt;

bool is_leap_year(int year)
{
    return !(year % 4) &amp;&amp; year % 100 || !(year % 400);
}

int main()
{
    int test_case[] = {1900, 1994, 1996, 1997, 2000}, key, end;
    for (key = 0, end = sizeof(test_case)/sizeof(test_case[0]); key &lt; end; ++key) {
        int year = test_case[key];
        printf(&quot;%d is %sa leap year.\n&quot;, year, is_leap_year(year) ? &quot;&quot; : &quot;not &quot;);
    }
}
