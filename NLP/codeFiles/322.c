/* this is global */int integers[NMEMB]; /* should be initialized with 0s */

int funcB()
{
  static int ints[NMEMB]; /* this is &quot;static&quot;, i.e. the memory &quot;survive&quot; even
                             when the function exits, but the symbol's scope is local */ 
  return integers[0] + ints[0];
}

void funcC(int a)
{
  integers[0] = a;
}
