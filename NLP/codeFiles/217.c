#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef unsigned long long ham;

size_t alloc = 0, n = 1;
ham *q = 0;

void qpush(ham h)
{
	int i, j;
	if (alloc &lt;= n) {
		alloc = alloc ? alloc * 2 : 16;
		q = realloc(q, sizeof(ham) * alloc);
	}

	for (i = n++; (j = i/2) &amp;&amp; q[j] &gt; h; q[i] = q[j], i = j);
	q[i] = h;
}

ham qpop()
{
	int i, j;
	ham r, t;
	/* outer loop for skipping duplicates */
	for (r = q[1]; n &gt; 1 &amp;&amp; r == q[1]; q[i] = t) {
		/* inner loop is the normal down heap routine */
		for (i = 1, t = q[--n]; (j = i * 2) &lt; n;) {
			if (j + 1 &lt; n &amp;&amp; q[j] &gt; q[j+1]) j++;
			if (t &lt;= q[j]) break;
			q[i] = q[j], i = j;
		}
	}

	return r;
}

int main()
{
	int i;
	ham h;

	for (qpush(i = 1); i &lt;= 1691; i++) {
		/* takes smallest value, and queue its multiples */
		h = qpop();
		qpush(h * 2);
		qpush(h * 3);
		qpush(h * 5);

		if (i &lt;= 20 || i == 1691)
			printf(&quot;%6d: %llu\n&quot;, i, h);
	}

	/* free(q); */
	return 0;
}
