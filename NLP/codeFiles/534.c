#include &lt;string.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;

int main( int argc, char ** argv ){
  const char * str_a = &quot;knight&quot;;
  const char * str_b = &quot;socks&quot;;
  const char * str_c = &quot;brooms&quot;;

  char * new_a = malloc( strlen( str_a ) - 1 );
  char * new_b = malloc( strlen( str_b ) - 1 );
  char * new_c = malloc( strlen( str_c ) - 2 );

  strcpy( new_a, str_a + 1 );
  strncpy( new_b, str_b, strlen( str_b ) - 1 );
  strncpy( new_c, str_c + 1, strlen( str_c ) - 2 );

  printf( &quot;%s\n%s\n%s\n&quot;, new_a, new_b, new_c );

  free( new_a );
  free( new_b );
  free( new_c );

  return 0;
}
