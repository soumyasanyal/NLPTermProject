#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char* lcs(char *a, char *b, char *out)
{
	int longest = 0;
	int match(char *a, char *b, int dep) {
		if (!a || !b) return 0;
		if (!*a || !*b) {
			if (dep &lt;= longest) return 0;
			out[ longest = dep ] = 0;
			return 1;
		}

		if (*a == *b)
			return match(a + 1, b + 1, dep + 1) &amp;&amp; (out[dep] = *a);

		return	match(a + 1, b + 1, dep) + 
			match(strchr(a, *b), b, dep) +
			match(a, strchr(b, *a), dep);
	}

	return match(a, b, 0) ? out : 0;
}

int main()
{
	char buf[128];
	printf(&quot;%s\n&quot;, lcs(&quot;thisisatest&quot;, &quot;testing123testing&quot;, buf));
	printf(&quot;%p\n&quot;, lcs(&quot;no&quot;, &quot;match&quot;, buf));
	return 0;
}
