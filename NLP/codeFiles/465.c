#include &lt;time.h&gt;#include &lt;stdio.h&gt;

int main() {
    time_t t = 0;
    printf(&quot;%s&quot;, asctime(gmtime(&amp;t)));
    return 0;
}
