#include &lt;stdio.h&gt;
int pangram(const char *s)
{
	int c, mask = (1 &lt;&lt; 26) - 1;
	while ((c = (*s++)) != '\0') /* 0x20 converts lowercase to upper */
		if ((c &amp;= ~0x20) &lt;= 'Z' &amp;&amp; c &gt;= 'A')
			mask &amp;= ~(1 &lt;&lt; (c - 'A'));

	return !mask;
}

int main()
{
	int i;
	const char *s[] = {	&quot;The quick brown fox jumps over lazy dogs.&quot;,
				&quot;The five boxing wizards dump quickly.&quot;,  };

	for (i = 0; i &lt; 2; i++)
		printf(&quot;%s: %s\n&quot;, pangram(s[i]) ? &quot;yes&quot; : &quot;no &quot;, s[i]);

	return 0;
}
