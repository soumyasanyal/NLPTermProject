#include &lt;stdio.h&gt;#include &quot;silly.h&quot;

int main()
{
    AbsCls abster = Silly_Instance(NewSilly( 10.1, &quot;Green Tomato&quot;));

    printf(&quot;AbsMethod1: %d\n&quot;, Abs_Method1(abster, 5));
    printf(&quot;AbsMethod2: %s\n&quot;, Abs_Method2(abster, 4));
    Abs_Method3(abster, 21.55);
    Abs_Free(abster);
    return 0;
}

