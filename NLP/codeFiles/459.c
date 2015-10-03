#include &lt;stdio.h&gt;
int self_desc(char *s)
{
	unsigned char cnt[10] = {0};
	int i;
	for (i = 0; s[i] != '\0'; i++) cnt[s[i] - '0']++;
	for (i = 0; s[i] != '\0'; i++) if (cnt[i] + '0' != s[i]) return 0;
	return 1;
}

void gen(int n)
{
	char d[11];
	int one, i;
	/* one = 0 may be confusing.  'one' is the number of digit 1s */
	for (one = 0; one &lt;= 2 &amp;&amp; one &lt; n - 2; one++) {
		for (i = 0; i &lt;= n; d[i++] = 0);

		if ((d[0] = n - 2 - one) != 2) {
			d[2] = d[d[0] - 0] = 1;
			d[1] = 2;
		} else {
			d[1] = one ? 1 : 0;
			d[2] = 2;
		}

		for (i = 0; i &lt; n; d[i++] += '0');
		if (self_desc(d)) printf(&quot;%s\n&quot;, d);
	}
}

int main()
{
	int i;
	char *nums[] = { &quot;1210&quot;, &quot;1337&quot;, &quot;2020&quot;, &quot;21200&quot;, &quot;3211000&quot;, &quot;42101000&quot;, 0};

	for (i = 0; nums[i]; i++)
		printf(&quot;%s is %sself describing\n&quot;, nums[i],
			self_desc(nums[i]) ? &quot;&quot; : &quot;not &quot;);

	printf(&quot;\nAll autobiograph numbers:\n&quot;);
	for (i = 0; i &lt; 11; i++) gen(i);
	return 0;
}
