#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;time.h&gt;

struct s_env {
    unsigned int n, i;
    size_t size;
    void *sample;
};

void s_of_n_init(struct s_env *s_env, size_t size, unsigned int n)
{
    s_env-&gt;i = 0;
    s_env-&gt;n = n;
    s_env-&gt;size = size;
    s_env-&gt;sample = malloc(n * size);
}

void sample_set_i(struct s_env *s_env, unsigned int i, void *item)
{
    memcpy(s_env-&gt;sample + i * s_env-&gt;size, item, s_env-&gt;size);
}

void *s_of_n(struct s_env *s_env, void *item)
{
    s_env-&gt;i++;
    if (s_env-&gt;i &lt;= s_env-&gt;n)
        sample_set_i(s_env, s_env-&gt;i - 1, item);
    else if ((rand() % s_env-&gt;i) &lt; s_env-&gt;n)
        sample_set_i(s_env, rand() % s_env-&gt;n, item);
    return s_env-&gt;sample;
}

int *test(unsigned int n, int *items_set, unsigned int num_items)
{
    int i;
    struct s_env s_env;
    s_of_n_init(&amp;s_env, sizeof(items_set[0]), n);
    for (i = 0; i &lt; num_items; i++) {
        s_of_n(&amp;s_env, (void *) &amp;items_set[i]);
    }
    return (int *)s_env.sample;
}

int main()
{
    unsigned int i, j;
    unsigned int n = 3;
    unsigned int num_items = 10;
    unsigned int *frequencies;
    int *items_set;
    srand(time(NULL));
    items_set = malloc(num_items * sizeof(int));
    frequencies = malloc(num_items * sizeof(int));
    for (i = 0; i &lt; num_items; i++) {
        items_set[i] = i;
        frequencies[i] = 0;
    }
    for (i = 0; i &lt; 100000; i++) {
        int *res = test(n, items_set, num_items);
        for (j = 0; j &lt; n; j++) {
            frequencies[res[j]]++;
        }
	free(res);
    }
    for (i = 0; i &lt; num_items; i++) {
        printf(&quot; %d&quot;, frequencies[i]);
    }
    puts(&quot;&quot;);
    return 0;
}
