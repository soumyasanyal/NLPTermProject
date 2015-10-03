#include &lt;stdlib.h&gt;#include &lt;string.h&gt;
#include &lt;stdio.h&gt;
#include &lt;assert.h&gt;


#define MAXLEN 100
typedef char TWord[MAXLEN];


typedef struct WordsArray {
    TWord *words;
    size_t len;
} WordsArray;


int is_ordered_word(const TWord word) {
    assert(word != NULL);
    int i;

    for (i = 0; word[i] != '\0'; i++)
        if (word[i] &gt; word[i + 1] &amp;&amp; word[i + 1] != '\0')
            return 0;

    return 1;
}


void array_append(WordsArray *words_array, const TWord new_word) {
    assert(words_array != NULL);
    assert(new_word != NULL);
    assert((words_array-&gt;len == 0) == (words_array-&gt;words == NULL));

    words_array-&gt;len++;
    words_array-&gt;words = realloc(words_array-&gt;words,
                                 words_array-&gt;len * sizeof(words_array-&gt;words[0]));
    if (words_array-&gt;words == NULL)
        exit(EXIT_FAILURE);
    strcpy(words_array-&gt;words[words_array-&gt;len-1], new_word);
}


void array_free(WordsArray *words_array) {
    assert(words_array != NULL);
    free(words_array-&gt;words);
    words_array-&gt;words = NULL;
    words_array-&gt;len = 0;
}


void list_print(WordsArray *words_array) {
    assert(words_array != NULL);
    size_t i;
    for (i = 0; i &lt; words_array-&gt;len; i++)
        printf(&quot;\n%s&quot;, words_array-&gt;words[i]);
}


int main() {
    FILE *fp = fopen(&quot;unixdict.txt&quot;, &quot;r&quot;);
    if (fp == NULL)
        return EXIT_FAILURE;

    WordsArray words;
    words.len = 0;
    words.words = NULL;

    TWord line;
    line[0] = '\0';
    unsigned int max_len = 0;

    while (fscanf(fp, &quot;%99s\n&quot;, line) != EOF) { // 99 = MAXLEN - 1
        if (strlen(line) &gt; max_len &amp;&amp; is_ordered_word(line)) {
            max_len = strlen(line);
            array_free(&amp;words);
            array_append(&amp;words, line);
        } else if (strlen(line) == max_len &amp;&amp; is_ordered_word(line)) {
            array_append(&amp;words, line);
        }
    }

    fclose(fp);
    list_print(&amp;words);
    array_free(&amp;words);

    return EXIT_SUCCESS;
}
