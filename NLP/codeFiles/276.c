#include &lt;stdio.h&gt;#include &lt;string.h&gt;

int levenshtein(char *s, char *t)
{
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];

	for (int i = 0; i &lt;= ls; i++)
		for (int j = 0; j &lt;= lt; j++)
			d[i][j] = -1;

	int dist(int i, int j) {
		if (d[i][j] &gt;= 0) return d[i][j];

		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);

			int y;
			if ((y = dist(i, j + 1)) &lt; x) x = y;
			if ((y = dist(i + 1, j)) &lt; x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);
}

int main(void)
{
	char *s1 = &quot;rosettacode&quot;;
	char *s2 = &quot;raisethysword&quot;;
	printf(&quot;distance betweeh `%s' and `%s': %d\n&quot;, s1, s2,
		levenshtein(s1, s2));
 
        return 0;
}
