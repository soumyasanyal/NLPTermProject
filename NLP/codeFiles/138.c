#include &lt;stdio.h&gt;#include &lt;stdbool.h&gt;

void halve(int *x) { *x &gt;&gt;= 1; }
void doublit(int *x)  { *x &lt;&lt;= 1; }
bool iseven(const int x) { return (x &amp; 1) ==  0; }

int ethiopian(int plier,
	      int plicand, const bool tutor)
{
  int result=0;

  if (tutor)
    printf(&quot;ethiopian multiplication of %d by %d\n&quot;, plier, plicand);
  
  while(plier &gt;= 1) {
    if ( iseven(plier) ) {
      if (tutor) printf(&quot;%4d %6d struck\n&quot;, plier, plicand);
    } else {
      if (tutor) printf(&quot;%4d %6d kept\n&quot;, plier, plicand);
      result += plicand;
    }
    halve(&amp;plier); doublit(&amp;plicand);
  }
  return result;
}

int main()
{
  printf(&quot;%d\n&quot;, ethiopian(17, 34, true));
  return 0;
}
