#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define CW 10	/* cell width. This decides how big the output is */

typedef struct cell_t cell_t, *cell;

enum { N, E, S, W, V };
struct cell_t {
	unsigned int flags;
	cell prev, next, nei[4]; /* neighbors */
};

int sx, sy, sz, w, h;

#define C(y, x) c[(y) * w + x]
#define P(y, x) pix[(y) * w2 + x]
void draw_maze(cell *c)
{
#define FOR(a, b) for(a = 0; a &lt; b; a++)
	FILE *fp;
	int w2 = w * CW + 8, h2 = h * CW + 7;
	char *pix = malloc(w2 * h2);
	memset(pix, 200, w2 * h2);

	void draw_face(int x, int y, int ww, int hh, int px, int py) {
		int i, j, k, l;
		cell t;

		px += 2, py += 2;
		for (i = py; i &lt;= py + hh * CW; i++)
			memset(&amp;P(i, px), 0, ww * CW+1);

		px++, py++;
#		define mark(y, x) P(py + CW*i + y, px + CW*j + x) = 255
		FOR (i, hh) FOR (j, ww) {
			FOR(k, CW - 1) FOR(l, CW - 1) mark(k, l);

			t = C(y + i, x + j);
			if (t-&gt;flags &amp; (1 &lt;&lt; N))
				FOR (l, CW - 1) mark(-1, l);
			if (t-&gt;flags &amp; (1 &lt;&lt; S))
				FOR (l, CW - 1) mark(CW - 1, l);
			if (t-&gt;flags &amp; (1 &lt;&lt; E))
				FOR (l, CW - 1) mark(l, CW - 1);
			if (t-&gt;flags &amp; (1 &lt;&lt; W))
				FOR (l, CW - 1) mark(l, -1);
		}
	}

	draw_face(0, 0, sx, sy, 0, 0);
	draw_face(0, sy, sx, sz, 0, CW*sy + 1);
	draw_face(sx, sy, sy, sz, CW*sx + 1, CW*sy + 1);
	draw_face(sx + sy, sy, sx, sz, CW*(sx + sy) + 2, CW*sy + 1);
	draw_face(sx + sy + sx, sy, sy, sz, CW*(sx + sy + sx) + 3, CW*sy + 1);
	draw_face(sx + sy, sy + sz, sx, sy, CW*(sx + sy) + 2, CW*(sy + sz) + 2);

	fp = fopen(&quot;maze.pgm&quot;, &quot;w+&quot;);
	fprintf(fp, &quot;P5\n%d %d\n255\n&quot;, w2, h2);
	fwrite(pix, 1, w2 * h2, fp);
	fclose(fp);
}

cell rand_neighbor(cell x)
{
	cell r = 0;
	int i, c = 1;
	for (i = N; i &lt;= W; i++) {
		if (!x-&gt;nei[i] || (x-&gt;nei[i]-&gt;flags &amp; (1 &lt;&lt; V)))
			continue;
		if (rand() % c++ == 0)
			r = x-&gt;nei[i];
	}
	return r;
}

void link_cells(cell a, cell b)
{
	int i;
	for (i = N; i &lt;= W; i++) {
		if (a-&gt;nei[i] != b) continue;
		a-&gt;flags |= 1 &lt;&lt; i;
		break;
	}
	for (i = N; i &lt;= W; i++) {
		if (b-&gt;nei[i] != a) continue;
		b-&gt;flags |= 1 &lt;&lt; i;
		break;
	}
}

void walk(cell head)
{
	cell tail = head, p, n;

	while (head) {
		for (p = head; p; p = n) {
			p-&gt;flags |= 1 &lt;&lt; V;
			n = rand_neighbor(p);
			if (!n) break;
			tail-&gt;next = n;
			n-&gt;prev = tail;

			tail = n;
			link_cells(p, n);
		}
		while (head &amp;&amp; !rand_neighbor(head)) head = head-&gt;next;
	}
}

void make_maze(void)
{
	int i, j;
	int n = (sx * sy + sx * sz + sy * sz) * 2;
	cell t, *c;
	cell_t * cells;

	w = 2 * sx + 2 * sy, h = sy * 2 + sz;
	cells = calloc(sizeof(cell_t), n);
	c = calloc(sizeof(cell), w * h);

	for (i = 0; i &lt; sy; i++)
		for (j = 0; j &lt; sx; j++)
			C(i, j) = cells + --n;
	for (; i &lt; sy + sz; i++)
		for (j = 0; j &lt; w; j++)
			C(i, j) = cells + --n;
	for (; i &lt; h; i++)
		for (j = sx + sy; j &lt; w - sy; j++)
			C(i, j) = cells + --n;

	for (i = 0; i &lt; h; i++) {
		for (j = 0; j &lt; w; j++) {
			t = C(i, j);
			if (!t) continue;
			if (i) t-&gt;nei[N] = C(i - 1, j);
			if (i &lt; h - 1) t-&gt;nei[S] = C(i + 1, j);
			if (j) t-&gt;nei[W] = C(i, j - 1);
			if (j &lt; w - 1) t-&gt;nei[E] = C(i, j + 1);
		}
	}

	for (j = 0; j &lt; sx; j++) {
		C(0, j)-&gt;nei[N] = C(sy, w - sy - j - 1);
		C(sy, w - sy - j - 1)-&gt;nei[N] = C(0, j);

		C(h - sy - 1, j)-&gt;nei[S] = C(h - 1, w - sy - j - 1);
		C(h - 1, w - sy - j - 1)-&gt;nei[S] = C(h - sy - 1, j);
	}

	for (i = sy; i &lt; sy + sz; i++) {
		C(i, 0)-&gt;nei[W] = C(i, w - 1);
		C(i, w - 1)-&gt;nei[E] = C(i, 0);
	}

	for (i = 0; i &lt; sy; i++) {
		C(i, 0)-&gt;nei[W] = C(sy, w - sy + i);
		C(sy, w - sy + i)-&gt;nei[N] = C(i, 0);

		C(i, sx - 1)-&gt;nei[E] = C(sy, sx + sy - i - 1);
		C(sy, sx + sy - i - 1)-&gt;nei[N] = C(i, sx - 1);

		C(h - sy - 1, sx + i)-&gt;nei[S] = C(h - 1 - i, sx + sy);
		C(h - 1 - i, sx + sy)-&gt;nei[W] = C(h - sy - 1, sx + i);

		C(sy + sz + i, w - sy - 1)-&gt;nei[E] = C(sy + sz - 1, w - sy + i);
		C(sy + sz - 1, w - sy + i)-&gt;nei[S] = C(sy + sz + i, w - sy - 1);
	}

	walk(C(0, 0));
	draw_maze(c);
}

int main(int c, char **v)
{
	if (c &lt; 2 || (sx = atoi(v[1])) &lt;= 0) sx = 10;
	if (c &lt; 3 || (sy = atoi(v[2])) &lt;= 0) sy = sx;
	if (c &lt; 4 || (sz = atoi(v[3])) &lt;= 0) sz = sy;

	make_maze();

	return 0;
}
