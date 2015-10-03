#include &lt;stdio.h&gt;
void transpose(void *dest, void *src, int src_h, int src_w)
{
	int i, j;
	double (*d)[src_h] = dest, (*s)[src_w] = src;
	for (i = 0; i &lt; src_h; i++)
		for (j = 0; j &lt; src_w; j++)
			d[j][i] = s[i][j];
}

int main()
{
	int i, j;
	double a[3][5] = {{ 0, 1, 2, 3, 4 },
			  { 5, 6, 7, 8, 9 },
			  { 1, 0, 0, 0, 42}};
	double b[5][3];
	transpose(b, a, 3, 5);

	for (i = 0; i &lt; 5; i++)
		for (j = 0; j &lt; 3; j++)
			printf(&quot;%g%c&quot;, b[i][j], j == 2 ? '\n' : ' ');
	return 0;
}
