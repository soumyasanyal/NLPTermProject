#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

//#define BIG_EXAMPLE

typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {
	node_t *nd;	/* target of this edge */
	edge_t *sibling;/* for singly linked list */
	int len;	/* edge cost */
};
struct node_t {
	edge_t *edge;	/* singly linked list of edges */
	node_t *via;	/* where previous node is in shortest path */
	double dist;	/* distance from origining node */
	char name[8];	/* the, er, name */
	int heap_idx;	/* link to heap position for updating distance */
};


/* --- edge management --- */
#ifdef BIG_EXAMPLE
#	define BLOCK_SIZE (1024 * 32 - 1)
#else
#	define BLOCK_SIZE 15
#endif
edge_t *edge_root = 0, *e_next = 0;

/* Don't mind the memory management stuff, they are besides the point.
   Pretend e_next = malloc(sizeof(edge_t)) */
void add_edge(node_t *a, node_t *b, double d)
{
	if (e_next == edge_root) {
		edge_root = malloc(sizeof(edge_t) * (BLOCK_SIZE + 1));
		edge_root[BLOCK_SIZE].sibling = e_next;
		e_next = edge_root + BLOCK_SIZE;
	}
	--e_next;

	e_next-&gt;nd = b;
	e_next-&gt;len = d;
	e_next-&gt;sibling = a-&gt;edge;
	a-&gt;edge = e_next;
}

void free_edges()
{
	for (; edge_root; edge_root = e_next) {
		e_next = edge_root[BLOCK_SIZE].sibling;
		free(edge_root);
	}
}

/* --- priority queue stuff --- */
heap_t *heap;
int heap_len;

void set_dist(node_t *nd, node_t *via, double d)
{
	int i, j;

	/* already knew better path */
	if (nd-&gt;via &amp;&amp; d &gt;= nd-&gt;dist) return;

	/* find existing heap entry, or create a new one */
	nd-&gt;dist = d;
	nd-&gt;via = via;

	i = nd-&gt;heap_idx;
	if (!i) i = ++heap_len;

	/* upheap */
	for (; i &gt; 1 &amp;&amp; nd-&gt;dist &lt; heap[j = i/2]-&gt;dist; i = j)
		(heap[i] = heap[j])-&gt;heap_idx = i;

	heap[i] = nd;
	nd-&gt;heap_idx = i;
}

node_t * pop_queue()
{
	node_t *nd, *tmp;
	int i, j;

	if (!heap_len) return 0;

	/* remove leading element, pull tail element there and downheap */
	nd = heap[1];
	tmp = heap[heap_len--];

	for (i = 1; i &lt; heap_len &amp;&amp; (j = i * 2) &lt;= heap_len; i = j) {
		if (j &lt; heap_len &amp;&amp; heap[j]-&gt;dist &gt; heap[j+1]-&gt;dist) j++;

		if (heap[j]-&gt;dist &gt;= tmp-&gt;dist) break;
		(heap[i] = heap[j])-&gt;heap_idx = i;
	}

	heap[i] = tmp;
	tmp-&gt;heap_idx = i;

	return nd;
}

/* --- Dijkstra stuff; unreachable nodes will never make into the queue --- */
void calc_all(node_t *start)
{
	node_t *lead;
	edge_t *e;

	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead-&gt;edge; e; e = e-&gt;sibling)
			set_dist(e-&gt;nd, lead, lead-&gt;dist + e-&gt;len);
}

void show_path(node_t *nd)
{
	if (nd-&gt;via == nd)
		printf(&quot;%s&quot;, nd-&gt;name);
	else if (!nd-&gt;via)
		printf(&quot;%s(unreached)&quot;, nd-&gt;name);
	else {
		show_path(nd-&gt;via);
		printf(&quot;-&gt; %s(%g) &quot;, nd-&gt;name, nd-&gt;dist);
	}
}

int main(void)
{
#ifndef BIG_EXAMPLE
	int i;

#	define N_NODES ('f' - 'a' + 1)
	node_t *nodes = calloc(sizeof(node_t), N_NODES);

	for (i = 0; i &lt; N_NODES; i++)
		sprintf(nodes[i].name, &quot;%c&quot;, 'a' + i);

#	define E(a, b, c) add_edge(nodes + (a - 'a'), nodes + (b - 'a'), c)
	E('a', 'b', 7);	E('a', 'c', 9); E('a', 'f', 14);
	E('b', 'c', 10);E('b', 'd', 15);E('c', 'd', 11);
	E('c', 'f', 2); E('d', 'e', 6);	E('e', 'f', 9);
#	undef E

#else /* BIG_EXAMPLE */
	int i, j, c;

#	define N_NODES 4000
	node_t *nodes = calloc(sizeof(node_t), N_NODES);

	for (i = 0; i &lt; N_NODES; i++)
		sprintf(nodes[i].name, &quot;%d&quot;, i + 1);

	/* given any pair of nodes, there's about 50% chance they are not
	   connected; if connected, the cost is randomly chosen between 0
	   and 49 (inclusive! see output for consequences) */
	for (i = 0; i &lt; N_NODES; i++) {
		for (j = 0; j &lt; N_NODES; j++) {
			/* majority of runtime is actually spent here */
			if (i == j) continue;
			c = rand() % 100;
			if (c &lt; 50) continue;
			add_edge(nodes + i, nodes + j, c - 50);
		}
	}

#endif
	heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes);
	for (i = 0; i &lt; N_NODES; i++) {
		show_path(nodes + i);
		putchar('\n');
	}

#if 0
	/* real programmers don't free memories (they use Fortran) */
	free_edges();
	free(heap);
	free(nodes);
#endif
	return 0;
}
