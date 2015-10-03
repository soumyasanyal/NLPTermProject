#include &lt;stdio.h&gt;
void recurse(unsigned int i)
{
  printf(&quot;%d\n&quot;, i);
  recurse(i+1); // 523756
}

int main()
{
  recurse(0);
  return 0;
}
