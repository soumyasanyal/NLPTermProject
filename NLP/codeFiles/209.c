#include &lt;assert.h&gt;
float max(unsigned int count, float values[]) {
     assert(count &gt; 0);
     unsigned int idx;
     float themax = values[0];
     for(i = 1; i &lt; count; ++i) {
          themax = values[i] &gt; themax ? values[i] : themax;
     }
     return themax;
}
