#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef struct list_t list_t, *list;
struct list_t{
	int is_list, ival; /* ival is either the integer value or list length */
	list *lst;
};

list new_list()
{
	list x = malloc(sizeof(list_t));
	x-&gt;ival = 0;
	x-&gt;is_list = 1;
	x-&gt;lst = 0;
	return x;
}

void append(list parent, list child)
{
	parent-&gt;lst = realloc(parent-&gt;lst, sizeof(list) * (parent-&gt;ival + 1));
	parent-&gt;lst[parent-&gt;ival++] = child;
}

list from_string(char *s, char **e, list parent)
{
	list ret = 0;
	if (!parent) parent = new_list();

	while (*s != '\0') {
		if (*s == ']') {
			if (e) *e = s + 1;
			return parent;
		}
		if (*s == '[') {
			ret = new_list();
			ret-&gt;is_list = 1;
			ret-&gt;ival = 0;
			append(parent, ret);
			from_string(s + 1, &amp;s, ret);
			continue;
		}
		if (*s &gt;= '0' &amp;&amp; *s &lt;= '9') {
			ret = new_list();
			ret-&gt;is_list = 0;
			ret-&gt;ival = strtol(s, &amp;s, 10);
			append(parent, ret);
			continue;
		}
		s++;
	}

	if (e) *e = s;
	return parent;
}

void show_list(list l)
{
	int i;
	if (!l) return;
	if (!l-&gt;is_list) {
		printf(&quot;%d&quot;, l-&gt;ival);
		return;
	}

	printf(&quot;[&quot;);
	for (i = 0; i &lt; l-&gt;ival; i++) {
		show_list(l-&gt;lst[i]);
		if (i &lt; l-&gt;ival - 1) printf(&quot;, &quot;);
	}
	printf(&quot;]&quot;);
}

list flatten(list from, list to)
{
	int i;
	list t;

	if (!to) to = new_list();
	if (!from-&gt;is_list) {
		t = new_list();
		*t = *from;
		append(to, t);
	} else
		for (i = 0; i &lt; from-&gt;ival; i++)
			flatten(from-&gt;lst[i], to);
	return to;
}

void delete_list(list l)
{
	int i;
	if (!l) return;
	if (l-&gt;is_list &amp;&amp; l-&gt;ival) {
		for (i = 0; i &lt; l-&gt;ival; i++)
			delete_list(l-&gt;lst[i]);
		free(l-&gt;lst);
	}

	free(l);
}

int main()
{
	list l = from_string(&quot;[1], 2, [[3,4], 5], [[[]]], [[[6]]], 7, 8, []&quot;, 0, 0);

	printf(&quot;Nested: &quot;);
	show_list(l);
	printf(&quot;\n&quot;);

	list flat = flatten(l, 0);
	printf(&quot;Flattened: &quot;);
	show_list(flat);

	/* delete_list(l); delete_list(flat); */
	return 0;
}
