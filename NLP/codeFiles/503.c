#include &lt;stdlib.h&gt;#include &lt;unistd.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/wait.h&gt;

int main(int c, char **v)
{
        while (--c &gt; 1 &amp;&amp; !fork());
        sleep(c = atoi(v[c]));
        printf(&quot;%d\n&quot;, c);
        wait(0);
        return 0;
}
