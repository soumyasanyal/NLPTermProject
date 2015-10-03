#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

inline
void merge(int *left, int l_len, int *right, int r_len, int *out)
{
	int i, j, k;
	for (i = j = k = 0; i &lt; l_len &amp;&amp; j &lt; r_len; )
		out[k++] = left[i] &lt; right[j] ? left[i++] : right[j++];

	while (i &lt; l_len) out[k++] = left[i++];
	while (j &lt; r_len) out[k++] = right[j++];
}

/* inner recursion of merge sort */
void recur(int *buf, int *tmp, int len)
{
	int l = len / 2;
	if (len &lt;= 1) return;

	/* note that buf and tmp are swapped */
	recur(tmp, buf, l);
	recur(tmp + l, buf + l, len - l);

	merge(tmp, l, tmp + l, len - l, buf);
}

/* preparation work before recursion */
void merge_sort(int *buf, int len)
{
	/* call alloc, copy and free only once */
	int *tmp = malloc(sizeof(int) * len);
	memcpy(tmp, buf, sizeof(int) * len);

	recur(buf, tmp, len);

	free(tmp);
}

int main()
{
#	define LEN 20
	int i, x[LEN];

	for (i = 0; i &lt; LEN; i++)
		x[i] = rand() % LEN;

	puts(&quot;before sort:&quot;);
	for (i = 0; i &lt; LEN; i++) printf(&quot;%d &quot;, x[i]);
	putchar('\n');

	merge_sort(x, LEN);

	puts(&quot;after sort:&quot;);
	for (i = 0; i &lt; LEN; i++) printf(&quot;%d &quot;, x[i]);
	putchar('\n');

	return 0;
}
