#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

int main(void)
{
  FILE *fh = tmpfile(); /* file is automatically deleted when program exits */
  /* do stuff with stream &quot;fh&quot; */
  fclose(fh);
  /* The C standard library also has a tmpnam() function to create a file
    for you to open later. But you should not use it because someone else might
    be able to open the file from the time it is created by this function to the
    time you open it. */
  return 0;
}
