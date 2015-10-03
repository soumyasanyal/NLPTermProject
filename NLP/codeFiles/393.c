#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef struct { void * data; int pri; } q_elem_t;
typedef struct { q_elem_t *buf; int n, alloc; } pri_queue_t, *pri_queue;

#define priq_purge(q) (q)-&gt;n = 1
#define priq_size(q) ((q)-&gt;n - 1)
/* first element in array not used to simplify indices */
pri_queue priq_new(int size)
{
	if (size &lt; 4) size = 4;

	pri_queue q = malloc(sizeof(pri_queue_t));
	q-&gt;buf = malloc(sizeof(q_elem_t) * size);
	q-&gt;alloc = size;
	q-&gt;n = 1;

	return q;
}

void priq_push(pri_queue q, void *data, int pri)
{
	q_elem_t *b;
	int n, m;

	if (q-&gt;n &gt;= q-&gt;alloc) {
		q-&gt;alloc *= 2;
		b = q-&gt;buf = realloc(q-&gt;buf, sizeof(q_elem_t) * q-&gt;alloc);
	} else
		b = q-&gt;buf;

	n = q-&gt;n++;
	/* append at end, then up heap */
	while ((m = n / 2) &amp;&amp; pri &lt; b[m].pri) {
		b[n] = b[m];
		n = m;
	}
	b[n].data = data;
	b[n].pri = pri;
}

/* remove top item. returns 0 if empty. *pri can be null. */
void * priq_pop(pri_queue q, int *pri)
{
	void *out;
	if (q-&gt;n == 1) return 0;

	q_elem_t *b = q-&gt;buf;

	out = b[1].data;
	if (pri) *pri = b[1].pri;

	/* pull last item to top, then down heap. */
	--q-&gt;n;

	int n = 1, m;
	while ((m = n * 2) &lt; q-&gt;n) {
		if (m + 1 &lt; q-&gt;n &amp;&amp; b[m].pri &gt; b[m + 1].pri) m++;

		if (b[q-&gt;n].pri &lt;= b[m].pri) break;
		b[n] = b[m];
		n = m;
	}

	b[n] = b[q-&gt;n];
	if (q-&gt;n &lt; q-&gt;alloc / 2 &amp;&amp; q-&gt;n &gt;= 16)
		q-&gt;buf = realloc(q-&gt;buf, (q-&gt;alloc /= 2) * sizeof(b[0]));

	return out;
}

/* get the top element without removing it from queue */
void* priq_top(pri_queue q, int *pri)
{
	if (q-&gt;n == 1) return 0;
	if (pri) *pri = q-&gt;buf[1].pri;
	return q-&gt;buf[1].data;
}

/* this is O(n log n), but probably not the best */
void priq_combine(pri_queue q, pri_queue q2)
{
	int i;
	q_elem_t *e = q2-&gt;buf + 1;

	for (i = q2-&gt;n - 1; i &gt;= 1; i--, e++)
		priq_push(q, e-&gt;data, e-&gt;pri);
	priq_purge(q2);
}

int main()
{
	int i, p;
	char *c, *tasks[] ={
		&quot;Clear drains&quot;, &quot;Feed cat&quot;, &quot;Make tea&quot;, &quot;Solve RC tasks&quot;, &quot;Tax return&quot; };
	int pri[] = { 3, 4, 5, 1, 2 };

	/* make two queues */
	pri_queue q = priq_new(0), q2 = priq_new(0);

	/* push all 5 tasks into q */
	for (i = 0; i &lt; 5; i++)
		priq_push(q, tasks[i], pri[i]);

	/* pop them and print one by one */
	while ((c = priq_pop(q, &amp;p)))
		printf(&quot;%d: %s\n&quot;, p, c);

	/* put a million random tasks in each queue */
	for (i = 0; i &lt; 1 &lt;&lt; 20; i++) {
		p = rand() / ( RAND_MAX / 5 );
		priq_push(q, tasks[p], pri[p]);

		p = rand() / ( RAND_MAX / 5 );
		priq_push(q2, tasks[p], pri[p]);
	}

	printf(&quot;\nq has %d items, q2 has %d items\n&quot;, priq_size(q), priq_size(q2));

	/* merge q2 into q; q2 is empty */
	priq_combine(q, q2);
	printf(&quot;After merge, q has %d items, q2 has %d items\n&quot;,
		priq_size(q), priq_size(q2));

	/* pop q until it's empty */
	for (i = 0; (c = priq_pop(q, 0)); i++);
	printf(&quot;Popped %d items out of q\n&quot;, i);

	return 0;
}
