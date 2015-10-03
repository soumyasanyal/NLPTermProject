#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

struct list_node {int x; struct list_node *next;};
typedef struct list_node node;

node * uniq(int *a, unsigned alen)
 {if (alen == 0) return NULL;
  node *start = malloc(sizeof(node));
  if (start == NULL) exit(EXIT_FAILURE);
  start-&gt;x = a[0];
  start-&gt;next = NULL;

  for (int i = 1 ; i &lt; alen ; ++i)
     {node *n = start;
      for (;; n = n-&gt;next)
         {if (a[i] == n-&gt;x) break;
          if (n-&gt;next == NULL)
             {n-&gt;next = malloc(sizeof(node));
              n = n-&gt;next;
              if (n == NULL) exit(EXIT_FAILURE);
              n-&gt;x = a[i];
              n-&gt;next = NULL;
              break;}}}

  return start;}

int main(void)
   {int a[] = {1, 2, 1, 4, 5, 2, 15, 1, 3, 4};
    for (node *n = uniq(a, 10) ; n != NULL ; n = n-&gt;next)
        printf(&quot;%d &quot;, n-&gt;x);
    puts(&quot;&quot;);
    return 0;}
