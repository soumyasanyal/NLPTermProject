#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdint.h&gt;
#include &lt;string.h&gt;

#define max_weight 400

typedef struct { char *name; int w, v, qty; } item_t;

item_t items[] = {
	{&quot;map&quot;,			9,	150,	1},
	{&quot;compass&quot;,		13,	35,	1},
	{&quot;water&quot;,		153,	200,	2},
	{&quot;sandwich&quot;,		50,	60,	2},
	{&quot;glucose&quot;,		15,	60,	2},
	{&quot;tin&quot;,			68,	45,	3},
	{&quot;banana&quot;,		27,	60,	3},
	{&quot;apple&quot;,		39,	40,	3},
	{&quot;cheese&quot;,		23,	30,	1},
	{&quot;beer&quot;,		52,	10,	3},
	{&quot;suntancream&quot;,		11,	70,	1},
	{&quot;camera&quot;,		32,	30,	1},
	{&quot;T-shirt&quot;,		24,	15,	2},
	{&quot;trousers&quot;,		48,	10,	2},
	{&quot;umbrella&quot;,		73,	40,	1},
	{&quot;w-trousers&quot;,		42,	70,	1},
	{&quot;w-overclothes&quot;,	43,	75,	1},
	{&quot;note-case&quot;,		22,	80,	1},
	{&quot;sunglasses&quot;,		7,      20,	1},
	{&quot;towel&quot;,		18,	12,	2},
	{&quot;socks&quot;,		4,      50,	1},
	{&quot;book&quot;,		30,	10,	2},
};

/* for C, the main problem is not the algorithm: it's cache management */
#define n_types (sizeof(items)/sizeof(item_t))
typedef struct {
	int v, w;		   /* value &amp; weight total */
	unsigned short n[n_types]; /* num of each item taken */
} solution_t, *solution;

solution_t *cache, *blank;

int init_cache()
{
	/* a flat array.  If problem size is large, might be a bad idea;
	 * then again, other caching method face similar issue, too
	 */
	size_t i;
	size_t n_rec = (max_weight + 1) * n_types;
	cache = calloc(sizeof(solution_t), (n_rec + 1));
	if (!cache) return 0;

	for (i = 0; i &lt;= n_rec; i++) {
		cache[i].v = -1;  /* value = -1 means cache not used yet */
		cache[i].w = 0;
	}
	(blank = cache + n_rec)-&gt;v = 0;
	return 1;
}

solution solve(int weight, int pos)
{
	int i, w, v, qty;
	solution sol, best = 0, ret;

	if (pos &lt; 0) return blank;

	ret = &amp;cache[weight * n_types + pos];
	if (ret-&gt;v &gt;= 0) return ret;

	w   = items[pos].w;
	v   = items[pos].v;
	qty = items[pos].qty;

	for (i = 0; i &lt;= qty &amp;&amp; weight &gt; 0; i++, weight -= w) {
		sol = solve(weight, pos - 1);
		if (sol-&gt;v + i * v &lt;= ret-&gt;v) continue;

		best = sol;
		ret-&gt;v = best-&gt;v + v * i;
		ret-&gt;n[pos] = i;
	}

	/*  only happens if there are no solution at all, i.e.
	 *  max_weight too small to hold even one item
	 */
	if (ret-&gt;v &lt;= 0) return blank;

	ret-&gt;w = best-&gt;w + w * ret-&gt;n[pos];
	memcpy(ret-&gt;n, best-&gt;n, sizeof(unsigned short) * pos);

	return ret;
}

int main()
{
	int i;
	solution x;

	init_cache();
	x = solve(max_weight, n_types - 1);

	printf(&quot;Taking:\n&quot;);
	for (i = 0; i &lt; n_types; i++) {
		if (! x-&gt;n[i]) continue;
		printf(&quot;  %hu %s\n&quot;, x-&gt;n[i], items[i].name);
	}

	printf(&quot;Weight: %d Value: %d\n&quot;, x-&gt;w, x-&gt;v);

	/* free(cache); */
	return 0;
}
