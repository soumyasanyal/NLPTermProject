#include &lt;stdio.h&gt;
int common_len(char **names, int n, char sep)
{
	int i, pos;
	for (pos = 0; ; pos++) {
		for (i = 0; i &lt; n; i++) {
			if (names[i][pos] != '\0' &amp;&amp;
					names[i][pos] == names[0][pos])
				continue;

			/* backtrack */
			while (pos &gt; 0 &amp;&amp; names[0][--pos] != sep);
			return pos;
		}
	}

	return 0;
}

int main()
{
	char *names[] = {
		&quot;/home/user1/tmp/coverage/test&quot;,
		&quot;/home/user1/tmp/covert/operator&quot;,
		&quot;/home/user1/tmp/coven/members&quot;,
	};
	int len = common_len(names, sizeof(names) / sizeof(char*), '/');

	if (!len) printf(&quot;No common path\n&quot;);
	else      printf(&quot;Common path: %.*s\n&quot;, len, names[0]);

	return 0;
}
