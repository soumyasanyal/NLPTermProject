#include &lt;stdio.h&gt;#include &lt;stdarg.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;stdbool.h&gt;
#include &lt;curses.h&gt;
#include &lt;string.h&gt;

#define MAX_NUM_TRIES 72
#define LINE_BEGIN 7
#define LAST_LINE 18

int yp=LINE_BEGIN, xp=0;

char number[5];
char guess[5];

#define MAX_STR 256
void mvaddstrf(int y, int x, const char *fmt, ...)
{
  va_list args;
  char buf[MAX_STR];
  
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  move(y, x);
  clrtoeol();
  addstr(buf);
  va_end(args);
}

void ask_for_a_number()
{
  int i=0;
  char symbols[] = &quot;123456789&quot;;

  move(5,0); clrtoeol();
  addstr(&quot;Enter four digits: &quot;);
  while(i&lt;4) {
    int c = getch();
    if ( (c &gt;= '1') &amp;&amp; (c &lt;= '9') &amp;&amp; (symbols[c-'1']!=0) ) {
      addch(c);
      symbols[c-'1'] = 0;
      guess[i++] = c;
    }
  }
}

void choose_the_number()
{
  int i=0, j;
  char symbols[] = &quot;123456789&quot;;

  while(i&lt;4) {
    j = rand() % 9;
    if ( symbols[j] != 0 ) {
      number[i++] = symbols[j];
      symbols[j] = 0;
    }
  }
}
