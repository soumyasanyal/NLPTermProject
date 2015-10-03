#include &lt;stdio.h&gt;
int main()
{
  int door, square, increment;
  for (door = 1, square = 1, increment = 1; door &lt;= 100; door++ == square &amp;&amp; (square += increment += 2))
    printf(&quot;door #%d is %s.\n&quot;, door, (door == square? &quot;open&quot; : &quot;closed&quot;));
  return 0;
}
