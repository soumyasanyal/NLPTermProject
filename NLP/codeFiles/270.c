#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;unistd.h&gt;

int w = 0, h = 0;
unsigned char *pix;

void refresh(int x, int y)
{
	int i, j, k;
	printf(&quot;\033[H&quot;);
	for (i = k = 0; i &lt; h; putchar('\n'), i++)
		for (j = 0; j &lt; w; j++, k++)
			putchar(pix[k] ? '#' : ' ');
}

void walk()
{
	int dx = 0, dy = 1, i, k;
	int x = w / 2, y = h / 2;

	pix = calloc(1, w * h);
	printf(&quot;\033[H\033[J&quot;);

	while (1) {
		i = (y * w + x);
		if (pix[i]) k = dx, dx = -dy, dy = k;
		else	    k = dy, dy = -dx, dx = k;

		pix[i] = !pix[i];
		printf(&quot;\033[%d;%dH%c&quot;, y + 1, x + 1, pix[i] ? '#' : ' ');

		x += dx, y += dy;

		k = 0;
		if (x &lt; 0) {
			memmove(pix + 1, pix, w * h - 1);
			for (i = 0; i &lt; w * h; i += w) pix[i] = 0;
			x++, k = 1;
		}
		else if (x &gt;= w) {
			memmove(pix, pix + 1, w * h - 1);
			for (i = w-1; i &lt; w * h; i += w) pix[i] = 0;
			x--, k = 1;
		}

		if (y &gt;= h) {
			memmove(pix, pix + w, w * (h - 1));
			memset(pix + w * (h - 1), 0, w);
			y--, k = 1;
		}
		else if (y &lt; 0) {
			memmove(pix + w, pix, w * (h - 1));
			memset(pix, 0, w);
			y++, k = 1;
		}
		if (k) refresh(x, y);
		printf(&quot;\033[%d;%dH\033[31m@\033[m&quot;, y + 1, x + 1);

		fflush(stdout);
		usleep(10000);
	}
}

int main(int c, char **v)
{
	if (c &gt; 1) w = atoi(v[1]);
	if (c &gt; 2) h = atoi(v[2]);
	if (w &lt; 40) w = 40;
	if (h &lt; 25) h = 25;

	walk();
	return 0;
}
