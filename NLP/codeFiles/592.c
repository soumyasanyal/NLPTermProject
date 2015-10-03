/* 2009-09-27 &lt;kaz@kylheku.com&gt; */#define ANIMATE_VT100_POSIX
#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#ifdef ANIMATE_VT100_POSIX
#include &lt;time.h&gt;
#endif

char world_7x14[2][512] = {
  {
    &quot;+-----------+\n&quot;
    &quot;|tH.........|\n&quot;
    &quot;|.   .      |\n&quot;
    &quot;|   ...     |\n&quot;
    &quot;|.   .      |\n&quot;
    &quot;|Ht.. ......|\n&quot;
    &quot;+-----------+\n&quot;
  }
};

void next_world(const char *in, char *out, int w, int h)
{
  int i;

  for (i = 0; i &lt; w*h; i++) {
    switch (in[i]) {
    case ' ': out[i] = ' '; break;
    case 't': out[i] = '.'; break;
    case 'H': out[i] = 't'; break;
    case '.': {
      int hc = (in[i-w-1] == 'H') + (in[i-w] == 'H') + (in[i-w+1] == 'H') +
               (in[i-1]   == 'H')                    + (in[i+1]   == 'H') +
               (in[i+w-1] == 'H') + (in[i+w] == 'H') + (in[i+w+1] == 'H');
      out[i] = (hc == 1 || hc == 2) ? 'H' : '.';
      break;
    }
    default:
      out[i] = in[i];
    }
  }
  out[i] = in[i];
}

int main()
{
  int f;

  for (f = 0; ; f = 1 - f) {
#ifdef ANIMATE_VT100_POSIX
    puts(&quot;\x1b[H&quot;);
#endif
    puts(world_7x14[f]);
    next_world(world_7x14[f], world_7x14[1-f], 14, 7);
#ifdef ANIMATE_VT100_POSIX
    {
      static const struct timespec ts = { 0, 100000000 };
      nanosleep(&amp;ts, 0);
    }
#endif
  }

  return 0;
}
