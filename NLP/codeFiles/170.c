#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int even_sel(int x) { return !(x &amp; 1); }
int tri_sel(int x) { return x % 3; }

/* using a predicate function sel() to select elements */
int* grep(int *in, int len, int *outlen, int (*sel)(int), int inplace)
{
	int i, j, *out;

	if (inplace)	out = in;
	else		out = malloc(sizeof(int) * len);

	for (i = j = 0; i &lt; len; i++)
		if (sel(in[i]))
			out[j++] = in[i];

	if (!inplace &amp;&amp; j &lt; len)
		out = realloc(out, sizeof(int) * j);

	*outlen = j;
	return out;
}

int main()
{
	int in[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int i, len;

	int *even = grep(in, 10, &amp;len, even_sel, 0);
	printf(&quot;Filtered even:&quot;);
	for (i = 0; i &lt; len; i++) printf(&quot; %d&quot;, even[i]);
	printf(&quot;\n&quot;);

	grep(in, 8, &amp;len, tri_sel, 1);
	printf(&quot;In-place filtered not multiple of 3:&quot;);
	for (i = 0; i &lt; len; i++) printf(&quot; %d&quot;, in[i]);

	printf(&quot;\n&quot;);

	return 0;
}
