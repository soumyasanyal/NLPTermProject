#define  DUMMY -1 /* dummy element of array (to adjust indexing from 1..n) */
int main(void) 
{
  Object a[] = {DUMMY, 0, 1, 1, 2, 5}; /* allowed indices from 1 to n including */
  int n = sizeof(a)/sizeof(*a) - 1;
  const int NotFound = -1;

  /* key not in Array */
  Object key = 4;
  assert(NotFound == bsearch(a, n, &amp;key, cmpObject, NotFound));
  key = DUMMY;
  assert(NotFound == bsearch(a, n, &amp;key, cmpObject, NotFound));
  key = 7;
  assert(NotFound == bsearch(a, n, &amp;key, cmpObject, NotFound));

  /* all possible `n' and `k' for `a' array */
  int k;
  key = 10; /* not in `a` array */
  for (n = 0; n &lt;= sizeof(a)/sizeof(*a) - 1; ++n)
    for (k = n; k&gt;=1; --k) {
      int index = bsearch(a, n, &amp;a[k], cmpObject, NotFound);
      assert(index == k || (k==3 &amp;&amp; index == 2) || n == 0); /* for equal `1's */
      assert(NotFound == bsearch(a, n, &amp;key, cmpObject, NotFound));
    }
  n = sizeof(a)/sizeof(*a) - 1;

  /* NULL array */
  assert(NotFound == bsearch(NULL, n, &amp;key, cmpObject, NotFound));
  /* NULL &amp;key */
  assert(NotFound == bsearch(a, n, NULL, cmpObject, NotFound));
  /* NULL cmpObject */
  assert(1 == bsearch(a, n, &amp;a[1], cmpObject, NotFound));
  assert(NotFound  == bsearch(a, n, &amp;a[1], NULL, NotFound));

  printf(&quot;OK\n&quot;);
  return 0;
}
