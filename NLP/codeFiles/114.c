#include &lt;unistd.h&gt;
int main() {
  unlink(&quot;input.txt&quot;);
  unlink(&quot;/input.txt&quot;);
  rmdir(&quot;docs&quot;);
  rmdir(&quot;/docs&quot;);
  return 0;
}
