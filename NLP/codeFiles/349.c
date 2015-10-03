#include &lt;stdio.h&gt;#include &lt;string.h&gt;

char *ones[] = { 0, &quot;one&quot;, &quot;two&quot;, &quot;three&quot;, &quot;four&quot;,
	&quot;five&quot;, &quot;six&quot;, &quot;seven&quot;, &quot;eight&quot;, &quot;nine&quot;, 
	&quot;ten&quot;, &quot;eleven&quot;, &quot;twelve&quot;, &quot;thirteen&quot;, &quot;fourteen&quot;,
	&quot;fifteen&quot;, &quot;sixteen&quot;, &quot;seventeen&quot;, &quot;eighteen&quot;, &quot;nineteen&quot; };
char *tens[] = { 0, &quot;ten&quot;, &quot;twenty&quot;, &quot;thirty&quot;, &quot;forty&quot;,
	&quot;fifty&quot;, &quot;sixty&quot;, &quot;seventy&quot;, &quot;eighty&quot;, &quot;ninety&quot; };
char *llions[] = { 0, &quot;thousand&quot;, &quot;million&quot;, &quot;billion&quot;, &quot;trillion&quot;,
//	&quot;quadrillion&quot;, &quot;quintillion&quot;, &quot;sextillion&quot;, &quot;septillion&quot;,
//	&quot;octillion&quot;, &quot;nonillion&quot;, &quot;decillion&quot;
	};
const int maxillion = sizeof(llions) / sizeof(llions[0]) * 3 - 3;

int say_hundred(char *s, int len, int depth, int has_lead)
{
	int c[3], i;
	for (i = -3; i &lt; 0; i++) {
		if (len + i &gt;= 0) c[i + 3] = s[len + i] - '0';
		else c[i + 3] = 0;
	}
	if (!(c[0] + c[1] + c[2])) return 0;

	if (c[0]) {
		printf(&quot;%s hundred&quot;, ones[c[0]]);
		has_lead = 1;
	}

	if (has_lead &amp;&amp; (c[1] || c[2]))
		printf((!depth || c[0]) &amp;&amp; (!c[0] || !c[1]) ? &quot;and &quot; :
			c[0] ? &quot; &quot; : &quot;&quot;);

	if (c[1] &lt; 2) {
		if (c[1] || c[2]) printf(&quot;%s&quot;, ones[c[1] * 10 + c[2]]);
	} else {
		if (c[1]) {
			printf(&quot;%s&quot;, tens[c[1]]);
			if (c[2]) putchar('-');
		}
		if (c[2]) printf(&quot;%s&quot;, ones[c[2]]);
	}

	return 1;
}

int say_maxillion(char *s, int len, int depth, int has_lead)
{
	int n = len / 3, r = len % 3;
	if (!r) {
		n--;
		r = 3;
	}
	char *e = s + r;
	do {
		if (say_hundred(s, r, n, has_lead) &amp;&amp; n) {
			has_lead = 1;
			printf(&quot; %s&quot;, llions[n]);
			if (!depth) printf(&quot;, &quot;);
			else printf(&quot; &quot;);
		}
		s = e; e += 3;
	} while (r = 3, n--);

	return 1;
}

void say_number(char *s)
{
	int len, i, got_sign = 0;

	while (*s == ' ') s++;
	if (*s &lt; '0' || *s &gt; '9') {
		if (*s == '-') got_sign = -1;
		else if (*s == '+') got_sign = 1;
		else goto nan;
		s++;
	} else
		got_sign = 1;

	while (*s == '0') {
		s++;
		if (*s == '\0') {
			printf(&quot;zero\n&quot;);
			return;
		}
	}

	len = strlen(s);
	if (!len) goto nan;

	for (i = 0; i &lt; len; i++) {
		if (s[i] &lt; '0' || s[i] &gt; '9') {
			printf(&quot;(not a number)&quot;);
			return;
		}
	}
	if (got_sign == -1) printf(&quot;minus &quot;);

	int n = len / maxillion;
	int r = len % maxillion;
	if (!r) {
		r = maxillion;
		n--;
	}

	char *end = s + len - n * maxillion;
	int has_lead = 0;
	do {
		if ((has_lead = say_maxillion(s, r, n, has_lead))) {
			for (i = 0; i &lt; n; i++)
				printf(&quot; %s&quot;, llions[maxillion / 3]);
			if (n) printf(&quot;, &quot;);
		}
		n--;
		r = maxillion;
		s = end;
		end += r;
	} while (n &gt;= 0);

	printf(&quot;\n&quot;);
	return;

nan:	printf(&quot;not a number\n&quot;);
	return;
}

int main()
{
	say_number(&quot;-42&quot;);
	say_number(&quot;1984&quot;);
	say_number(&quot;10000&quot;);
	say_number(&quot;1024&quot;);
	say_number(&quot;1001001001001&quot;);
	say_number(&quot;123456789012345678901234567890123456789012345678900000001&quot;);
	return 0;
}
