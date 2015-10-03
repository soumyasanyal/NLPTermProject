#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef struct node_t node_t, *node, *queue;
struct node_t { int val; node prev, next; };

#define HEAD(q) q-&gt;prev
#define TAIL(q) q-&gt;next
queue q_new()
{
	node q = malloc(sizeof(node_t));
	q-&gt;next = q-&gt;prev = 0;
	return q;
}

int empty(queue q)
{
	return !HEAD(q);
}

void enqueue(queue q, int n)
{
	node nd = malloc(sizeof(node_t));
	nd-&gt;val = n;
	if (!HEAD(q)) HEAD(q) = nd;
	nd-&gt;prev = TAIL(q);
	if (nd-&gt;prev) nd-&gt;prev-&gt;next = nd;
	TAIL(q) = nd;
	nd-&gt;next = 0;
}

int dequeue(queue q, int *val)
{
	node tmp = HEAD(q);
	if (!tmp) return 0;
	*val = tmp-&gt;val;

	HEAD(q) = tmp-&gt;next;
	if (TAIL(q) == tmp) TAIL(q) = 0;
	free(tmp);

	return 1;
}

