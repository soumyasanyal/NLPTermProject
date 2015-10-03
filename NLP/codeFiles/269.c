#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

/* define a shuffle function. e.g. decl_shuffle(double).
 * advantage: compiler is free to optimize the swap operation without
 *            indirection with pointers, which could be much faster.
 * disadvantage: each datatype needs a separate instance of the function.
 *            for a small funciton like this, it's not very big a deal.
 */
#define decl_shuffle(type)				\
void shuffle_##type(type *list, size_t len) {		\
	int j;						\
	type tmp;					\
	while(len) {					\
		j = irand(len);				\
		if (j != len - 1) {			\
			tmp = list[j];			\
			list[j] = list[len - 1];	\
			list[len - 1] = tmp;		\
		}					\
		len--;					\
	}						\
}							\

/* random integer from 0 to n-1 */
int irand(int n)
{
	int r, rand_max = RAND_MAX - (RAND_MAX % n);
	/* reroll until r falls in a range that can be evenly
	 * distributed in n bins.  Unless n is comparable to
	 * to RAND_MAX, it's not *that* important really. */
	while ((r = rand()) &gt;= rand_max);
	return r / (rand_max / n);
}

/* declare and define int type shuffle function from macro */
decl_shuffle(int);

int main()
{
	int i, x[20];

	for (i = 0; i &lt; 20; i++) x[i] = i;
	for (printf(&quot;before:&quot;), i = 0; i &lt; 20 || !printf(&quot;\n&quot;); i++)
		printf(&quot; %d&quot;, x[i]);

	shuffle_int(x, 20);

	for (printf(&quot;after: &quot;), i = 0; i &lt; 20 || !printf(&quot;\n&quot;); i++)
		printf(&quot; %d&quot;, x[i]);
	return 0;
}
