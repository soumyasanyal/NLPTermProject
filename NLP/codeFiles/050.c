#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef struct letter_group_t {
	char c;
	int count;
} *letter_p;

struct letter_group_t all_letters[26];
letter_p letters[26];

/* counts how many of each letter is in a string, used later 
 * to generate permutations
 */
int count_letters(char *s)
{
	int i, c;
	for (i = 0; i &lt; 26; i++) {
		all_letters[i].count = 0;
		all_letters[i].c = i + 'a';
	}
	while (*s != '\0') {
		i = *(s++);

		/* don't want to deal with bad inputs */
		if (i &lt; 'a' || i &gt; 'z') {
			fprintf(stderr, &quot;Abort: Bad string %s\n&quot;, s);
			exit(1);
		}

		all_letters[i - 'a'].count++;
	}
	for (i = 0, c = 0; i &lt; 26; i++)
		if (all_letters[i].count)
			letters[c++] = all_letters + i;

	return c;
}

int least_overlap, seq_no;
char out[100], orig[100], best[100];

void permutate(int n_letters, int pos, int overlap)
{
	int i, ol;
	if (pos &lt; 0) {
                /* if enabled will show all shuffles no worse than current best */
	//	printf(&quot;%s: %d\n&quot;, out, overlap);

                /* if better than current best, replace it and reset counter */
		if (overlap &lt; least_overlap) {
			least_overlap = overlap;
			seq_no = 0;
		}

                /* the Nth best tie has 1/N chance of being kept, so all ties
                 * have equal chance of being selected even though we don't
                 * how many there are before hand
                 */
		if ( (double)rand() / (RAND_MAX + 1.0) * ++seq_no &lt;= 1)
			strcpy(best, out);

		return;
	}

        /* standard &quot;try take the letter; try take not&quot; recursive method */
	for (i = 0; i &lt; n_letters; i++) {
		if (!letters[i]-&gt;count) continue;

		out[pos] = letters[i]-&gt;c;
		letters[i]-&gt;count --;
		ol = (letters[i]-&gt;c == orig[pos]) ? overlap + 1 : overlap;

                /* but don't try options that's already worse than current best */
		if (ol &lt;= least_overlap)
			permutate(n_letters, pos - 1, ol);

		letters[i]-&gt;count ++;
	}
	return;
}

void do_string(char *str)
{
	least_overlap = strlen(str);
	strcpy(orig, str);

	seq_no = 0;
	out[least_overlap] = '\0';
	least_overlap ++;

	permutate(count_letters(str), least_overlap - 2, 0);
	printf(&quot;%s -&gt; %s, overlap %d\n&quot;, str, best, least_overlap);
}

int main()
{
	srand(time(0));
	do_string(&quot;abracadebra&quot;);
	do_string(&quot;grrrrrr&quot;);
	do_string(&quot;elk&quot;);
	do_string(&quot;seesaw&quot;);
	do_string(&quot;&quot;);
	return 0;
}
