#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;sys/mman.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;

int main()
{
  char *buffer;
  struct stat s;

  int fd = open(&quot;readentirefile_mm.c&quot;, O_RDONLY);
  if (fd &lt; 0 ) return EXIT_FAILURE;
  fstat(fd, &amp;s);
  /* PROT_READ disallows writing to buffer: will segv */
  buffer = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  if ( buffer != (void*)-1 )
  {
    /* do something */
    fwrite(buffer, s.st_size, 1, stdout);
    munmap(buffer, s.st_size);
  }

  close(fd);
  return EXIT_SUCCESS;
}
