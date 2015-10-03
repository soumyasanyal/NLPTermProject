#include &lt;stdio.h&gt;#include &lt;string.h&gt;

typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char c;
} *node;

struct node_t pool[256] = {{0}};
node qqq[255], *q = qqq - 1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[1024];

node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_nodes++;
	if (freq) n-&gt;c = c, n-&gt;freq = freq;
	else {
		n-&gt;left = a, n-&gt;right = b;
		n-&gt;freq = a-&gt;freq + b-&gt;freq;
	}
	return n;
}

/* priority queue */
void qinsert(node n)
{
	int j, i = qend++;
	while ((j = i / 2)) {
		if (q[j]-&gt;freq &lt;= n-&gt;freq) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}

node qremove()
{
	int i, l;
	node n = q[i = 1];

	if (qend &lt; 2) return 0;
	qend--;
	while ((l = i * 2) &lt; qend) {
		if (l + 1 &lt; qend &amp;&amp; q[l + 1]-&gt;freq &lt; q[l]-&gt;freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];
	return n;
}

/* walk the tree and put 0s and 1s */
void build_code(node n, char *s, int len)
{
	static char *out = buf;
	if (n-&gt;c) {
		s[len] = 0;
		strcpy(out, s);
		code[n-&gt;c] = out;
		out += len + 1;
		return;
	}

	s[len] = '0'; build_code(n-&gt;left,  s, len + 1);
	s[len] = '1'; build_code(n-&gt;right, s, len + 1);
}

void init(char *s)
{
	int i, freq[128] = {0};
	char c[16];

	while (*s) freq[(int)*s++]++;

	for (i = 0; i &lt; 128; i++)
		if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));

	while (qend &gt; 2) 
		qinsert(new_node(0, 0, qremove(), qremove()));

	build_code(q[1], c, 0);
}

void encode(char *s, char *out)
{
	while (*s) {
		strcpy(out, code[*s]);
		out += strlen(code[*s++]);
	}
}

void decode(char *s, node t)
{
	node n = t;
	while (*s) {
		if (*s++ == '0') n = n-&gt;left;
		else n = n-&gt;right;

		if (n-&gt;c) putchar(n-&gt;c), n = t;
	}

	putchar('\n');
	if (t != n) printf(&quot;garbage input\n&quot;);
}

int main(void)
{
	int i;
	char *str = &quot;this is an example for huffman encoding&quot;, buf[1024];

	init(str);
	for (i = 0; i &lt; 128; i++)
		if (code[i]) printf(&quot;'%c': %s\n&quot;, i, code[i]);

	encode(str, buf);
	printf(&quot;encoded: %s\n&quot;, buf);

	printf(&quot;decoded: &quot;);
	decode(buf, q[1]);

	return 0;
}
