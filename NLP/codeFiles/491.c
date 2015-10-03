#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

void counting_sort_mm(int *array, int n, int min, int max)
{
  int i, j, z;

  int range = max - min + 1;
  int *count = malloc(range * sizeof(*array));

  for(i = 0; i &lt; range; i++) count[i] = 0;
  for(i = 0; i &lt; n; i++) count[ array[i] - min ]++;

  for(i = min, z = 0; i &lt;= max; i++) {
    for(j = 0; j &lt; count[i - min]; j++) {
      array[z++] = i;
    }
  } 

  free(count);
}

void counting_sort(int *array, int n)
{
  int i, min, max;
  
  min = max = array[0];
  for(i=1; i &lt; n; i++) {
    if ( array[i] &lt; min ) {
      min = array[i];
    } else if ( array[i] &gt; max ) {
      max = array[i];
    }
  }
}
