#include &lt;limits.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

static void powerset(int argc, char** argv)
{
    unsigned int i, j, bits, i_max = 1U &lt;&lt; argc;

    if (argc &gt;= sizeof(i) * CHAR_BIT) {
        fprintf(stderr, &quot;Error: set too large\n&quot;);
        exit(1);
    }

    for (i = 0; i &lt; i_max ; ++i) {
        printf(&quot;{&quot;);
        for (bits = i, j = 0; bits; bits &gt;&gt;= 1, ++j) {
            if (bits &amp; 1)
                printf(bits &gt; 1 ? &quot;%s, &quot; : &quot;%s&quot;, argv[j]);
        }
        printf(&quot;}\n&quot;);
    }
}

int main(int argc, char* argv[])
{
    powerset(argc - 1, argv + 1);
    return 0;
}
