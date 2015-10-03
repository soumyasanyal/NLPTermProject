#include &lt;alloca.h&gt;int *funcA()
{
  int *ints = alloca(SIZEOF_MEMB*NMEMB);
  ints[0] = 0;                                  /* use it */
  return ints; /* BUT THIS IS WRONG! It is not like malloc: the memory
                  does not &quot;survive&quot;! */
}
