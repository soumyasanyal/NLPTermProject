#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;sys/types.h&gt;

#define INOUT_LEN 4
#define TIME_LEN 20
#define MAX_MAXOUT 1000

char inout[INOUT_LEN];
char time[TIME_LEN];
uint jobnum;

char maxtime[MAX_MAXOUT][TIME_LEN];

int main(int argc, char **argv)
{
  FILE *in = NULL;
  int l_out = 0, maxout=-1, maxcount=0;

  if ( argc &gt; 1 ) {
    in = fopen(argv[1], &quot;r&quot;);
    if ( in == NULL ) {
      fprintf(stderr, &quot;cannot read %s\n&quot;, argv[1]);
      exit(1);
    }
  } else {
    in = stdin;
  }

  while( fscanf(in, &quot;License %s @ %s for job %u\n&quot;, inout, time, &amp;jobnum) != EOF ) {

    if ( strcmp(inout, &quot;OUT&quot;) == 0 )
      l_out++;
    else
      l_out--;

    if ( l_out &gt; maxout ) {
      maxout = l_out;
      maxcount=0; maxtime[0][0] = '\0';
    }
    if ( l_out == maxout ) {
      if ( maxcount &lt; MAX_MAXOUT ) {
	strncpy(maxtime[maxcount], time, TIME_LEN);
	maxcount++;
      } else {
	fprintf(stderr, &quot;increase MAX_MAXOUT (now it is %u)\n&quot;, MAX_MAXOUT);
	exit(1);
      }
    }
  }

  printf(&quot;Maximum simultaneous license use is %d at the following times:\n&quot;, maxout);
  for(l_out=0; l_out &lt; maxcount; l_out++) {
    printf(&quot;%s\n&quot;, maxtime[l_out]);
  }

  if ( in != stdin ) fclose(in);
  exit(0);
}
