#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
 
int main(int c, char **v)
{
	int i, j, m, n, *s;
 
	/* default size: 5 */
	if (c &lt; 2 || ((m = atoi(v[1]))) &lt;= 0) m = 5;
 
	/* alloc array*/
	s = malloc(sizeof(int) * m * m);
 
	for (i = n = 0; i &lt; m * 2; i++)
		for (j = (i &lt; m) ? 0 : i-m+1; j &lt;= i &amp;&amp; j &lt; m; j++)
			s[(i&amp;1)? j*(m-1)+i : (i-j)*m+j ] = n++;
 
	for (i = 0; i &lt; m * m; putchar((++i % m) ? ' ':'\n'))
		printf(&quot;%3d&quot;, s[i]);

	/* free(s) */
	return 0;
}
