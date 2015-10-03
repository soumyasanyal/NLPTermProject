#include &lt;math.h&gt;	/* HUGE_VAL */#include &lt;stdio.h&gt;	/* printf() */

double inf(void) {
  return HUGE_VAL;
}

int main() {
  printf(&quot;%g\n&quot;, inf());
  return 0;
}
