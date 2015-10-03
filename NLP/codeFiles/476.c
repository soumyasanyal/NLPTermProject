#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;X11/Xlib.h&gt;
#include &lt;X11/Xutil.h&gt;

int main(int argc, char *argv[])
{
  Display *dpy;
  Window win;
  GC gc;
  int scr;
  Atom WM_DELETE_WINDOW;
  XEvent ev;
  XEvent ev2;
  KeySym keysym;
  int loop;

  /* open connection with the server */
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    fputs(&quot;Cannot open display&quot;, stderr);
    exit(1);
  }
  scr = XDefaultScreen(dpy);

  /* create window */
  win = XCreateSimpleWindow(dpy,
          XRootWindow(dpy, scr),
          /* x, y, width, height, border_width */
          10, 10, 300, 200, 1,
          /* border, background */
          XBlackPixel(dpy, scr), XWhitePixel(dpy, scr));

  /* set window name */
  XStoreName(dpy, win, argv[0]);

  /* select kind of events we are interested in */
  XSelectInput(dpy, win, ExposureMask | KeyPressMask | ButtonPressMask);

  /* map (show) the window */
  XMapWindow(dpy, win);
  XFlush(dpy);

  /* default graphics context */
  gc = XDefaultGC(dpy, scr);

  /* connect the close button in the window handle */
  WM_DELETE_WINDOW = XInternAtom(dpy, &quot;WM_DELETE_WINDOW&quot;, True);
  XSetWMProtocols(dpy, win, &amp;WM_DELETE_WINDOW, 1);

  /* event loop */
  loop = 1;
  while (loop) {
    XNextEvent(dpy, &amp;ev);
    switch (ev.type)
    {
      case Expose:
        /* draw or redraw the window */
        {
          char msg1[] = &quot;Clic in the window to generate&quot;;
          char msg2[] = &quot;a key press event&quot;;
          XDrawString(dpy, win, gc, 10, 20, msg1, sizeof(msg1)-1);
          XDrawString(dpy, win, gc, 10, 35, msg2, sizeof(msg2)-1);
        }
        break;

      case ButtonPress:
        puts(&quot;ButtonPress event received&quot;);
        /*
        printf(&quot;&gt; button (x,y) : %d %d\n&quot;,
               ev.xbutton.x,
               ev.xbutton.y);
        */
        ev2.type = KeyPress;
        ev2.xkey.state = ShiftMask;
        ev2.xkey.keycode = 24 + (rand() % 33);
        ev2.xkey.same_screen = True;
        XSendEvent(dpy, win, True/*propagate*/, KeyPressMask, &amp;ev2);
        break;
   
      case ClientMessage:
        /* delete window event */
        if (ev.xclient.data.l[0] == WM_DELETE_WINDOW)
          loop = 0;
        break;
   
      case KeyPress:
        /* handle key press */
        puts(&quot;KeyPress event received&quot;);
        printf(&quot;&gt; keycode: %d\n&quot;, ev.xkey.keycode);
        /* exit if q or escape are pressed */
        keysym = XLookupKeysym(&amp;(ev.xkey), 0);
        if (keysym == XK_q ||
            keysym == XK_Escape) {
          loop = 0;
        } else {
          char buffer[] = &quot;  &quot;;
          int nchars = XLookupString(
                &amp;(ev.xkey),
                buffer,
                2,  /* buffer size */
                &amp;keysym,
                NULL );
          if (nchars == 1)
            printf(&quot;&gt; Key '%c' pressed\n&quot;, buffer[0]);
        }
        break;
    }
  }
  XDestroyWindow(dpy, win);
  /* close connection to server */
  XCloseDisplay(dpy);
  return 1;
}
