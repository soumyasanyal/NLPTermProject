#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

/*
 * Writes the Roman numeral representing n into the buffer s.
 * Handles up to n = 3999.
 * Since C doesn't have exceptions, n = 0 causes the whole program to exit
 * unsuccessfully.
 * s should be have room for at least 16 characters, including the trailing
 * null.
 */
void roman(char *s, unsigned int n)
{
 if (n == 0)
 {
  fputs(stderr, &quot;Roman numeral for zero requested.&quot;);
  exit(EXIT_FAILURE);
 }

  #define digit(loop, num, c) \
      loop (n &gt;= num)         \
         {*(s++) = c;         \
          n -= num;}  
  #define digits(loop, num, c1, c2) \
      loop (n &gt;= num)               \
         {*(s++) = c1;              \
          *(s++) = c2;              \
          n -= num;}

  digit  ( while, 1000, 'M'      )
  digits ( if,     900, 'C', 'M' )
  digit  ( if,     500, 'D'      )
  digits ( if,     400, 'C', 'D' )
  digit  ( while,  100, 'C'      )
  digits ( if,      90, 'X', 'C' )
  digit  ( if,      50, 'L'      )
  digits ( if,      40, 'X', 'L' )
  digit  ( while,   10, 'X'      )
  digits ( if,       9, 'I', 'X' )
  digit  ( if,       5, 'V'      )
  digits ( if,       4, 'I', 'V' )
  digit  ( while,    1, 'I'      )

  #undef digit
  #undef digits
  
  *s = 0;}

int main(void)
{
 char buffer[16];
 unsigned int i;
 for (i = 1 ; i &lt; 4000 ; ++i)
 {
  roman(buffer, i);
  printf(&quot;%4u: %s\n&quot;, i, buffer);
 }
 return EXIT_SUCCESS;
}
