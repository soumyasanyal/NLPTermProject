#include &lt;stdio.h&gt;#include &lt;string.h&gt;

inline int ishex(int x)
{
	return	(x &gt;= '0' &amp;&amp; x &lt;= '9')	||
		(x &gt;= 'a' &amp;&amp; x &lt;= 'f')	||
		(x &gt;= 'A' &amp;&amp; x &lt;= 'F');
}

int decode(char *s, char *dec)
{
	char *o, *end = s + strlen(s);
	int c;

	for (o = dec; s &lt;= end; o++) {
		c = *s++;
		if (c == '+') c = ' ';
		else if (c == '%' &amp;&amp; (	!ishex(*s++)	||
					!ishex(*s++)	||
					!sscanf(s - 2, &quot;%2x&quot;, &amp;c)))
			return -1;

		if (dec) *o = c;
	}

	return o - dec;
}

int main()
{
	char url[] = &quot;http%3A%2F%2ffoo+bar%2fabcd&quot;;
	char out[sizeof(url)];

	printf(&quot;length: %d\n&quot;, decode(url, 0));
	puts(decode(url, out) &lt; 0 ? &quot;bad string&quot; : out);

	return 0;
}
