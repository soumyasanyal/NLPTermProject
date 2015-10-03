#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;ctype.h&gt;
#include &lt;string.h&gt;
#include &lt;math.h&gt;

#define die(msg) fprintf(stderr, msg&quot;\n&quot;), abort();
double get(char *s, char *e, char **new_e)
{
	char *t;
	double a, b;

	for (e--; e &gt;= s &amp;&amp; isspace(*e); e--);
	for (t = e; t &gt; s &amp;&amp; !isspace(t[-1]); t--);

	if (t &lt; s) die(&quot;underflow&quot;);

#define get2(expr) b = get(s, t, &amp;t), a = get(s, t, &amp;t), a = expr
	a = strtod(t, &amp;e);
	if (e &lt;= t) {
		if	(t[0] == '+') get2(a + b);
		else if (t[0] == '-') get2(a - b);
		else if (t[0] == '*') get2(a * b);
		else if (t[0] == '/') get2(a / b);
		else if (t[0] == '^') get2(pow(a, b));
		else {
			fprintf(stderr, &quot;'%c': &quot;, t[0]);
			die(&quot;unknown token&quot;);
		}
	}
#undef get2

	*new_e = t;
	return a;
}

double rpn(char *s)
{
	char *e = s + strlen(s);
	double v = get(s, e, &amp;e);

	while (e &gt; s &amp;&amp; isspace(e[-1])) e--;
	if (e == s) return v;

	fprintf(stderr, &quot;\&quot;%.*s\&quot;: &quot;, e - s, s);
	die(&quot;front garbage&quot;);
}

int main(void)
{
	printf(&quot;%g\n&quot;, rpn(&quot;3 4 2 * 1 5 - 2 3 ^ ^ / +&quot;));
	return 0;
}
