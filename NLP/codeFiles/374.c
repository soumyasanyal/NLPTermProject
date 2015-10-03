#include &lt;stdio.h&gt;
void pascaltriangle(unsigned int n)
{
  unsigned int c, i, j, k;

  for(i=0; i &lt; n; i++) {
    c = 1;
    for(j=1; j &lt;= 2*(n-1-i); j++) printf(&quot; &quot;);
    for(k=0; k &lt;= i; k++) {
      printf(&quot;%3d &quot;, c);
      c = c * (i-k)/(k+1);
    }
    printf(&quot;\n&quot;);
  }
}

int main()
{
  pascaltriangle(8);
  return 0;
}
