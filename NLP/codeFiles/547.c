#include &lt;stdio.h&gt;
typedef enum { t_F = -1, t_M, t_T } trit;

trit t_not  (trit a) { return -a; }
trit t_and  (trit a, trit b) { return a &lt; b ? a : b; }
trit t_or   (trit a, trit b) { return a &gt; b ? a : b; }
trit t_eq   (trit a, trit b) { return a * b; }
trit t_imply(trit a, trit b) { return -a &gt; b ? -a : b; }
char t_s(trit a) { return &quot;F?T&quot;[a + 1]; }

#define forall(a) for(a = t_F; a &lt;= t_T; a++)
void show_op(trit (*f)(trit, trit), char *name) {
	trit a, b;
	printf(&quot;\n[%s]\n    F ? T\n  -------&quot;, name);
	forall(a) {
		printf(&quot;\n%c |&quot;, t_s(a));
		forall(b) printf(&quot; %c&quot;, t_s(f(a, b)));
	}
	puts(&quot;&quot;);
}

int main(void)
{
	trit a;

	puts(&quot;[Not]&quot;);
	forall(a) printf(&quot;%c | %c\n&quot;, t_s(a), t_s(t_not(a)));

	show_op(t_and,   &quot;And&quot;);
	show_op(t_or,    &quot;Or&quot;);
	show_op(t_eq,    &quot;Equiv&quot;);
	show_op(t_imply, &quot;Imply&quot;);

	return 0;
}
