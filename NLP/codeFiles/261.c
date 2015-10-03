#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;X11/Xlib.h&gt;
#include &lt;X11/keysym.h&gt;

int main()
{
  Display *d;
  XEvent event;
  
  d = XOpenDisplay(NULL);
  if ( d != NULL ) {
                /* or simply XK_F7 should work too */
    XGrabKey(d, XKeysymToKeycode(d, XStringToKeysym(&quot;F7&quot;)), 
	     Mod1Mask, /* normally it's Alt */ 
	     DefaultRootWindow(d), True, GrabModeAsync, GrabModeAsync);
    XGrabKey(d, XKeysymToKeycode(d, XStringToKeysym(&quot;F6&quot;)), 
	     Mod1Mask, 
	     DefaultRootWindow(d), True, GrabModeAsync, GrabModeAsync);

    for(;;)
    {
      XNextEvent(d, &amp;event);
      if ( event.type == KeyPress ) {
	KeySym s = XLookupKeysym(&amp;event.xkey, 0);
	if ( s == XK_F7 ) {
	  printf(&quot;something's happened\n&quot;);
	} else if ( s == XK_F6 ) {
	  break;
	}
      }
    }

    XUngrabKey(d, XKeysymToKeycode(d, XStringToKeysym(&quot;F7&quot;)), Mod1Mask, DefaultRootWindow(d));
    XUngrabKey(d, XKeysymToKeycode(d, XStringToKeysym(&quot;F6&quot;)), Mod1Mask, DefaultRootWindow(d));
  }
  return EXIT_SUCCESS;
}
