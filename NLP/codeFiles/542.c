#include&lt;time.h&gt;#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
int main(){
  time_t my_time = time(NULL);
  printf(&quot;%s&quot;, ctime(&amp;my_time));
  return 0;
}
