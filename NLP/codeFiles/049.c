#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;assert.h&gt;
#include &lt;limits.h&gt;

#define DEBUG

void best_shuffle(const char* txt, char* result) {
    const size_t len = strlen(txt);
    if (len == 0)
        return;

#ifdef DEBUG
    // txt and result must have the same length
    assert(len == strlen(result));
#endif

    // how many of each character?
    size_t counts[UCHAR_MAX];
    memset(counts, '\0', UCHAR_MAX * sizeof(int));
    size_t fmax = 0;
    for (size_t i = 0; i &lt; len; i++) {
        counts[(unsigned char)txt[i]]++;
        const size_t fnew = counts[(unsigned char)txt[i]];
        if (fmax &lt; fnew)
             fmax = fnew;
    }
    assert(fmax &gt; 0 &amp;&amp; fmax &lt;= len);

    // all character positions, grouped by character
    size_t *ndx1 = malloc(len * sizeof(size_t));
    if (ndx1 == NULL)
        exit(EXIT_FAILURE);
    for (size_t ch = 0, i = 0; ch &lt; UCHAR_MAX; ch++)
       if (counts[ch])
            for (size_t j = 0; j &lt; len; j++)
                if (ch == (unsigned char)txt[j]) {
                    ndx1[i] = j;
                    i++;
                }

    // regroup them for cycles
    size_t *ndx2 = malloc(len * sizeof(size_t));
    if (ndx2 == NULL)
        exit(EXIT_FAILURE);
    for (size_t i = 0, n = 0, m = 0; i &lt; len; i++) {
        ndx2[i] = ndx1[n];
        n += fmax;
        if (n &gt;= len) {
            m++;
            n = m;
        }
    }

    // how long can our cyclic groups be?
    const size_t grp = 1 + (len - 1) / fmax;
    assert(grp &gt; 0 &amp;&amp; grp &lt;= len);

    // how many of them are full length?
    const size_t lng = 1 + (len - 1) % fmax;
    assert(lng &gt; 0 &amp;&amp; lng &lt;= len);

    // rotate each group
    for (size_t i = 0, j = 0; i &lt; fmax; i++) {
        const size_t first = ndx2[j];
        const size_t glen = grp - (i &lt; lng ? 0 : 1);
        for (size_t k = 1; k &lt; glen; k++)
            ndx1[j + k - 1] = ndx2[j + k];
        ndx1[j + glen - 1] = first;
        j += glen;
    }

    // result is original permuted according to our cyclic groups
    result[len] = '\0';
    for (size_t i = 0; i &lt; len; i++)
        result[ndx2[i]] = txt[ndx1[i]];

    free(ndx1);
    free(ndx2);
}

void display(const char* txt1, const char* txt2) {
    const size_t len = strlen(txt1);
    assert(len == strlen(txt2));
    int score = 0;
    for (size_t i = 0; i &lt; len; i++)
        if (txt1[i] == txt2[i])
            score++;
    (void)printf(&quot;%s, %s, (%u)\n&quot;, txt1, txt2, score);
}

int main() {
    const char* data[] = {&quot;abracadabra&quot;, &quot;seesaw&quot;, &quot;elk&quot;, &quot;grrrrrr&quot;,
                          &quot;up&quot;, &quot;a&quot;, &quot;aabbbbaa&quot;, &quot;&quot;, &quot;xxxxx&quot;};
    const size_t data_len = sizeof(data) / sizeof(data[0]);
    for (size_t i = 0; i &lt; data_len; i++) {
        const size_t shuf_len = strlen(data[i]) + 1;
        char shuf[shuf_len];

#ifdef DEBUG
        memset(shuf, 0xFF, sizeof shuf);
        shuf[shuf_len - 1] = '\0';
#endif

        best_shuffle(data[i], shuf);
        display(data[i], shuf);
    }

    return EXIT_SUCCESS;
}
