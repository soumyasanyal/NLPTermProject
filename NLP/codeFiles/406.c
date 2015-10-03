#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef int DATA; /* type of data to store in queue */
typedef struct {
	DATA *buf;
	size_t head, tail, alloc;
} queue_t, *queue;

queue q_new()
{
	queue q = malloc(sizeof(queue_t));
	q-&gt;buf = malloc(sizeof(DATA) * (q-&gt;alloc = 4));
	q-&gt;head = q-&gt;tail = 0;
	return q;
}

int empty(queue q)
{
	return q-&gt;tail == q-&gt;head;
}

void enqueue(queue q, DATA n)
{
	if (q-&gt;tail &gt;= q-&gt;alloc) q-&gt;tail = 0;
	q-&gt;buf[q-&gt;tail++] = n;
	if (q-&gt;tail == q-&gt;head) {  /* needs more room */
		q-&gt;buf = realloc(q-&gt;buf, sizeof(DATA) * q-&gt;alloc * 2);
		if (q-&gt;head) {
			memcpy(q-&gt;buf + q-&gt;head + q-&gt;alloc, q-&gt;buf + q-&gt;head,
				sizeof(DATA) * (q-&gt;alloc - q-&gt;head));
			q-&gt;head += q-&gt;alloc;
		} else
			q-&gt;tail = q-&gt;alloc;
		q-&gt;alloc *= 2;
	}
}

int dequeue(queue q, DATA *n)
{
	if (q-&gt;head == q-&gt;tail) return 0;
	*n = q-&gt;buf[q-&gt;head++];
	if (q-&gt;head &gt;= q-&gt;alloc) { /* reduce allocated storage no longer needed */
		q-&gt;head = 0;
		if (q-&gt;alloc &gt;= 512 &amp;&amp; q-&gt;tail &lt; q-&gt;alloc / 2)
			q-&gt;buf = realloc(q-&gt;buf, sizeof(DATA) * (q-&gt;alloc/=2));
	}
	return 1;
}
