#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdint.h&gt;

typedef struct {
        char * name;
        int weight, value;
} item_t;

item_t item[] = {
        {&quot;map&quot;,                     9,       150},
        {&quot;compass&quot;,                 13,      35},
        {&quot;water&quot;,                   153,     200},
        {&quot;sandwich&quot;,                50,      160},
        {&quot;glucose&quot;,                 15,      60},
        {&quot;tin&quot;,                     68,      45},
        {&quot;banana&quot;,                  27,      60},
        {&quot;apple&quot;,                   39,      40},
        {&quot;cheese&quot;,                  23,      30},
        {&quot;beer&quot;,                    52,      10},
        {&quot;suntancream&quot;,             11,      70},
        {&quot;camera&quot;,                  32,      30},
        {&quot;T-shirt&quot;,                 24,      15},
        {&quot;trousers&quot;,                48,      10},
        {&quot;umbrella&quot;,                73,      40},
        {&quot;waterproof trousers&quot;,     42,      70},
        {&quot;waterproof overclothes&quot;,  43,      75},
        {&quot;note-case&quot;,               22,      80},
        {&quot;sunglasses&quot;,              7,       20},
        {&quot;towel&quot;,                   18,      12},
        {&quot;socks&quot;,                   4,       50},
        {&quot;book&quot;,                    30,      10}
};

#define n_items (sizeof(item)/sizeof(item_t))

typedef struct {
        uint32_t bits; /* 32 bits, can solve up to 32 items */
        int value;
} solution;


void optimal(int weight, int idx, solution *s)
{
        solution v1, v2;
        if (idx &lt; 0) {
                s-&gt;bits = s-&gt;value = 0;
                return;
        }

        if (weight &lt; item[idx].weight)
                return optimal(weight, idx - 1, s);

        optimal(weight, idx - 1, &amp;v1);
        optimal(weight - item[idx].weight, idx - 1, &amp;v2);

        v2.value += item[idx].value;
        v2.bits |= (1 &lt;&lt; idx);

        *s = (v1.value &gt;= v2.value) ? v1 : v2;
}

int main()
{
        int i = 0, w = 0;
        solution s = {0, 0};
        optimal(400, n_items - 1, &amp;s);

        for (i = 0; i &lt; n_items; i++) {
                if (s.bits &amp; (1 &lt;&lt; i)) {
                        printf(&quot;%s\n&quot;, item[i].name);
                        w += item[i].weight;
                }
        }
        printf(&quot;Total value: %d; weight: %d\n&quot;, s.value, w);
        return 0;
}
