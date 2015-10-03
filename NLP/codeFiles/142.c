#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

char target[] = &quot;METHINKS IT IS LIKE A WEASEL&quot;;
char tbl[] = &quot;ABCDEFGHIJKLMNOPQRSTUVWXYZ &quot;;

#define CHOICE (sizeof(tbl) - 1)
#define MUTATE 15
#define COPIES 30

/* returns random integer from 0 to n - 1 */
int irand(int n)
{
	int r, rand_max = RAND_MAX - (RAND_MAX % n);
	while((r = rand()) &gt;= rand_max);
	return r / (rand_max / n);
}

/* number of different chars between a and b */
int unfitness(char *a, char *b)
{
	int i, sum = 0;
	for (i = 0; a[i]; i++)
		sum += (a[i] != b[i]);
	return sum;
}

/* each char of b has 1/MUTATE chance of differing from a */
void mutate(char *a, char *b)
{
	int i;
	for (i = 0; a[i]; i++)
		b[i] = irand(MUTATE) ? a[i] : tbl[irand(CHOICE)];

	b[i] = '\0';
}

int main()
{
	int i, best_i, unfit, best, iters = 0;
	char specimen[COPIES][sizeof(target) / sizeof(char)];

	/* init rand string */
	for (i = 0; target[i]; i++)
		specimen[0][i] = tbl[irand(CHOICE)];
	specimen[0][i] = 0;

	do {
		for (i = 1; i &lt; COPIES; i++)
			mutate(specimen[0], specimen[i]);

		/* find best fitting string */
		for (best_i = i = 0; i &lt; COPIES; i++) {
			unfit = unfitness(target, specimen[i]);
			if(unfit &lt; best || !i) {
				best = unfit;
				best_i = i;
			}
		}

		if (best_i) strcpy(specimen[0], specimen[best_i]);
		printf(&quot;iter %d, score %d: %s\n&quot;, iters++, best, specimen[0]);
	} while (best);

	return 0;
}
