#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main()
{
	char *a = malloc(2), *b = 0, *x, c;
	int cnt, len = 1;

	for (sprintf(a, &quot;1&quot;); (b = realloc(b, len * 2 + 1)); a = b, b = x) {
		puts(x = a);
		for (len = 0, cnt = 1; (c = *a); ) {
			if (c == *++a)
				cnt++;
			else if (c) {
				len += sprintf(b + len, &quot;%d%c&quot;, cnt, c);
				cnt = 1;
			}
		}
	}

	return 0;
}
