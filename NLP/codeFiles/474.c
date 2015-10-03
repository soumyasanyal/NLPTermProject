#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;

char* eratosthenes (int n, int *c)
{
  char* sieve;
  int i, j, m;

  *c = n-1;     /* primes count */

  /* calloc initializes to zero */
  sieve = calloc (n+1, sizeof(char));
  m = (int) sqrt ((double) n);
  sieve[0] = 1;
  sieve[1] = 1;
  for (i = 2; i &lt;= m; i++) {
    if (sieve[i] == 0) {
      for (j = i*i; j &lt;= n; j += i) {
        if (sieve[j] == 0) {
          sieve[j] = 1; 
          --(*c);
        }
      }
    }
  }
  return sieve;
}

