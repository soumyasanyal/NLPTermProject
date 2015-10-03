#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdbool.h&gt;

#include &lt;sys/queue.h&gt;

struct entry {
  int value;
  TAILQ_ENTRY(entry) entries;
};

typedef struct entry entry_t;

TAILQ_HEAD(FIFOList_s, entry);

typedef struct FIFOList_s FIFOList;


bool m_enqueue(int v, FIFOList *l)
{
  entry_t *val;
  val = malloc(sizeof(entry_t));
  if ( val != NULL ) {
    val-&gt;value = v;
    TAILQ_INSERT_TAIL(l, val, entries);
    return true;
  }
  return false;
}

bool m_dequeue(int *v, FIFOList *l)
{
  entry_t *e = l-&gt;tqh_first;
  if ( e != NULL ) {
    *v = e-&gt;value;
    TAILQ_REMOVE(l, e, entries);
    free(e);
    return true;
  }
  return false;
}

bool isQueueEmpty(FIFOList *l)
{
  if ( l-&gt;tqh_first == NULL ) return true;
  return false;
}
