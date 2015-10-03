#include &lt;X11/Xlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

int main(void) {
   Display *d;
   Window w;
   XEvent e;
   char *msg = &quot;Hello, World!&quot;;
   int s;

   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, &quot;Cannot open display\n&quot;);
      exit(1);
   }

   s = DefaultScreen(d);
   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);

   while (1) {
      XNextEvent(d, &amp;e);
      if (e.type == Expose) {
         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
      }
      if (e.type == KeyPress)
         break;
   }

   XCloseDisplay(d);
   return 0;
}
