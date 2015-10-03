#include &lt;stdio.h&gt;#include &lt;math.h&gt;

int main(int argc, char **argv) {

   float x[4] = {1,2,3,1e11}, y[4];
   int i = 0;
   FILE *filePtr;

   filePtr = fopen(&quot;floatArray&quot;,&quot;w&quot;);

   for (i = 0; i &lt; 4; i++) {
      y[i] = sqrt(x[i]);
      fprintf(filePtr, &quot;%.3g\t%.5g\n&quot;, x[i], y[i]);
   }

   return 0;
}
