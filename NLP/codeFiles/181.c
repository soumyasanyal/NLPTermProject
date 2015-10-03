#include&lt;stdio.h&gt;
int main (void)
{
    int i;
    for (i = 1; i &lt;= 100; i++)
    {
        if (!(i % 15))
            printf (&quot;FizzBuzz&quot;);
        else if (!(i % 3))
            printf (&quot;Fizz&quot;);
        else if (!(i % 5))
            printf (&quot;Buzz&quot;);
        else
            printf (&quot;%d&quot;, i);

        printf(&quot;\n&quot;);
    }
    return 0;
}
