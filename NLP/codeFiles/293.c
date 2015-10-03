#include &lt;stdio.h&gt;...

const char *list[] = {&quot;Red&quot;,&quot;Green&quot;,&quot;Blue&quot;,&quot;Black&quot;,&quot;White&quot;};
#define LIST_SIZE (sizeof(list)/sizeof(list[0]))

int ix;
for(ix=0; ix&lt;LIST_SIZE; ix++) {
   printf(&quot;%s\n&quot;, list[ix]);
}
