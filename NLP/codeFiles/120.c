#include &lt;pthread.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;stdarg.h&gt;

#define N 5
char *names[N] = { &quot;Aristotle&quot;, &quot;Kant&quot;, &quot;Spinoza&quot;, &quot;Marx&quot;, &quot;Russell&quot; };
pthread_mutex_t forks[N];

#define M 5 /* think bubbles */
char *topic[M] = { &quot;Spaghetti!&quot;, &quot;Life&quot;, &quot;Universe&quot;, &quot;Everything&quot;, &quot;Bathroom&quot; };

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define xy(x, y) printf(&quot;\033[%d;%dH&quot;, x, y)
#define clear_eol(x) print(x, 12, &quot;\033[K&quot;)
void print(int y, int x, char *fmt, ...)
{
	static pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;
	va_list ap;
	va_start(ap, fmt);

	lock(&amp;screen);
	xy(y + 1, x), vprintf(fmt, ap);
	xy(N + 1, 1), fflush(stdout);
	unlock(&amp;screen);
}

void eat(int id)
{
	int f[2], ration, i; /* forks */
	f[0] = f[1] = id;

	/* make some (but not all) philosophers leftie.
	   could have been f[!id] = (id + 1) %N; for example */
	f[id &amp; 1] = (id + 1) % N;

	clear_eol(id);
	print(id, 12, &quot;..oO (forks, need forks)&quot;);

	for (i = 0; i &lt; 2; i++) {
		lock(forks + f[i]);
		if (!i) clear_eol(id);

		print(id, 12 + (f[i] != id) * 6, &quot;fork%d&quot;, f[i]);
		/* delay 1 sec to clearly show the order of fork acquisition */
		sleep(1);
	}

	for (i = 0, ration = 3 + rand() % 8; i &lt; ration; i++)
		print(id, 24 + i * 4, &quot;nom&quot;), sleep(1);

	/* done nomming, give up forks (order doesn't matter) */
	for (i = 0; i &lt; 2; i++) unlock(forks + f[i]);
}

void think(int id)
{
	int i, t;
	char buf[64] = {0};

	do {
		clear_eol(id);
		sprintf(buf, &quot;..oO (%s)&quot;, topic[t = rand() % M]);

		for (i = 0; buf[i]; i++) {
			print(id, i+12, &quot;%c&quot;, buf[i]);
			if (i &lt; 5) usleep(200000);
		}
		usleep(500000 + rand() % 1000000);
	} while (t);
}

void* philosophize(void *a)
{
	int id = *(int*)a;
	print(id, 1, &quot;%10s&quot;, names[id]);
	while(1) think(id), eat(id);
}

int main()
{
	int i, id[N];
	pthread_t tid[N];

	for (i = 0; i &lt; N; i++)
		pthread_mutex_init(forks + (id[i] = i), 0);

	for (i = 0; i &lt; N; i++)
		pthread_create(tid + i, 0, philosophize, id + i);

	/* wait forever: the threads don't actually stop */
	return pthread_join(tid[0], 0);
}
