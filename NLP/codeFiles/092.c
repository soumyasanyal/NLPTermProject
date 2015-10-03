#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;

#define for_x for (int x = 0; x &lt; w; x++)
#define for_y for (int y = 0; y &lt; h; y++)
#define for_xy for_x for_y
void show(void *u, int w, int h)
{
	int (*univ)[w] = u;
	printf(&quot;\033[H&quot;);
	for_y {
		for_x printf(univ[y][x] ? &quot;\033[07m  \033[m&quot; : &quot;  &quot;);
		printf(&quot;\033[E&quot;);
	}
	fflush(stdout);
}

void evolve(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;
	unsigned new[h][w];

	for_y for_x {
		int n = 0;
		for (int y1 = y - 1; y1 &lt;= y + 1; y1++)
			for (int x1 = x - 1; x1 &lt;= x + 1; x1++)
				if (univ[(y1 + h) % h][(x1 + w) % w])
					n++;

		if (univ[y][x]) n--;
		new[y][x] = (n == 3 || (n == 2 &amp;&amp; univ[y][x]));
	}
	for_y for_x univ[y][x] = new[y][x];
}

void game(int w, int h)
{
	unsigned univ[h][w];
	for_xy univ[y][x] = rand() &lt; RAND_MAX / 10 ? 1 : 0;
	while (1) {
		show(univ, w, h);
		evolve(univ, w, h);
		usleep(200000);
	}
}

int main(int c, char **v)
{
	int w = 0, h = 0;
	if (c &gt; 1) w = atoi(v[1]);
	if (c &gt; 2) h = atoi(v[2]);
	if (w &lt;= 0) w = 30;
	if (h &lt;= 0) h = 30;
	game(w, h);
}
