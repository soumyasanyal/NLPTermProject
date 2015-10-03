#include &lt;stdio.h&gt;
int main()
{
  int square = 1, increment = 3, door;
  for (door = 1; door &lt;= 100; ++door)
  {
    printf(&quot;door #%d&quot;, door);
    if (door == square)
    {
      printf(&quot; is open.\n&quot;);
      square += increment;
      increment += 2;
    }
    else
      printf(&quot; is closed.\n&quot;);
  }
  return 0;
}
