#include &lt;stdio.h&gt;#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;

/*  Constraints: input is in the form of (\+|-)?[0-9]+
 *  and without leading zero (0 itself can be as &quot;0&quot; or &quot;+0&quot;, but not &quot;-0&quot;);
 *  input pointer is realloc'able and may change;
 *  if input has leading + sign, return may or may not keep it.
 *  The constranits conform to sprintf(&quot;%+d&quot;) and this function's own output.
 */
char * incr(char *s)
{
	int i, begin, tail, len;
	int neg = (*s == '-');
	char tgt = neg ? '0' : '9';

	/* special case: &quot;-1&quot; */
	if (!strcmp(s, &quot;-1&quot;)) {
		s[0] = '0', s[1] = '\0';
		return s;
	}

	len = strlen(s);
	begin = (*s == '-' || *s == '+') ? 1 : 0;

	/* find out how many digits need to be changed */
	for (tail = len - 1; tail &gt;= begin &amp;&amp; s[tail] == tgt; tail--);

	if (tail &lt; begin &amp;&amp; !neg) {
		/* special case: all 9s, string will grow */
		if (!begin) s = realloc(s, len + 2);
		s[0] = '1';
		for (i = 1; i &lt;= len - begin; i++) s[i] = '0';
		s[len + 1] = '\0';
	} else if (tail == begin &amp;&amp; neg &amp;&amp; s[1] == '1') {
		/* special case: -1000..., so string will shrink */
		for (i = 1; i &lt; len - begin; i++) s[i] = '9';
		s[len - 1] = '\0';
	} else { /* normal case; change tail to all 0 or 9, change prev digit by 1*/
		for (i = len - 1; i &gt; tail; i--)
			s[i] = neg ? '9' : '0';
		s[tail] += neg ? -1 : 1;
	}

	return s;
}

void string_test(const char *s)
{
	char *ret = malloc(strlen(s));
	strcpy(ret, s);

	printf(&quot;text: %s\n&quot;, ret);
	printf(&quot;  -&gt;: %s\n&quot;, ret = incr(ret));
	free(ret);
}

int main()
{
	string_test(&quot;+0&quot;);
	string_test(&quot;-1&quot;);
	string_test(&quot;-41&quot;);
	string_test(&quot;+41&quot;);
	string_test(&quot;999&quot;);
	string_test(&quot;+999&quot;);
	string_test(&quot;109999999999999999999999999999999999999999&quot;);
	string_test(&quot;-100000000000000000000000000000000000000000000&quot;);

	return 0;
}
