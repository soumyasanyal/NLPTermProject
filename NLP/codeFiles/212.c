#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;time.h&gt;

int main(void)
{
    int n;
    int g;
    char c;

    srand(time(NULL));
    n = 1 + (rand() % 10);

    puts(&quot;I'm thinking of a number between 1 and 10.&quot;);
    puts(&quot;Try to guess it:&quot;);

    while (1) {
        if (scanf(&quot;%d&quot;, &amp;g) != 1) {
		/* ignore one char, in case user gave a non-number */
		scanf(&quot;%c&quot;, &amp;c);
		continue;
	}

        if (g == n) {
	    puts(&quot;Correct!&quot;);
	    return 0;
	}
        puts(&quot;That's not my number. Try another guess:&quot;);
    }
}
