#include &lt;stdio.h&gt;
void show(int *x)
{
	int i, j;
	for (i = 0; i &lt; 9; i++) {
		if (!(i % 3)) putchar('\n');
		for (j = 0; j &lt; 9; j++)
			printf(j % 3 ? &quot;%2d&quot; : &quot;%3d&quot;, *x++);
		putchar('\n');
	}
}

int trycell(int *x, int pos)
{
	int row = pos / 9;
	int col = pos % 9;
	int i, j, used = 0;

	if (pos == 81) return 1;
	if (x[pos]) return trycell(x, pos + 1);

	for (i = 0; i &lt; 9; i++)
		used |= 1 &lt;&lt; (x[i * 9 + col] - 1);

	for (j = 0; j &lt; 9; j++)
		used |= 1 &lt;&lt; (x[row * 9 + j] - 1);

	row = row / 3 * 3;
	col = col / 3 * 3;
	for (i = row; i &lt; row + 3; i++)
		for (j = col; j &lt; col + 3; j++)
			used |= 1 &lt;&lt; (x[i * 9 + j] - 1);

	for (x[pos] = 1; x[pos] &lt;= 9; x[pos]++, used &gt;&gt;= 1)
		if (!(used &amp; 1) &amp;&amp; trycell(x, pos + 1)) return 1;

	x[pos] = 0;
	return 0;
}

void solve(char *s)
{
	int i, x[81];
	for (i = 0; i &lt; 81; i++)
		x[i] = s[i] &gt;= '1' &amp;&amp; s[i] &lt;= '9' ? s[i] - '0' : 0;

	if (trycell(x, 0))
		show(x);
	else
		puts(&quot;no solution&quot;);
}

int main(void)
{
	solve(	&quot;5x..7....&quot;
		&quot;6..195...&quot;
		&quot;.98....6.&quot;
		&quot;8...6...3&quot;
		&quot;4..8.3..1&quot;
		&quot;7...2...6&quot;
		&quot;.6....28.&quot;
		&quot;...419..5&quot;
		&quot;....8..79&quot;	);

	return 0;
}
