#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;

enum { empty = 0, tree = 1, fire = 2 };
char *disp[] = {&quot;  &quot;, &quot;\033[32m/\\\033[m&quot;, &quot;\033[07;31m/\\\033[m&quot;};
double tree_prob = 0.01, burn_prob = 0.0001;

#define for_x for (int x = 0; x &lt; w; x++)
#define for_y for (int y = 0; y &lt; h; y++)
#define for_yx for_y for_x
#define chance(x) (rand() &lt; RAND_MAX * x)
void evolve(int w, int h)
{
	unsigned univ[h][w], new[h][w];
	for_yx new[y][x] = univ[y][x] = chance(tree_prob) ? tree : empty;

show:	printf(&quot;\033[H&quot;);
	for_y {
		for_x printf(disp[univ[y][x]]);
		printf(&quot;\033[E&quot;);
	}
	fflush(stdout);

	for_yx {
		switch (univ[y][x]) {
		case fire:	new[y][x] = empty;
				break;
		case empty:	if (chance(tree_prob)) new[y][x] = tree;
				break;
		default:
			for (int y1 = y - 1; y1 &lt;= y + 1; y1++) {
				if (y1 &lt; 0 || y1 &gt;= h) continue;
				for (int x1 = x - 1; x1 &lt;= x + 1; x1++) {
					if (x1 &lt; 0 || x1 &gt;= w) continue;
					if (univ[y1][x1] != fire) continue;

					new[y][x] = fire;
					goto burn;
				}
			}

			burn:
			if (new[y][x] == tree &amp;&amp; chance(burn_prob))
				new[y][x] = fire;
		}
	}

	for_yx { univ[y][x] = new[y][x]; }
	//usleep(100000);
	goto show;
}
 
int main(int c, char **v)
{
	//srand(time(0));
	int w = 0, h = 0;

	if (c &gt; 1) w = atoi(v[1]);
	if (c &gt; 2) h = atoi(v[2]);
	if (w &lt;= 0) w = 30;
	if (h &lt;= 0) h = 30;

	evolve(w, h);
}
