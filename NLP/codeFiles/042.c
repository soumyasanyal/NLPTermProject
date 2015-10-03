#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* select the k-th smallest item in array x of length len */
int qselect(int *x, int k, int len)
{
	inline void swap(int a, int b) {
		int t = x[a];
		x[a] = x[b], x[b] = t;
	}

	int left = 0, right = len - 1;
	int pivot, pos, i;

	while (left &lt; right) {
		pivot = x[k];
		swap(k, right);
		for (i = pos = left; i &lt; right; i++) {
			if (x[i] &lt; pivot) {
				swap(i, pos);
				pos++;
			}
		}
		swap(right, pos);
		if (pos == k) break;
		if (pos &lt; k) left = pos + 1;
		else right = pos - 1;
	}
	return x[k];
}

#define N 10000001

int icmp(const void *a, const void *b)
{
	return *(int*)a &lt; *(int*)b ? -1 : *(int*)a &gt; *(int*) b;
}

int main()
{
	int i, med, *x = malloc(sizeof(int) * N);

	/* divide by large value to create many duplicate values */
	for (i = 0; i &lt; N; i++) x[i] = rand()/100000;

	med = qselect(x, N/2, N);

	/* qsort for speed comparison */
	//qsort(x, N, sizeof(int), icmp); med = x[N/2];

	printf(&quot;median is %d\n&quot;, med);

	/* just to show it is the median */
	int less = 0, more = 0, eq = 0;
	for (i = 0; i &lt; N; i++) {
		if	(x[i] &lt; med) less ++;
		else if (x[i] &gt; med) more ++;
		else eq ++;
	}
	printf(&quot;&lt;: %d\n&gt;: %d\n=: %d\n&quot;, less, more, eq);

	return 0;
}
