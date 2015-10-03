#include &lt;sys/stat.h&gt;#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;

int main() { /* permissions are before umask */
  int fd = open(&quot;output.txt&quot;, O_WRONLY|O_CREAT|O_TRUNC, 0640); /* rights 0640 for rw-r----- */
  /* or equivalently:
     int fd = creat(&quot;output.txt&quot;, 0640); */ /* rights 0640 for rw-r----- */
  close(fd);

  mkdir(&quot;docs&quot;, 0750); /* rights 0750 for rwxr-x--- */

  return 0;
}
