#include &lt;stdio.h&gt;#include &lt;assert.h&gt;

int ipow(int base, int exp)
{
   int pow = base;
   int v = 1;
   if (exp &lt; 0) {
      assert (base != 0);  /* divide by zero */
      return (base*base != 1)? 0: (exp&amp;1)? base : 1;
   }
       
   while(exp &gt; 0 )
   {
      if (exp &amp; 1) v *= pow;
      pow *= pow;
      exp &gt;&gt;= 1;
    }
   return v;
}

double dpow(double base, int exp)
{
   double v=1.0;
   double pow = (exp &lt;0)? 1.0/base : base;
   if (exp &lt; 0) exp = - exp;

   while(exp &gt; 0 )
   {
      if (exp &amp; 1) v *= pow;
      pow *= pow;
      exp &gt;&gt;= 1;
   }
   return v;
}

int main()
{
    printf(&quot;2^6 = %d\n&quot;, (int)ipow(2,6));
    printf(&quot;2^-6 = %lf\n&quot;, ipow(2,-6));
    printf(&quot;2.71^6 = %lf\n&quot;, dpow(2.71,6));
    printf(&quot;2.71^-6 = %lf\n&quot;, dpow(2.71,-6));
}
