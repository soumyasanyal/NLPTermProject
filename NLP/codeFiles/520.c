/* Demonstrate toupper and tolower for    standard C strings.
   This does not work for multibyte character sets. */
#include &lt;ctype.h&gt;
#include &lt;stdio.h&gt;

/* upper-cases s in place */
void str_toupper(char *s)
{
    while(*s)
    {
        *s=toupper(*s);
        s++;
    }
}


/* lower-cases s in place */
void str_tolower(char *s)
{
    while(*s)
    {
        *s=tolower(*s);
        s++;
    }
}

int main(int argc, char *argv[])
{
    char t[255]=&quot;alphaBETA&quot;;
    str_toupper(t);
    printf(&quot;uppercase: %s\n&quot;, t);
    str_tolower(t);
    printf(&quot;lowercase: %s\n&quot;, t);
    return 0;
}
