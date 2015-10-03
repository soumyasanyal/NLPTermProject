#include &lt;math.h&gt;#include &lt;stdio.h&gt;

int main() {
  double pi = 4 * atan(1);
  /*Pi / 4 is 45 degrees. All answers should be the same.*/
  double radians = pi / 4;
  double degrees = 45.0;
  double temp;
  /*sine*/
  printf(&quot;%f %f\n&quot;, sin(radians), sin(degrees * pi / 180));
  /*cosine*/
  printf(&quot;%f %f\n&quot;, cos(radians), cos(degrees * pi / 180));
  /*tangent*/
  printf(&quot;%f %f\n&quot;, tan(radians), tan(degrees * pi / 180));
  /*arcsine*/
  temp = asin(sin(radians));
  printf(&quot;%f %f\n&quot;, temp, temp * 180 / pi);
  /*arccosine*/
  temp = acos(cos(radians));
  printf(&quot;%f %f\n&quot;, temp, temp * 180 / pi);
  /*arctangent*/
  temp = atan(tan(radians));
  printf(&quot;%f %f\n&quot;, temp, temp * 180 / pi);

  return 0;
}
