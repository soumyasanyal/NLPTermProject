#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int count = 0;
void solve(int n, int col, int *hist)
{
	if (col == n) {
		printf(&quot;\nNo. %d\n-----\n&quot;, ++count);
		for (int i = 0; i &lt; n; i++, putchar('\n'))
			for (int j = 0; j &lt; n; j++)
				putchar(j == hist[i] ? 'Q' : ((i + j) &amp; 1) ? ' ' : '.');

		return;
	}

#	define attack(i, j) (hist[j] == i || abs(hist[j] - i) == col - j)
	for (int i = 0, j = 0; i &lt; n; i++) {
		for (j = 0; j &lt; col &amp;&amp; !attack(i, j); j++);
		if (j &lt; col) continue;

		hist[col] = i;
		solve(n, col + 1, hist);
	}
}

int main(int n, char **argv)
{
	if (n &lt;= 1 || (n = atoi(argv[1])) &lt;= 0) n = 8;
	int hist[n];
	solve(n, 0, hist);
}
