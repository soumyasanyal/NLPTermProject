#include &lt;math.h&gt;#include &lt;stdio.h&gt;
#include &lt;limits.h&gt;
#pragma precision=log10l(ULLONG_MAX)/2

typedef enum { FALSE=0, TRUE=1 } BOOL;

BOOL is_prime( int p ){
  if( p == 2 ) return TRUE;
  else if( p &lt;= 1 || p % 2 == 0 ) return FALSE;
  else {
    BOOL prime = TRUE;
    const int to = sqrt(p);
    int i;
    for(i = 3; i &lt;= to; i+=2)  
      if (!(prime = p % i))break;
    return prime;
  }
}

BOOL is_mersenne_prime( int p ){
  if( p == 2 ) return TRUE;
  else {
    const long long unsigned m_p = ( 1LLU &lt;&lt; p ) - 1;
    long long unsigned s = 4;
    int i;
    for (i = 3; i &lt;= p; i++){
      s = (s * s - 2) % m_p;
    }
    return s == 0;
  }
}

int main(int argc, char **argv){

  const int upb = log2l(ULLONG_MAX)/2; 
  int p;
  printf(&quot; Mersenne primes:\n&quot;);
  for( p = 2; p &lt;= upb; p += 1 ){
    if( is_prime(p) &amp;&amp; is_mersenne_prime(p) ){
      printf (&quot; M%u&quot;,p);
    }
  }
  printf(&quot;\n&quot;);
}
