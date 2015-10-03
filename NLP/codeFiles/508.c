#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
 
#define valid(i, j) 0 &lt;= i &amp;&amp; i &lt; m &amp;&amp; 0 &lt;= j &amp;&amp; j &lt; n &amp;&amp; !s[i][j]
int main(int c, char **v)
{
	int i, j, m = 0, n = 0;
 
	/* default size: 5 */
	if (c &gt;= 2) m = atoi(v[1]);
	if (c &gt;= 3) n = atoi(v[2]);
	if (m &lt;= 0) m = 5;
	if (n &lt;= 0) n = m;
 
	int **s = calloc(1, sizeof(int *) * m + sizeof(int) * m * n);
	s[0] = (int*)(s + m);
	for (i = 1; i &lt; m; i++) s[i] = s[i - 1] + n;
 
	int dx = 1, dy = 0, val = 0, t;
	for (i = j = 0; valid(i, j); i += dy, j += dx ) {
		for (; valid(i, j); j += dx, i += dy)
			s[i][j] = ++val;
 
		j -= dx; i -= dy;
		t = dy; dy = dx; dx = -t;
	}

	for (t = 2; val /= 10; t++);

	for(i = 0; i &lt; m; i++)
		for(j = 0; j &lt; n || !putchar('\n'); j++)
			printf(&quot;%*d&quot;, t, s[i][j]);

	return 0;
}
