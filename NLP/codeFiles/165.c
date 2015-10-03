#include &lt;sys/stat.h&gt;#include &lt;sys/time.h&gt;
#include &lt;err.h&gt;

const char *filename = &quot;input.txt&quot;;

int main() {
  struct stat foo;
  struct timeval new_times[2];

  if (stat(filename, &amp;foo) &lt; 0)
    err(1, &quot;%s&quot;, filename);

  /* keep atime unchanged */
  TIMESPEC_TO_TIMEVAL(&amp;new_times[0], &amp;foo.st_atim);

  /* set mtime to current time */
  gettimeofday(&amp;new_times[1], NULL);

  if (utimes(filename, new_times) &lt; 0)
    err(1, &quot;%s&quot;, filename);

  return 0;
}
