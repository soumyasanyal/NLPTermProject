#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt; // atoi()
#include &lt;math.h&gt; // pow()

int main(int argc, char* argv[])
{
  int i, count=0;
  double f, sum=0.0, prod=1.0, resum=0.0;

  for (i=1; i&lt;argc; ++i) {
    f = atof(argv[i]);
    count++;
    sum += f;
    prod *= f;
    resum += (1.0/f);
  }
  //printf(&quot; c:%d\n s:%f\n p:%f\n r:%f\n&quot;,count,sum,prod,resum);
  printf(&quot;Arithmetic mean = %f\n&quot;,sum/count);
  printf(&quot;Geometric mean = %f\n&quot;,pow(prod,(1.0/count)));
  printf(&quot;Harmonic mean = %f\n&quot;,count/resum);

  return 0;
}
