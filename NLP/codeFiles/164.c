#include &lt;sys/stat.h&gt;#include &lt;stdio.h&gt;
#include &lt;time.h&gt;
#include &lt;utime.h&gt;

const char *filename = &quot;input.txt&quot;;

int main() {
  struct stat foo;
  time_t mtime;
  struct utimbuf new_times;

  if (stat(filename, &amp;foo) &lt; 0) {
    perror(filename);
    return 1;
  }
  mtime = foo.st_mtime; /* seconds since the epoch */

  new_times.actime = foo.st_atime; /* keep atime unchanged */
  new_times.modtime = time(NULL);    /* set mtime to current time */
  if (utime(filename, &amp;new_times) &lt; 0) {
    perror(filename);
    return 1;
  }

  return 0;
}
