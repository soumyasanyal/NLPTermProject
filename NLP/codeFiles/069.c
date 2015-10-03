#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;dlfcn.h&gt;

int myopenimage(const char *in)
{
  static int handle=0;
  fprintf(stderr, &quot;internal openimage opens %s...\n&quot;, in);
  return handle++;
}

int main()
{
  void *imglib;
  int (*extopenimage)(const char *);
  int imghandle;

  imglib = dlopen(&quot;./fakeimglib.so&quot;, RTLD_LAZY);
  if ( imglib != NULL ) {
    /* extopenimage = (int (*)(const char *))dlsym(imglib,...)
       &quot;man dlopen&quot; says that C99 standard leaves casting from
       &quot;void *&quot; to a function pointer undefined. The following is the
       POSIX.1-2003 workaround found in man */
    *(void **)(&amp;extopenimage) = dlsym(imglib, &quot;openimage&quot;);
    /* the following works with gcc, gives no warning even with
       -Wall -std=c99 -pedantic options... :D */
    /* extopenimage = dlsym(imglib, &quot;openimage&quot;); */
    imghandle = extopenimage(&quot;fake.img&quot;);
  } else {
    imghandle = myopenimage(&quot;fake.img&quot;);
  }
  printf(&quot;opened with handle %d\n&quot;, imghandle);
  /* ... */
  if (imglib != NULL ) dlclose(imglib);
  return EXIT_SUCCESS;
}
