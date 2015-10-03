#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

int main(void)
{
  unsigned int bottles = 99;
  do
  {
    printf(&quot;%u bottles of beer on the wall\n&quot;, bottles);
    printf(&quot;%u bottles of beer\n&quot;, bottles);
    printf(&quot;Take one down, pass it around\n&quot;);
    printf(&quot;%u bottles of beer on the wall\n\n&quot;, --bottles);
  } while(bottles &gt; 0);
  return EXIT_SUCCESS;
}
