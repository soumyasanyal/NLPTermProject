#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;locale.h&gt;

int locale_ok = 0;

wchar_t s_suits[] = L&quot;♠♥♦♣&quot;;
/* if your file can't contain unicode, use the next line instead */
//wchar_t s_suits[] = L&quot;\x2660\x2665\x2666\x2663&quot;;

char *s_suits_ascii[] = { &quot;S&quot;, &quot;H&quot;, &quot;D&quot;, &quot;C&quot; };
char *s_nums[] = { &quot;WHAT&quot;,
	&quot;A&quot;, &quot;2&quot;, &quot;3&quot;, &quot;4&quot;, &quot;5&quot;, &quot;6&quot;, &quot;7&quot;, &quot;8&quot;, &quot;9&quot;, &quot;10&quot;, &quot;J&quot;, &quot;Q&quot;, &quot;K&quot;,
	&quot;OVERFLOW&quot;
};

typedef struct { int suit, number, _s; } card_t, *card;
typedef struct { int n; card_t cards[52]; } deck_t, *deck;

void show_card(card c)
{
	if (locale_ok)
		printf(&quot; %lc%s&quot;, s_suits[c-&gt;suit], s_nums[c-&gt;number]);
	else
		printf(&quot; %s%s&quot;, s_suits_ascii[c-&gt;suit], s_nums[c-&gt;number]);
}

deck new_deck()
{
	int i, j, k;
	deck d = malloc(sizeof(deck_t));
	d-&gt;n = 52;
	for (i = k = 0; i &lt; 4; i++)
		for (j = 1; j &lt;= 13; j++, k++) {
			d-&gt;cards[k].suit = i;
			d-&gt;cards[k].number = j;
		}
	return d;
}

void show_deck(deck d)
{
	int i;
	printf(&quot;%d cards:&quot;, d-&gt;n);
	for (i = 0; i &lt; d-&gt;n; i++)
		show_card(d-&gt;cards + i);
	printf(&quot;\n&quot;);
}

int cmp_card(const void *a, const void *b)
{
	int x = ((card)a)-&gt;_s, y = ((card)b)-&gt;_s;
	return x &lt; y ? -1 : x &gt; y;
}

card deal_card(deck d)
{
	if (!d-&gt;n) return 0;
	return d-&gt;cards + --d-&gt;n;
}

void shuffle_deck(deck d)
{
	int i;
	for (i = 0; i &lt; d-&gt;n; i++)
		d-&gt;cards[i]._s = rand();
	qsort(d-&gt;cards, d-&gt;n, sizeof(card_t), cmp_card);
}

int main()
{
	int i, j;
	deck d = new_deck();

	locale_ok = (0 != setlocale(LC_CTYPE, &quot;&quot;));

	printf(&quot;New deck, &quot;); show_deck(d);

	printf(&quot;\nShuffle and deal to three players:\n&quot;);
	shuffle_deck(d);
	for (i = 0; i &lt; 3; i++) {
		for (j = 0; j &lt; 5; j++)
			show_card(deal_card(d));
		printf(&quot;\n&quot;);
	}
	printf(&quot;Left in deck &quot;); show_deck(d);

	/* freeing the data struct requires just free(), but it depends on the
	 * situation: there might be cards dealt out somewhere, which is not
	 * in the scope of this task.
	 */
	//free(d);
	return 0;
}
