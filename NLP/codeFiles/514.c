#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stddef.h&gt;
#include &lt;stdbool.h&gt;

#define check_pointer(p) if (!p) {puts(&quot;Out of memory.&quot;); exit(EXIT_FAILURE);}

#define MINIMUM_SIZE 1
 /* Minimal stack size (expressed in number of elements) for which
 space is allocated. It should be at least 1. */
#define GROWTH_FACTOR 2
 /* How much more memory is allocated each time a stack grows
 out of its allocated segment. */
typedef int T;
 // The type of the stack elements.

typedef struct
 {T *bottom;
  T *top;
  T *allocated_top;} stack;

stack * new(void)
/* Creates a new stack. */
 {stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s-&gt;bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s-&gt;bottom);
  s-&gt;top = s-&gt;bottom - 1;
  s-&gt;allocated_top = s-&gt;bottom + MINIMUM_SIZE - 1;
  return s;}

void destroy(stack *s)
/* Frees all the memory used for a stack. */
 {free(s-&gt;bottom);
  free(s);}

bool empty(stack *s)
/* Returns true iff there are no elements on the stack. This
is different from the stack not having enough memory reserved
for even one element, which case is never allowed to arise. */
 {return s-&gt;top &lt; s-&gt;bottom ? true : false;}

void push(stack *s, T x)
/* Puts a new element on the stack, enlarging the latter's
memory allowance if necessary. */
 {if (s-&gt;top == s-&gt;allocated_top)
     {ptrdiff_t qtty = s-&gt;top - s-&gt;bottom + 1;
      ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
      s-&gt;bottom = realloc(s-&gt;bottom, new_qtty * sizeof(T));
      check_pointer(s-&gt;bottom);
      s-&gt;top = s-&gt;bottom + qtty - 1;
      s-&gt;allocated_top = s-&gt;bottom + new_qtty - 1;}
  *(++s-&gt;top) = x;}

T pop(stack *s)
/* Removes and returns the topmost element. The result of popping
an empty stack is undefined. */
 {return *(s-&gt;top--);}

void compress(stack *s)
/* Frees any memory the stack isn't actually using. The
allocated portion still isn't allowed to shrink smaller than
MINIMUM_SIZE. If all the stack's memory is in use, nothing
happens. */
 {if (s-&gt;top == s-&gt;allocated_top) return;
  ptrdiff_t qtty = s-&gt;top - s-&gt;bottom + 1;
  if (qtty &lt; MINIMUM_SIZE) qtty = MINIMUM_SIZE;
  size_t new_size = qtty * sizeof(T);
  s-&gt;bottom = realloc(s-&gt;bottom, new_size);
  check_pointer(s-&gt;bottom);
  s-&gt;allocated_top = s-&gt;bottom + qtty - 1;}
