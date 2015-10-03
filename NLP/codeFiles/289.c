#include &lt;stdlib.h&gt;#include &lt;time.h&gt;
#include &lt;stdio.h&gt;

int main() {
    int a, b;

    srand(time(NULL));
    while (1) {
        a = rand() % 20; /* not exactly uniformly distributed, but doesn't matter */
        printf(&quot;%d\n&quot;, a);
        if (a == 10) break;
        b = rand() % 20; /* not exactly uniformly distributed, but doesn't matter */
        printf(&quot;%d\n&quot;, b);
    }
    return 0;
}
