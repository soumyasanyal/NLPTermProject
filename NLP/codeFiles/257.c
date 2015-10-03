#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

char chr_legal[] = &quot;abcdefghijklmnopqrstuvwxyz0123456789_-./&quot;;
int  chr_idx[256] = {0};
char idx_chr[256] = {0};
 
#define FNAME 0
typedef struct trie_t *trie, trie_t;
struct trie_t {
	trie next[sizeof(chr_legal)]; /* next letter; slot 0 is for file name */
	int eow;
};
 
trie trie_new() { return calloc(sizeof(trie_t), 1); }
 
#define find_word(r, w) trie_trav(r, w, 1)
/* tree traversal: returns node if end of word and matches string, optionally
 * create node if doesn't exist
 */
trie trie_trav(trie root, char * str, int no_create)
{
	int c;
	while (root) {
		if ((c = str[0]) == '\0') {
			if (!root-&gt;eow &amp;&amp; no_create) return 0;
			break;
		}
		if (! (c = chr_idx[c]) ) {
			str++;
			continue;
		}
 
		if (!root-&gt;next[c]) {
			if (no_create) return 0;
			root-&gt;next[c] = trie_new();
		}
		root = root-&gt;next[c];
		str++;
	}
	return root;
}
 
/*  complete traversal of whole tree, calling callback at each end of word node.
 *  similar method can be used to free nodes, had we wanted to do that.
 */
int trie_all(trie root, char path[], int depth, int (*callback)(char *))
{
	int i;
	if (root-&gt;eow &amp;&amp; !callback(path)) return 0;
 
	for (i = 1; i &lt; sizeof(chr_legal); i++) {
		if (!root-&gt;next[i]) continue;
 
		path[depth] = idx_chr[i];
		path[depth + 1] = '\0';
		if (!trie_all(root-&gt;next[i], path, depth + 1, callback))
			return 0;
	}
	return 1;
}
 
void add_index(trie root, char *word, char *fname)
{
	trie x = trie_trav(root, word, 0);
	x-&gt;eow = 1;
 
	if (!x-&gt;next[FNAME])
		x-&gt;next[FNAME] = trie_new();
	x = trie_trav(x-&gt;next[FNAME], fname, 0);
	x-&gt;eow = 1;
}
 
int print_path(char *path)
{
	printf(&quot; %s&quot;, path);
	return 1;
}
 
/*  pretend we parsed text files and got lower cased words: dealing     *
 *  with text file is a whole other animal and would make code too long */
char *files[] = { &quot;f1.txt&quot;, &quot;source/f2.txt&quot;, &quot;other_file&quot; };
char *text[][5] ={{ &quot;it&quot;, &quot;is&quot;, &quot;what&quot;, &quot;it&quot;, &quot;is&quot; },
		 { &quot;what&quot;, &quot;is&quot;, &quot;it&quot;, 0 },
		 { &quot;it&quot;, &quot;is&quot;, &quot;a&quot;, &quot;banana&quot;, 0 }};
 
trie init_tables()
{
	int i, j;
	trie root = trie_new();
	for (i = 0; i &lt; sizeof(chr_legal); i++) {
		chr_idx[(int)chr_legal[i]] = i + 1;
		idx_chr[i + 1] = chr_legal[i];
	}

/* Enable USE_ADVANCED_FILE_HANDLING to use advanced file handling.
 * You need to have files named like above files[], with words in them
 * like in text[][].  Case doesn't matter (told you it's advanced). 
 */
#define USE_ADVANCED_FILE_HANDLING 0
#if USE_ADVANCED_FILE_HANDLING
	void read_file(char * fname) {
		char cmd[1024];
		char word[1024];
		sprintf(cmd, &quot;perl -p -e 'while(/(\\w+)/g) {print lc($1),\&quot;\\n\&quot;}' %s&quot;, fname);
		FILE *in = popen(cmd, &quot;r&quot;);
		while (!feof(in)) {
			fscanf(in, &quot;%1000s&quot;, word);
			add_index(root, word, fname);
		}
		pclose(in);
	};

	read_file(&quot;f1.txt&quot;);
	read_file(&quot;source/f2.txt&quot;);
	read_file(&quot;other_file&quot;);
#else
	for (i = 0; i &lt; 3; i++) {
		for (j = 0; j &lt; 5; j++) {
			if (!text[i][j]) break;
			add_index(root, text[i][j], files[i]);
		}
	}
#endif /*USE_ADVANCED_FILE_HANDLING*/

	return root;
}
 
void search_index(trie root, char *word)
{
	char path[1024];
	printf(&quot;Search for \&quot;%s\&quot;: &quot;, word);
	trie found = find_word(root, word);
 
	if (!found) printf(&quot;not found\n&quot;);
	else {
		trie_all(found-&gt;next[FNAME], path, 0, print_path);
		printf(&quot;\n&quot;);
	}
}
 
int main()
{
	trie root = init_tables();
 
	search_index(root, &quot;what&quot;);
	search_index(root, &quot;is&quot;);
	search_index(root, &quot;banana&quot;);
	search_index(root, &quot;boo&quot;);
	return 0;
}
