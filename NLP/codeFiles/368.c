#include &lt;stdio.h&gt;
int isPangram(const char *string)
{
	char ch, wasused[26] = {0};
	int total = 0;

	while ((ch = *string++)) {
		int index;

		if('A'&lt;=ch&amp;&amp;ch&lt;='Z')
			index = ch-'A';
		else if('a'&lt;=ch&amp;&amp;ch&lt;='z')
			index = ch-'a';
		else
			continue;

		total += !wasused[index];
		wasused[index] = 1;
	}
	return (total==26);
}

int main()
{
	int i;
	const char *tests[] = {
		&quot;The quick brown fox jumps over the lazy dog.&quot;,
		&quot;The qu1ck brown fox jumps over the lazy d0g.&quot;
	};

	for (i = 0; i &lt; 2; i++)
		printf(&quot;\&quot;%s\&quot; is %sa pangram\n&quot;,
			tests[i], isPangram(tests[i])?&quot;&quot;:&quot;not &quot;);
	return 0;
}
