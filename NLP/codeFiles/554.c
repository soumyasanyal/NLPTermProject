#include &lt;stdio.h&gt;#include &lt;time.h&gt;

int identity(int x) { return x; }

int sum(int s)
{
  int i;
  for(i=0; i &lt; 1000000; i++) s += i;
  return s;
}

#define CLOCKTYPE CLOCK_MONOTONIC
/* this one should be appropriate to avoid errors on multiprocessors systems */

double time_it(int (*action)(int), int arg)
{
  struct timespec tsi, tsf;

  clock_gettime(CLOCKTYPE, &amp;tsi);
  action(arg);
  clock_gettime(CLOCKTYPE, &amp;tsf);

  double elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
  long elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
  return elaps_s + ((double)elaps_ns) / 1.0e9;
}

int main()
{
  printf(&quot;identity (4) takes %lf s\n&quot;, time_it(identity, 4));
  printf(&quot;sum      (4) takes %lf s\n&quot;, time_it(sum, 4));
  return 0;
}
