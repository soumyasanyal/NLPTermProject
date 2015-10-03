#include &lt;stdio.h&gt;
void move(int n, int from, int to, int via)
{
  if (n &gt; 0) {
    move(n - 1, from, via, to);
    printf(&quot;Move disk from pole %d to pole %d\n&quot;, from, to);
    move(n - 1, via, to, from);
  }
}
int main()
{
  move(4, 1,2,3);
  return 0;
}
