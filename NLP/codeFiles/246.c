#include &lt;stdlib.h&gt;
#include &lt;stdio.h&gt;
int main(int argc, char** argv) {
   if (argc &lt; 2) {
      printf(&quot;usage: identitymatrix &lt;number of rows&gt;\n&quot;);
      exit(EXIT_FAILURE);
   }
   signed int rowsize = atoi(argv[1]);
   if (rowsize &lt; 0) {
      printf(&quot;Dimensions of matrix cannot be negative\n&quot;);
      exit(EXIT_FAILURE);
   }
   volatile int numElements = rowsize * rowsize;
   if (numElements &lt; rowsize) {
      printf(&quot;Squaring %d caused result to overflow to %d.\n&quot;, rowsize, numElements);
      abort();
   }
   int** matrix = calloc(numElements, sizeof(int*));
   if (!matrix) {
      printf(&quot;Failed to allocate %d elements of %d bytes each\n&quot;, numElements, sizeof(int*));
      abort();
   }
   for (unsigned int row = 0;row &lt; rowsize;row++) {
      matrix[row] = calloc(numElements, sizeof(int));
      if (!matrix[row]) {
         printf(&quot;Failed to allocate %d elements of %d bytes each\n&quot;, numElements, sizeof(int));
         abort();
      }
      matrix[row][row] = 1;
   }
   printf(&quot;Matrix is: \n&quot;);
   for (unsigned int row = 0;row &lt; rowsize;row++) {
      for (unsigned int column = 0;column &lt; rowsize;column++) {
         printf(&quot;%d &quot;, matrix[row][column]);
      }
      printf(&quot;\n&quot;);
   }
}

