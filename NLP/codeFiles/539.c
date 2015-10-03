#include &lt;stdio.h&gt;#include &lt;string.h&gt;

char *A[] = { &quot;John&quot;, &quot;Serena&quot;, &quot;Bob&quot;, &quot;Mary&quot;, &quot;Serena&quot; };
char *B[] = { &quot;Jim&quot;, &quot;Mary&quot;, &quot;John&quot;, &quot;Jim&quot;, &quot;Bob&quot; };

#define LEN(x) sizeof(x)/sizeof(x[0])

/* null duplicate items */
void uniq(char *x[], int len)
{
	int i, j;
	for (i = 0; i &lt; len; i++)
		for (j = i + 1; j &lt; len; j++)
			if (x[j] &amp;&amp; x[i] &amp;&amp; !strcmp(x[i], x[j])) x[j] = 0;
}

int in_set(char *x[], int len, char *match)
{
	int i;
	for (i = 0; i &lt; len; i++)
		if (x[i] &amp;&amp; !strcmp(x[i], match))
			return 1;
	return 0;
}

/* x - y */
void show_diff(char *x[], int lenx, char *y[], int leny)
{
	int i;
	for (i = 0; i &lt; lenx; i++)
		if (x[i] &amp;&amp; !in_set(y, leny, x[i]))
			printf(&quot;  %s\n&quot;, x[i]);
}

/* X ^ Y */
void show_sym_diff(char *x[], int lenx, char *y[], int leny)
{
	show_diff(x, lenx, y, leny);
	show_diff(y, leny, x, lenx);
}

int main()
{
	uniq(A, LEN(A));
	uniq(B, LEN(B));
	printf(&quot;A \\ B:\n&quot;); show_diff(A, LEN(A), B, LEN(B));
	printf(&quot;\nB \\ A:\n&quot;); show_diff(B, LEN(B), A, LEN(A));
	printf(&quot;\nA ^ B:\n&quot;);  show_sym_diff(A, LEN(A), B, LEN(B));

	return 0;
}
