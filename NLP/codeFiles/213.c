#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;time.h&gt;

#define lower_limit 0
#define upper_limit 100

int main(){
  int number, guess;

  srand( time( 0 ) );
  number = lower_limit + rand() % (upper_limit - lower_limit + 1);

  printf( &quot;Guess the number between %d and %d: &quot;, lower_limit, upper_limit );

  while( scanf( &quot;%d&quot;, &amp;guess ) == 1 ){
    if( number == guess ){
      printf( &quot;You guessed correctly!\n&quot; );
      break;
    }
    printf( &quot;Your guess was too %s.\nTry again: &quot;, number &lt; guess ? &quot;high&quot; : &quot;low&quot; );
  }

  return 0;
}
