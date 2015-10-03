#include &lt;stdio.h&gt;
int main() {
  printf(&quot;%d\n&quot;, 'a'); /* prints &quot;97&quot; */
  printf(&quot;%c\n&quot;, 97); /* prints &quot;a&quot;; we don't have to cast because printf is type agnostic */
  return 0;
}
