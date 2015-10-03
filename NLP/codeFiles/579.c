#include &lt;stdio.h&gt;#include &lt;stdarg.h&gt;

void varstrings(int count, ...)   /* the ellipsis indicates variable arguments */
{
    va_list args;
    va_start(args, count);
    while (count--)
        puts(va_arg(args, const char *));
    va_end(args);
}

varstrings(5, &quot;Mary&quot;, &quot;had&quot;, &quot;a&quot;, &quot;little&quot;, &quot;lamb&quot;);
