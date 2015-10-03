#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

#define ValType double
#define IS_LESS(v1, v2)  (v1 &lt; v2)

void siftDown( ValType *a, int start, int count);

#define SWAP(r,s)  do{ValType t=r; r=s; s=t; } while(0)

void heapsort( ValType *a, int count)
{
    int start, end;

    /* heapify */
    for (start = (count-2)/2; start &gt;=0; start--) {
        siftDown( a, start, count);
    }

    for (end=count-1; end &gt; 0; end--) {
        SWAP(a[end],a[0]);
        siftDown(a, 0, end);
    }
}

void siftDown( ValType *a, int start, int end)
{
    int root = start;

    while ( root*2+1 &lt; end ) {
        int child = 2*root + 1;
        if ((child + 1 &lt; end) &amp;&amp; IS_LESS(a[child],a[child+1])) {
            child += 1;
        }
        if (IS_LESS(a[root], a[child])) {
            SWAP( a[child], a[root] );
            root = child;
        }
        else
            return;
    }
}


int main()
{
    int ix;
    double valsToSort[] = {
        1.4, 50.2, 5.11, -1.55, 301.521, 0.3301, 40.17,
        -18.0, 88.1, 30.44, -37.2, 3012.0, 49.2};
#define VSIZE (sizeof(valsToSort)/sizeof(valsToSort[0]))

    heapsort(valsToSort, VSIZE);
    printf(&quot;{&quot;);
    for (ix=0; ix&lt;VSIZE; ix++) printf(&quot; %.3f &quot;, valsToSort[ix]);
    printf(&quot;}\n&quot;);
    return 0;
}
