#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ucontext.h&gt;

#define try push_handler(); if (!exc_string)
#define catch(e) pop_handler(e); for (; exc_string; exc_string = 0)

ucontext_t *exc;
int exc_depth = 0;
int exc_alloc = 0;
char * exc_string;
char * e_saved;

void throw(char *str)
{
        exc_string = str;
        setcontext(exc + exc_depth - 1);
}

void push_handler()
{
        exc_string = 0;
        if (exc_alloc &lt;= exc_depth) {
                exc_alloc += 16;
                exc = realloc(exc, sizeof(ucontext_t) * exc_alloc);
        }
        getcontext(exc + exc_depth++);
}

void pop_handler(char *e)
{
        exc_depth --;
        if (exc_string &amp;&amp; strcmp(e, exc_string)) {
                if (exc_depth &gt; 0)
                        throw(exc_string);
                fprintf(stderr, &quot;Fatal: unhandled exception %s\n&quot;, exc_string);
                exit(1);
        }
}

/* try out the exception system */

void baz() {
        static int count = 0;
        switch (count++) {
                case 0: throw(&quot;U0&quot;);
                case 1: throw(&quot;U1&quot;);
                case 2: throw(&quot;U2&quot;);
        }
}

void foo()
{
        printf(&quot;    foo: calling baz\n&quot;);
        try { baz(); }
        catch(&quot;U0&quot;) {
                printf(&quot;    foo: got exception U0; handled and dandy\n&quot;);
        }

        printf(&quot;    foo: finished\n&quot;);
}

int main() {
        int i;
        for (i = 0; i &lt; 3; i++) {
                printf(&quot;main: calling foo: %d\n&quot;, i);
                try { foo(); }
                catch(&quot;U1&quot;) {
                        printf(&quot;main: Someone threw U1; handled and dandy\n&quot;);
                }
        }
        return 0;
}
