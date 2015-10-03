#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;string.h&gt;

typedef struct { char *key, *word; int cnt; } kw_t;

int lst_cmp(const void *a, const void *b)
{
	return strcmp(((kw_t*)a)-&gt;key, ((kw_t*)b)-&gt;key);
}

/* Bubble sort.  Faster than stock qsort(), believe it or not */
void sort_letters(char *s)
{
	int i, j;
	char t;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i + 1; s[j] != '\0'; j++)
			if (s[j] &lt; s[i]) {
				t = s[j]; s[j] = s[i]; s[i] = t;
			}
	}
}

int main()
{
	struct stat s;
	char *words, *keys;
	size_t i, j, k, longest, offset;
	int n_word = 0;
	kw_t *list;

	int fd = open(&quot;unixdict.txt&quot;, O_RDONLY);
	if (fd == -1) return 1;
	fstat(fd, &amp;s);
	words = malloc(s.st_size * 2);
	keys  = words + s.st_size;

	read(fd, words, s.st_size);
	memcpy(keys, words, s.st_size);

	/* change newline to null for easy use; sort letters in keys */
	for (i = j = 0; i &lt; s.st_size; i++) {
		if (words[i] == '\n') {
			words[i] = keys[i] = '\0';
			sort_letters(keys + j);
			j = i + 1;
			n_word ++;
		}
	}

	list = calloc(n_word, sizeof(kw_t));

	/* make key/word pointer pairs for sorting */
	for (i = j = k = 0; i &lt; s.st_size; i++) {
		if (words[i] == '\0') {
			list[j].key = keys + k;
			list[j].word = words + k;
			k = i + 1;
			j++;
		}
	}

	qsort(list, n_word, sizeof(kw_t), lst_cmp);

	/* count each key's repetition */
	for (i = j = k = offset = longest = 0; i &lt; n_word; i++) {
		if (!strcmp(list[i].key, list[j].key)) {
			++k;
			continue;
		}

		/* move current longest to begining of array */
		if (k &lt; longest) {
			k = 0;
			j = i;
			continue;
		}

		if (k &gt; longest) offset = 0;

		while (j &lt; i) list[offset++] = list[j++];
		longest = k;
		k = 0;
	}

	/* show the longest */
	for (i = 0; i &lt; offset; i++) {
		printf(&quot;%s &quot;, list[i].word);
		if (i &lt; n_word - 1 &amp;&amp; strcmp(list[i].key, list[i+1].key))
			printf(&quot;\n&quot;);
	}

	/* free(list); free(words); */
	close(fd);
	return 0;
}
