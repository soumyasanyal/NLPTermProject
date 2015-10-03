#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;

typedef struct { int *x, n; } tower;
tower *new_tower(int cap)
{
	tower *t = calloc(1, sizeof(tower) + sizeof(int) * cap);
	t-&gt;x = (int*)(t + 1);
	return t;
}

tower *t[3];
int height;

void text(int y, int i, int d, char *s)
{
	printf(&quot;\033[%d;%dH&quot;, height - y + 1, (height + 1) * (2 * i + 1) - d);
	while (d--) printf(s);
}

void add_disk(int i, int d)
{
	t[i]-&gt;x[t[i]-&gt;n++] = d;
	text(t[i]-&gt;n, i, d, &quot;==&quot;);

	usleep(100000);
	fflush(stdout);
}

int remove_disk(int i)
{
	int d = t[i]-&gt;x[--t[i]-&gt;n];
	text(t[i]-&gt;n + 1, i, d, &quot;  &quot;);
	return d;
}

void move(int n, int from, int to, int via)
{
	if (!n) return;

	move(n - 1, from, via, to);
	add_disk(to, remove_disk(from));
	move(n - 1, via, to, from);
}

int main(int c, char *v[])
{
	puts(&quot;\033[H\033[J&quot;);

	if (c &lt;= 1 || (height = atoi(v[1])) &lt;= 0)
		height = 8;
	for (c = 0; c &lt; 3; c++)	 t[c] = new_tower(height);
	for (c = height; c; c--) add_disk(0, c);

	move(height, 0, 2, 1);

	text(1, 0, 1, &quot;\n&quot;);
	return 0;
}
