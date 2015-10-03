#include &lt;stdio.h&gt;#include &lt;X11/Xlib.h&gt;

int main()
{
  Display *d;
  Window inwin;      /* root window the pointer is in */
  Window inchildwin; /* child win the pointer is in */
  int rootx, rooty; /* relative to the &quot;root&quot; window; we are not interested in these,
                       but we can't pass NULL */
  int childx, childy;  /* the values we are interested in */
  Atom atom_type_prop; /* not interested */
  int actual_format;   /* should be 32 after the call */
  unsigned int mask;   /* status of the buttons */
  unsigned long n_items, bytes_after_ret;
  Window *props; /* since we are interested just in the first value, which is
		    a Window id */

  /* default DISPLAY */
  d = XOpenDisplay(NULL); 

  /* ask for active window (no error check); the client must be freedesktop
     compliant */
  (void)XGetWindowProperty(d, DefaultRootWindow(d),
			   XInternAtom(d, &quot;_NET_ACTIVE_WINDOW&quot;, True),
			   0, 1, False, AnyPropertyType,
			   &amp;atom_type_prop, &amp;actual_format,
			   &amp;n_items, &amp;bytes_after_ret, (unsigned char**)&amp;props);
			  
  XQueryPointer(d, props[0], &amp;inwin,  &amp;inchildwin,
		&amp;rootx, &amp;rooty, &amp;childx, &amp;childy, &amp;mask);
  printf(&quot;relative to active window: %d,%d\n&quot;, childx, childy);

  XFree(props);           /* free mem */
  (void)XCloseDisplay(d); /* and close the display */
  return 0;
}
