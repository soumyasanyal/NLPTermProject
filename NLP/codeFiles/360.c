#include &lt;stdlib.h&gt;#include &lt;string.h&gt;
#include &lt;stdio.h&gt;
#include &lt;assert.h&gt;


#define MAXLEN 100
typedef char TWord[MAXLEN];


typedef struct Node {
    TWord word;
    struct Node *next;
} Node;


int is_ordered_word(const TWord word) {
    assert(word != NULL);
    int i;

    for (i = 0; word[i] != '\0'; i++)
        if (word[i] &gt; word[i + 1] &amp;&amp; word[i + 1] != '\0')
            return 0;

    return 1;
}


Node* list_prepend(Node* words_list, const TWord new_word) {
    assert(new_word != NULL);
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
        exit(EXIT_FAILURE);

    strcpy(new_node-&gt;word, new_word);
    new_node-&gt;next = words_list;
    return new_node;
}


Node* list_destroy(Node *words_list) {
    while (words_list != NULL) {
        Node *temp = words_list;
        words_list = words_list-&gt;next;
        free(temp);
    }

    return words_list;
}


void list_print(Node *words_list) {
    while (words_list != NULL) {
        printf(&quot;\n%s&quot;, words_list-&gt;word);
        words_list = words_list-&gt;next;
    }
}


int main() {
    FILE *fp = fopen(&quot;unixdict.txt&quot;, &quot;r&quot;);
    if (fp == NULL)
        return EXIT_FAILURE;

    Node *words = NULL;
    TWord line;
    unsigned int max_len = 0;

    while (fscanf(fp, &quot;%99s\n&quot;, line) != EOF) {
        if (strlen(line) &gt; max_len &amp;&amp; is_ordered_word(line)) {
            max_len = strlen(line);
            words = list_destroy(words);
            words = list_prepend(words, line);
        } else if (strlen(line) == max_len &amp;&amp; is_ordered_word(line)) {
            words = list_prepend(words, line);
        }
    }

    fclose(fp);
    list_print(words);

    return EXIT_SUCCESS;
}
