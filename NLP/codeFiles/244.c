#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define BYTES 256

struct huffcode {
  int nbits;
  int code;
};
typedef struct huffcode huffcode_t;

struct huffheap {
  int *h;
  int n, s, cs;
  long *f;
};
typedef struct huffheap heap_t;

/* heap handling funcs */
static heap_t *_heap_create(int s, long *f)
{
  heap_t *h;
  h = malloc(sizeof(heap_t));
  h-&gt;h = malloc(sizeof(int)*s);
  h-&gt;s = h-&gt;cs = s;
  h-&gt;n = 0;
  h-&gt;f = f;
  return h;
}

static void _heap_destroy(heap_t *heap)
{
  free(heap-&gt;h);
  free(heap);
}

#define swap_(I,J) do { int t_; t_ = a[(I)];	\
      a[(I)] = a[(J)]; a[(J)] = t_; } while(0)
static void _heap_sort(heap_t *heap)
{
  int i=1, j=2; /* gnome sort */
  int *a = heap-&gt;h;

  while(i &lt; heap-&gt;n) { /* smaller values are kept at the end */
    if ( heap-&gt;f[a[i-1]] &gt;= heap-&gt;f[a[i]] ) {
      i = j; j++;
    } else {
      swap_(i-1, i);
      i--;
      i = (i==0) ? j++ : i;
    }
  }
}
#undef swap_

static void _heap_add(heap_t *heap, int c)
{
  if ( (heap-&gt;n + 1) &gt; heap-&gt;s ) {
    heap-&gt;h = realloc(heap-&gt;h, heap-&gt;s + heap-&gt;cs);
    heap-&gt;s += heap-&gt;cs;
  }
  heap-&gt;h[heap-&gt;n] = c;
  heap-&gt;n++;
  _heap_sort(heap);
}

static int _heap_remove(heap_t *heap)
{
  if ( heap-&gt;n &gt; 0 ) {
    heap-&gt;n--;
    return heap-&gt;h[heap-&gt;n];
  }
  return -1;
}

/* huffmann code generator */
huffcode_t **create_huffman_codes(long *freqs)
{
  huffcode_t **codes;
  heap_t *heap;
  long efreqs[BYTES*2];
  int preds[BYTES*2];
  int i, extf=BYTES;
  int r1, r2;

  memcpy(efreqs, freqs, sizeof(long)*BYTES);
  memset(&amp;efreqs[BYTES], 0, sizeof(long)*BYTES);

  heap = _heap_create(BYTES*2, efreqs);
  if ( heap == NULL ) return NULL;

  for(i=0; i &lt; BYTES; i++) if ( efreqs[i] &gt; 0 ) _heap_add(heap, i);

  while( heap-&gt;n &gt; 1 )
  {
    r1 = _heap_remove(heap);
    r2 = _heap_remove(heap);
    efreqs[extf] = efreqs[r1] + efreqs[r2];
    _heap_add(heap, extf);
    preds[r1] = extf;
    preds[r2] = -extf;
    extf++;
  }
  r1 = _heap_remove(heap);
  preds[r1] = r1;
  _heap_destroy(heap);

  codes = malloc(sizeof(huffcode_t *)*BYTES);

  int bc, bn, ix;
  for(i=0; i &lt; BYTES; i++) {
    bc=0; bn=0;
    if ( efreqs[i] == 0 ) { codes[i] = NULL; continue; }
    ix = i;
    while( abs(preds[ix]) != ix ) {
      bc |= ((preds[ix] &gt;= 0) ? 1 : 0 ) &lt;&lt; bn;
      ix = abs(preds[ix]);
      bn++;
    }
    codes[i] = malloc(sizeof(huffcode_t));
    codes[i]-&gt;nbits = bn;
    codes[i]-&gt;code = bc;
  }
  return codes;
}

void free_huffman_codes(huffcode_t **c)
{
  int i;

  for(i=0; i &lt; BYTES; i++) free(c[i]);
  free(c);
}

#define MAXBITSPERCODE 100

void inttobits(int c, int n, char *s)
{
  s[n] = 0;
  while(n &gt; 0) {
    s[n-1] = (c%2) + '0';
    c &gt;&gt;= 1; n--;
  }
}

const char *test = &quot;this is an example for huffman encoding&quot;;

int main()
{
  huffcode_t **r;
  int i;
  char strbit[MAXBITSPERCODE];
  const char *p;
  long freqs[BYTES];

  memset(freqs, 0, sizeof freqs);

  p = test;
  while(*p != '\0') freqs[*p++]++;

  r = create_huffman_codes(freqs);

  for(i=0; i &lt; BYTES; i++) {
    if ( r[i] != NULL ) {
      inttobits(r[i]-&gt;code, r[i]-&gt;nbits, strbit);
      printf(&quot;%c (%d) %s\n&quot;, i, r[i]-&gt;code, strbit);
    }
  }

  free_huffman_codes(r);

  return 0;
}
