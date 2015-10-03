#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;math.h&gt;

void die(char *msg)
{
	fprintf(stderr, &quot;%s&quot;, msg);
	abort();
}

#define MAX_D 256
double stack[MAX_D];
int depth;

void push(double v)
{
	if (depth &gt;= MAX_D) die(&quot;stack overflow\n&quot;);
	stack[depth++] = v;
}

double pop()
{
	if (!depth) die(&quot;stack underflow\n&quot;);
	return stack[--depth];
}

double rpn(char *s)
{
	double a, b;
	int i;
	char *e, *w = &quot; \t\n\r\f&quot;;

	for (s = strtok(s, w); s; s = strtok(0, w)) {
		a = strtod(s, &amp;e);
		if (e &gt; s)		printf(&quot; :&quot;), push(a);
#define binop(x) printf(&quot;%c:&quot;, *s), b = pop(), a = pop(), push(x)
		else if (*s == '+')	binop(a + b);
		else if (*s == '-')	binop(a - b);
		else if (*s == '*')	binop(a * b);
		else if (*s == '/')	binop(a / b);
		else if (*s == '^')	binop(pow(a, b));
#undef binop
		else {
			fprintf(stderr, &quot;'%c': &quot;, *s);
			die(&quot;unknown oeprator\n&quot;);
		}
		for (i = depth; i-- || 0 * putchar('\n'); )
			printf(&quot; %g&quot;, stack[i]);
	}

	if (depth != 1) die(&quot;stack leftover\n&quot;);

	return pop();
}

int main(void)
{
	char s[] = &quot; 3 4 2 * 1 5 - 2 3 ^ ^ / + &quot;;
	printf(&quot;%g\n&quot;, rpn(s));
	return 0;
}
