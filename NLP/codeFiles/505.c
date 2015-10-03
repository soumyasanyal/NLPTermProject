#include &lt;stdio.h&gt;
typedef struct node_t *node, node_t;
struct node_t { int v; node next; };
typedef struct { node head, tail; } slist;

void push(slist *l, node e) {
	if (!l-&gt;head) l-&gt;head = e;
	if (l-&gt;tail)  l-&gt;tail-&gt;next = e;
	l-&gt;tail = e;
}

node removehead(slist *l) {
	node e = l-&gt;head;
	if (e) {
		l-&gt;head = e-&gt;next;
		e-&gt;next = 0;
	}
	return e;
}

void join(slist *a, slist *b) {
	push(a, b-&gt;head);
	a-&gt;tail = b-&gt;tail;
}

void merge(slist *a, slist *b) {
	slist r = {0};
	while (a-&gt;head &amp;&amp; b-&gt;head)
		push(&amp;r, removehead(a-&gt;head-&gt;v &lt;= b-&gt;head-&gt;v ? a : b));

	join(&amp;r, a-&gt;head ? a : b);
	*a = r;
	b-&gt;head = b-&gt;tail = 0;
}

void sort(int *ar, int len)
{
	node_t all[len];

	// array to list
	for (int i = 0; i &lt; len; i++)
		all[i].v = ar[i], all[i].next = i &lt; len - 1 ? all + i + 1 : 0;

	slist list = {all, all + len - 1}, rem, strand = {0},  res = {0};

	for (node e = 0; list.head; list = rem) {
		rem.head = rem.tail = 0;
		while ((e = removehead(&amp;list)))
			push((!strand.head || e-&gt;v &gt;= strand.tail-&gt;v) ? &amp;strand : &amp;rem, e);

		merge(&amp;res, &amp;strand);
	}

	// list to array
	for (int i = 0; res.head; i++, res.head = res.head-&gt;next)
		ar[i] = res.head-&gt;v;
}

void show(char *title, int *x, int len)
{
	printf(&quot;%s &quot;, title);
	for (int i = 0; i &lt; len; i++)
		printf(&quot;%3d &quot;, x[i]);
	putchar('\n');
}

int main(void)
{
	int x[] = {-2,0,-2,5,5,3,-1,-3,5,5,0,2,-4,4,2};
#	define SIZE sizeof(x)/sizeof(int)

	show(&quot;before sort:&quot;, x, SIZE);
	sort(x, sizeof(x)/sizeof(int));
	show(&quot;after sort: &quot;, x, SIZE);

	return 0;
}
