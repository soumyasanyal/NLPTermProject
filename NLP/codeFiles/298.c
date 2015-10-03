#include &lt;stdlib.h&gt;#include &lt;time.h&gt;
#include &lt;stdio.h&gt;

int main() {
    int a[10][10], i, j;

    srand(time(NULL));
    for (i = 0; i &lt; 10; i++)
        for (j = 0; j &lt; 10; j++)
            a[i][j] = rand() % 20 + 1;

    for (i = 0; i &lt; 10; i++) {
        for (j = 0; j &lt; 10; j++) {
            printf(&quot; %d&quot;, a[i][j]);
            if (a[i][j] == 20)
                goto Done;
        }
        printf(&quot;\n&quot;);
    }
Done:
    printf(&quot;\n&quot;);
    return 0;
}
