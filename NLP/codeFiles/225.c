#include &lt;stdio.h&gt;
int main()
{
   FILE *lp;
   lp = fopen(&quot;/dev/lp0&quot;,&quot;w&quot;);
   fprintf(lp,&quot;Hello world!\n&quot;);
   fclose(lp);
   return 0;
}
