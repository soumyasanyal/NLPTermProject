#include &lt;stdio.h&gt;
#define N 4
char *perms[] = {
	&quot;ABCD&quot;, &quot;CABD&quot;, &quot;ACDB&quot;, &quot;DACB&quot;, &quot;BCDA&quot;, &quot;ACBD&quot;, &quot;ADCB&quot;, &quot;CDAB&quot;,
	&quot;DABC&quot;, &quot;BCAD&quot;, &quot;CADB&quot;, &quot;CDBA&quot;, &quot;CBAD&quot;, &quot;ABDC&quot;, &quot;ADBC&quot;, &quot;BDCA&quot;,
	&quot;DCBA&quot;, &quot;BACD&quot;, &quot;BADC&quot;, &quot;BDAC&quot;, &quot;CBDA&quot;, &quot;DBCA&quot;, &quot;DCAB&quot;,
};

int main()
{
	int i, j, n, cnt[N];
	char miss[N];

	for (n = i = 1; i &lt; N; i++) n *= i; /* n = (N-1)!, # of occurence */

	for (i = 0; i &lt; N; i++) {
		for (j = 0; j &lt; N; j++) cnt[j] = 0;

		/* count how many times each letter occur at postion i */
		for (j = 0; j &lt; sizeof(perms)/sizeof(char*); j++)
			cnt[perms[j][i] - 'A']++;

		/* letter not occuring (N-1)! times is the missing one */
		for (j = 0; j &lt; N &amp;&amp; cnt[j] == n; j++);

		miss[i] = j + 'A';
	}
	printf(&quot;Missing: %.*s\n&quot;, N, miss);

	return 0;
		
}
