#include &lt;stdio.h&gt;#include &lt;ctype.h&gt;
 
char rfc3986[256] = {0};
char html5[256] = {0};

/* caller responsible for memory */
void encode(unsigned char *s, char *enc, char *tb)
{
	for (; *s; s++) {
		if (tb[*s]) sprintf(enc, &quot;%c&quot;, tb[*s]);
		else        sprintf(enc, &quot;%%%02X&quot;, *s);
		while (*++enc);
	}
}
 
int main()
{
	unsigned char url[] = &quot;http://foo bar/&quot;;
	char enc[sizeof(url) * 3];
 
	int i;
	for (i = 0; i &lt; 256; i++) {
		rfc3986[i] = isalnum(i)||i == '~'||i == '-'||i == '.'||i == '_'
			? i : 0;
		html5[i] = isalnum(i)||i == '*'||i == '-'||i == '.'||i == '_'
			? i : (i == ' ') ? '+' : 0;
	}
 
	encode(url, enc, rfc3986);
	puts(enc);
 
	return 0;
}
