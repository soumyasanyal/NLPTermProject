#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;limits.h&gt;

/* Simple recursion method. Using uint64 would have
   been enough for task, if supremely slow */
int count(int sum, int *coins)
{
	return (!*coins || sum &lt; 0)
		? 0
		: !sum  ? 1
			: count(sum - *coins, coins) +
			  count(sum, coins + 1);
}

/* ad hoc 128-bit integer (faster than GMP) */
typedef unsigned long long ull;
typedef struct xint { ull v, c; } xint;
typedef struct node {
	xint x;
	struct node *next;
} node;

xint one = { 1, 0 };

xint countx(register int sum, int *coins)
{
	/* lumping all declarations here to avoid
	   gcc -pedantic C89 mode warnings */
	unsigned int n;

	/* q[i] points to a cyclic buffer of length coins[i] */
	node *buf, **q;
	xint prev, cur;
	register int i, j, carry = 0;

	/* alloc and init buffers */
	for (n = j = 0; coins[n]; j += coins[n++]);
	q = malloc(sizeof(node*) * n);

	q[0] = buf = calloc(j, sizeof(node));
	for (n = 0; coins[n]; n++) {
		if (n)
			q[n] = q[n - 1] + coins[n - 1];

		for (j = 1; j &lt; coins[n]; j++)
			q[n][j - 1].next = q[n] + j;

		q[n][coins[n] - 1].next = q[n];
		q[n]-&gt;x = one;
	}

	/* critical loops. for whatever reason, &quot;while (sum--)&quot; is a lot slower */
	for (j = 0; j &lt; sum; j++) {
		for (i = 0; i &lt; n; i++) {
			/* each int128 buffer is linked via pointers. It avoids
			   a separate look up on array bounds, while -&gt;next is in
			   cache anyway; arrays are bigger, but we had to allocate
			   more than one page regardless */
			q[i] = q[i]-&gt;next;
			cur = q[i]-&gt;x;

			if (i) {
				/* 128-bit integer addition */
				/* don't add high bits until we've seen a carry */
				if (carry)
					cur.c += prev.c;
				if (cur.v &gt;= ~prev.v)
					carry = ++cur.c;
				cur.v += prev.v;
			}
			prev = q[i]-&gt;x = cur;
		}
	}

	free(buf), free(q);
	return prev;
}

void print (xint v)
{
#	define BITS (sizeof(ull) * CHAR_BIT/2)
#	define BASE (1ULL &lt;&lt; BITS)

	int i, k = 63;
	char buf[64] = {0};
	ull n[3];
	n[0] = v.c, n[1] = v.v &gt;&gt; BITS, n[2] = v.v &amp; (BASE - 1);

	while (n[0] || n[1] || n[2])
		for (i = 0; i &lt; 3; n[i++] /= 10)
			if (i &lt; 2)
				n[i + 1] += BASE * (n[i] % 10);
			else
				buf[--k] = '0' + n[2] % 10;

	puts(buf + k);
}

int main()
{
	int us_coins[] = { 100, 50, 25, 10, 5, 1, 0 };
	int eu_coins[] = { 200, 100, 50, 20, 10, 5, 2, 1, 0 };

	printf(&quot;%d\n&quot;, count(100, us_coins + 2));

	print(countx(  1000 * 100, us_coins));
	print(countx( 10000 * 100, us_coins));
	print(countx(100000 * 100, us_coins));

	putchar('\n');

	print(countx(	  1 * 100, eu_coins));
	print(countx(  1000 * 100, eu_coins));
	print(countx( 10000 * 100, eu_coins));
	print(countx(100000 * 100, eu_coins));

	return 0;
}
