#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

typedef struct node_s
{
  int value;
  struct node_s* left;
  struct node_s* right;
} *node;

node tree(int v, node l, node r)
{
  node n = malloc(sizeof(struct node_s));
  n-&gt;value = v;
  n-&gt;left  = l;
  n-&gt;right = r;
  return n;
}

void destroy_tree(node n)
{
  if (n-&gt;left)
    destroy_tree(n-&gt;left);
  if (n-&gt;right)
    destroy_tree(n-&gt;right);
  free(n);
}

void preorder(node n, void (*f)(int))
{
  f(n-&gt;value);
  if (n-&gt;left)
    preorder(n-&gt;left, f);
  if (n-&gt;right)
    preorder(n-&gt;right, f);
}

void inorder(node n, void (*f)(int))
{
  if (n-&gt;left)
    inorder(n-&gt;left, f);
  f(n-&gt;value);
  if (n-&gt;right)
    inorder(n-&gt;right, f);
}

void postorder(node n, void (*f)(int))
{
  if (n-&gt;left)
    postorder(n-&gt;left, f);
  if (n-&gt;right)
    postorder(n-&gt;right, f);
  f(n-&gt;value);
}

/* helper queue for levelorder */
typedef struct qnode_s
{
  struct qnode_s* next;
  node value;
} *qnode;

typedef struct { qnode begin, end; } queue;

void enqueue(queue* q, node n)
{
  qnode node = malloc(sizeof(struct qnode_s));
  node-&gt;value = n;
  node-&gt;next = 0;
  if (q-&gt;end)
    q-&gt;end-&gt;next = node;
  else
    q-&gt;begin = node;
  q-&gt;end = node;
}

node dequeue(queue* q)
{
  node tmp = q-&gt;begin-&gt;value;
  qnode second = q-&gt;begin-&gt;next;
  free(q-&gt;begin);
  q-&gt;begin = second;
  if (!q-&gt;begin)
    q-&gt;end = 0;
  return tmp;
}

int queue_empty(queue* q)
{
  return !q-&gt;begin;
}

void levelorder(node n, void(*f)(int))
{
  queue nodequeue = {};
  enqueue(&amp;nodequeue, n);
  while (!queue_empty(&amp;nodequeue))
  {
    node next = dequeue(&amp;nodequeue);
    f(next-&gt;value);
    if (next-&gt;left)
      enqueue(&amp;nodequeue, next-&gt;left);
    if (next-&gt;right)
      enqueue(&amp;nodequeue, next-&gt;right);
  }
}

void print(int n)
{
  printf(&quot;%d &quot;, n);
}

int main()
{
  node n = tree(1,
                tree(2,
                     tree(4,
                          tree(7, 0, 0),
                          0),
                     tree(5, 0, 0)),
                tree(3,
                     tree(6,
                          tree(8, 0, 0),
                          tree(9, 0, 0)),
                     0));

  printf(&quot;preorder:    &quot;);
  preorder(n, print);
  printf(&quot;\n&quot;);

  printf(&quot;inorder:     &quot;);
  inorder(n, print);
  printf(&quot;\n&quot;);

  printf(&quot;postorder:   &quot;);
  postorder(n, print);
  printf(&quot;\n&quot;);

  printf(&quot;level-order: &quot;);
  levelorder(n, print);
  printf(&quot;\n&quot;);

  destroy_tree(n);

  return 0;
}
