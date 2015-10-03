#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

struct item { double w, v; char *name; } items[] = {
	{ 3.8, 36, &quot;beef&quot; },
	{ 5.4, 43, &quot;pork&quot; },
	{ 3.6, 90, &quot;ham&quot; },
	{ 2.4, 45, &quot;greaves&quot; },
	{ 4.0, 30, &quot;flitch&quot; },
	{ 2.5, 56, &quot;brawn&quot; },
	{ 3.7, 67, &quot;welt&quot; },
	{ 3.0, 95, &quot;salami&quot; },
	{ 5.9, 98, &quot;sausage&quot; },
};

int item_cmp(const void *aa, const void *bb)
{
	const struct item *a = aa, *b = bb;
	double ua = a-&gt;v / a-&gt;w, ub = b-&gt;v / b-&gt;w;
	return ua &lt; ub ? -1 : ua &gt; ub;
}

int main()
{
	struct item *it;
	double space = 15;

	qsort(items, 9, sizeof(struct item), item_cmp);
	for (it = items + 9; it---items &amp;&amp; space &gt; 0; space -= it-&gt;w)
		if (space &gt;= it-&gt;w)
			printf(&quot;take all %s\n&quot;, it-&gt;name);
		else
			printf(&quot;take %gkg of %g kg of %s\n&quot;,
				space, it-&gt;w, it-&gt;name);

	return 0;
}
