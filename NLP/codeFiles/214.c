#include &lt;stdio.h&gt;
int main(){
  int bounds[ 2 ] = {1, 100};
  char input[ 2 ] = &quot;  &quot;;
    /* second char is for the newline from hitting [return] */
  int choice = (bounds[ 0 ] + bounds[ 1 ]) / 2;
    /* using a binary search */

  printf( &quot;Choose a number between %d and %d.\n&quot;, bounds[ 0 ], bounds[ 1 ] );

  do{
    switch( input[ 0 ] ){
      case 'H':
        bounds[ 1 ] = choice;
        break;
      case 'L':
        bounds[ 0 ] = choice;
        break;
      case 'Y':
        printf( &quot;\nAwwwright\n&quot; );
        return 0;
    }
    choice = (bounds[ 0 ] + bounds[ 1 ]) / 2;

    printf( &quot;Is the number %d? (Y/H/L) &quot;, choice );
  }while( scanf( &quot;%1s&quot;, input ) == 1 );

  return 0;
}
