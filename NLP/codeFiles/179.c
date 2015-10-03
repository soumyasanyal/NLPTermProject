#include &lt;stdio.h&gt;#include &lt;time.h&gt;

static const char *months[] = {&quot;January&quot;, &quot;February&quot;, &quot;March&quot;, &quot;April&quot;, &quot;May&quot;,
    &quot;June&quot;, &quot;July&quot;, &quot;August&quot;, &quot;September&quot;, &quot;October&quot;, &quot;November&quot;, &quot;December&quot;};
static int long_months[] = {0, 2, 4, 6, 7, 9, 11};

int main() {
    int n = 0, y, i, m;
    struct tm t = {0};
    printf(&quot;Months with five weekends:\n&quot;);
    for (y = 1900; y &lt;= 2100; y++) {
        for (i = 0; i &lt; 7; i++) {
            m = long_months[i];
            t.tm_year = y-1900;
	    t.tm_mon = m;
	    t.tm_mday = 1;
            if (mktime(&amp;t) == -1) { /* date not supported */
                printf(&quot;Error: %d %s\n&quot;, y, months[m]);
                continue;
            }
            if (t.tm_wday == 5) { /* Friday */
                printf(&quot;  %d %s\n&quot;, y, months[m]);
                n++;
            }
        }
    }
    printf(&quot;%d total\n&quot;, n);
    return 0;
}
