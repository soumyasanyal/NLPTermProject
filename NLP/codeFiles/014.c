#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;sys/stat.h&gt;

// Letter lookup by frequency.  This is to reduce word insertion time.
unsigned char *freq = (void *)&quot;zqxjkvbpygfwmucldrhsnioate&quot;;
int char_to_idx[128];

// Trie structrue of sorts
struct word {
	char *w;
	struct word *next;
};

union node {
	union node *down[10];
	struct word *list[10];
};

int deranged(char *s1, char *s2)
{
	int i;
	for (i = 0; s1[i]; i++)
		if (s1[i] == s2[i]) return 0;
	return 1;
}

int count_letters(char *s, unsigned char *c)
{
	int i, len;
	memset(c, 0, 26);
	for (len = i = 0; s[i]; i++) {
		if (s[i] &lt; 'a' || s[i] &gt; 'z')
			return 0;
		len++, c[char_to_idx[s[i]]]++;
	}
	return len;
}

char * insert(union node *root, char *s, unsigned char *cnt)
{
	int i;
	union node *n;
	struct word *v, *w = 0;

	for (i = 0; i &lt; 25; i++, root = n) {
		if (!(n = root-&gt;down[cnt[i]]))
			root-&gt;down[cnt[i]] = n = calloc(1, sizeof(union node));
	}

	w = malloc(sizeof(struct word));
	w-&gt;w = s;
	w-&gt;next = root-&gt;list[cnt[25]];
	root-&gt;list[cnt[25]] = w;

	for (v = w-&gt;next; v; v = v-&gt;next) {
		if (deranged(w-&gt;w, v-&gt;w))
			return v-&gt;w;
	}
	return 0;
}

int main(int c, char **v)
{
	int i, j = 0;
	char *words;
	struct stat st;

	int fd = open(c &lt; 2 ? &quot;unixdict.txt&quot; : v[1], O_RDONLY);
	if (fstat(fd, &amp;st) &lt; 0) return 1;

	words = malloc(st.st_size);
	read(fd, words, st.st_size);
	close(fd);

	union node root = {{0}};
	unsigned char cnt[26];
	int best_len = 0;
	char *b1, *b2;

	for (i = 0; freq[i]; i++)
		char_to_idx[freq[i]] = i;

	/* count words, change newline to null */
	for (i = j = 0; i &lt; st.st_size; i++) {
		if (words[i] != '\n') continue;
		words[i] = '\0';

		if (i - j &gt; best_len) {
			count_letters(words + j, cnt);
			char *match = insert(&amp;root, words + j, cnt);

			if (match) {
				best_len = i - j;
				b1 = words + j;
				b2 = match;
			}
		}

		j = ++i;
	}

	if (best_len) printf(&quot;longest derangement: %s %s\n&quot;, b1, b2);

	return 0;
}
