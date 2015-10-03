#include &lt;sys/stat.h&gt;#include &lt;sys/time.h&gt;
#include &lt;time.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;stdio.h&gt;

const char *filename = &quot;input.txt&quot;;
 
int main() {
  struct stat foo;
  struct timespec new_times[2];
 
  if (stat(filename, &amp;foo) &lt; 0) {
    perror(filename);
    return 1;
  }
 
  /* keep atime unchanged */
  new_times[0] = foo.st_atim;
 
  /* set mtime to current time */
  clock_gettime(CLOCK_REALTIME, &amp;new_times[1]);
 
  if (utimensat(AT_FDCWD, filename, new_times, 0) &lt; 0) {
    perror(filename);
    return 1;
  }
 
  return 0;
}
