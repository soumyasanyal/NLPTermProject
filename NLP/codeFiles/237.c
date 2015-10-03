#include &lt;stdio.h&gt;#include &lt;math.h&gt;

#define PICKVALUE(TXT, VM) do {			\
    printf(&quot;%s: &quot;, TXT);			\
    scanf(&quot;%lf&quot;, &amp;VM);				\
  } while(0);

#if !defined(M_PI)
#define M_PI 3.14159265358979323846
#endif

#define DR(X) ((X)*M_PI/180.0)
#define RD(X) ((X)*180.0/M_PI)

int main()
{
  double lat, slat, lng, ref;
  int h;
  
  PICKVALUE(&quot;Enter latitude&quot;, lat);
  PICKVALUE(&quot;Enter longitude&quot;, lng);
  PICKVALUE(&quot;Enter legal meridian&quot;, ref);
  printf(&quot;\n&quot;);

  slat = sin(DR(lat));
  printf(&quot;sine of latitude: %.3f\n&quot;, slat);
  printf(&quot;diff longitude: %.3f\n\n&quot;, lng - ref);
  
  printf(&quot;Hour, sun hour angle, dial hour line angle from 6am to 6pm\n&quot;);
  
  for(h = -6; h &lt;= 6; h++)
  {
    double hla, hra;
    hra = 15.0*h;
    hra = hra - lng + ref;
    hla = RD(atan(slat * tan(DR(hra))));
    printf(&quot;HR= %3d;  \t  HRA=%7.3f;  \t  HLA= %7.3f\n&quot;,
	   h, hra, hla);
  }

  return 0;
}
