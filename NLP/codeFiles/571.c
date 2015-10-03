#include &lt;stdio.h&gt;int main(int argc, char* argv[])
{
        int input;
        if((scanf(&quot;%d&quot;, &amp;input))==1)
        {
                printf(&quot;Read in %d\n&quot;, input);
                return 1;
        }
        return 0;
}
