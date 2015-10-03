#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;

int main(){
  char array[] = { 'a', 'b', 'c' };

  srand( time( 0 ) );

  printf( &quot;%c\n&quot;, array[ rand() % 3 ] );

  return 0;
}
