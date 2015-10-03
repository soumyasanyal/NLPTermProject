#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;

char input[] =
	&quot;des_system_lib   std synopsys std_cell_lib des_system_lib dw02 dw01 ramlib ieee\n&quot;
	&quot;dw01             ieee dw01 dware gtech\n&quot;
	&quot;dw02             ieee dw02 dware\n&quot;
	&quot;dw03             std synopsys dware dw03 dw02 dw01 ieee gtech\n&quot;
	&quot;dw04             dw04 ieee dw01 dware gtech\n&quot;
	&quot;dw05             dw05 ieee dware\n&quot;
	&quot;dw06             dw06 ieee dware\n&quot;
	&quot;dw07             ieee dware\n&quot;
	&quot;dware            ieee dware\n&quot;
	&quot;gtech            ieee gtech\n&quot;
	&quot;ramlib           std ieee\n&quot;
	&quot;std_cell_lib     ieee std_cell_lib\n&quot;
	&quot;synopsys\n&quot;
	&quot;cycle_11	  cycle_12\n&quot;
	&quot;cycle_12	  cycle_11\n&quot;
	&quot;cycle_21	  dw01 cycle_22 dw02 dw03\n&quot;
	&quot;cycle_22	  cycle_21 dw01 dw04&quot;;

typedef struct item_t item_t, *item;
struct item_t { char *name; int *deps, n_deps, idx, depth; };

int get_item(item *list, int *len, char *name)
{
	int i;
	item lst = *list;

	for (i = 0; i &lt; *len; i++)
		if (!strcmp(lst[i].name, name)) return i;

	lst = *list = realloc(lst, ++*len * sizeof(item_t));
	i = *len - 1;
	memset(lst + i, 0, sizeof(item_t));
	lst[i].idx = i;
	lst[i].name = name;
	return i;
}

void add_dep(item it, int i)
{
	if (it-&gt;idx == i) return;
	it-&gt;deps = realloc(it-&gt;deps, (it-&gt;n_deps + 1) * sizeof(int));
	it-&gt;deps[it-&gt;n_deps++] = i;
}

int parse_input(item *ret)
{
	int n_items = 0;
	int i, parent, idx;
	item list = 0;

	char *s, *e, *word, *we;
	for (s = input; ; s = 0) {
		if (!(s = strtok_r(s, &quot;\n&quot;, &amp;e))) break;

		for (i = 0, word = s; ; i++, word = 0) {
			if (!(word = strtok_r(word, &quot; \t&quot;, &amp;we))) break;
			idx = get_item(&amp;list, &amp;n_items, word);

			if (!i) parent = idx;
			else    add_dep(list + parent, idx);
		}
	}

	*ret = list;
	return n_items;
}

/* recursively resolve compile order; negative means loop */
int get_depth(item list, int idx, int bad)
{
	int max, i, t;

	if (!list[idx].deps)
		return list[idx].depth = 1;

	if ((t = list[idx].depth) &lt; 0) return t;

	list[idx].depth = bad;
	for (max = i = 0; i &lt; list[idx].n_deps; i++) {
		if ((t = get_depth(list, list[idx].deps[i], bad)) &lt; 0) {
			max = t;
			break;
		}
		if (max &lt; t + 1) max = t + 1;
	}
	return list[idx].depth = max;
}

int main()
{
	int i, j, n, bad = -1, max, min;
	item items;
	n = parse_input(&amp;items);

	for (i = 0; i &lt; n; i++)
		if (!items[i].depth &amp;&amp; get_depth(items, i, bad) &lt; 0) bad--;

	for (i = 0, max = min = 0; i &lt; n; i++) {
		if (items[i].depth &gt; max) max = items[i].depth;
		if (items[i].depth &lt; min) min = items[i].depth;
	}

	printf(&quot;Compile order:\n&quot;);
	for (i = min; i &lt;= max; i++) {
		if (!i) continue;

		if (i &lt; 0) printf(&quot;   [unorderable]&quot;);
		else	   printf(&quot;%d:&quot;, i);

		for (j = 0; j &lt; n || !putchar('\n'); j++)
			if (items[j].depth == i)
				printf(&quot; %s&quot;, items[j].name);
	}

	return 0;
}
