#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main()
{
  char *buffer;
  FILE *fh = fopen(&quot;readentirefile.c&quot;, &quot;rb&quot;);
  if ( fh != NULL )
  {
    fseek(fh, 0L, SEEK_END);
    long s = ftell(fh);
    rewind(fh);
    buffer = malloc(s);
    if ( buffer != NULL )
    {
      fread(buffer, s, 1, fh);
      // we can now close the file
      fclose(fh); fh = NULL;
      
      // do something, e.g.
      fwrite(buffer, s, 1, stdout);

      free(buffer);
    }
    if (fh != NULL) fclose(fh);
  }
  return EXIT_SUCCESS;
}
