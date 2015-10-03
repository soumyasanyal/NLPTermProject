#include &lt;stdio.h&gt;
int main()
{
  char is_open[100] = { 0 };
  int pass, door;

  // do the 100 passes
  for (pass = 0; pass &lt; 100; ++pass)
    for (door = pass; door &lt; 100; door += pass+1)
      is_open[door] = !is_open[door];

  // output the result
  for (door = 0; door &lt; 100; ++door)
    printf(&quot;door #%d is %s.\n&quot;, door+1, (is_open[door]? &quot;open&quot; : &quot;closed&quot;));

  return 0;
}
