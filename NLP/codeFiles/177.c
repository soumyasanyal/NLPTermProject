#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;
#include &lt;math.h&gt;
 
/* declare a typedef for a function pointer */
typedef double (*Class2Func)(double);
 
/*A couple of functions with the above prototype */
double functionA( double v)
{
   return v*v*v;
}
double functionB(double v)
{
   return exp(log(v)/3);
}
 
/* A function taking a function as an argument */
double Function1( Class2Func f2, double val )
{
    return f2(val);
}
 
/*A function returning a function */
Class2Func WhichFunc( int idx)
{
   return (idx &lt; 4) ? &amp;functionA : &amp;functionB;
}
 
/* A list of functions */
Class2Func funcListA[] = {&amp;functionA, &amp;sin, &amp;cos, &amp;tan };
Class2Func funcListB[] = {&amp;functionB, &amp;asin, &amp;acos, &amp;atan };
 
/* Composing Functions */
double InvokeComposed( Class2Func f1, Class2Func f2, double val )
{
   return f1(f2(val));
}
 
typedef struct sComposition {
   Class2Func f1;
   Class2Func f2;
} *Composition;
 
Composition Compose( Class2Func f1, Class2Func f2)
{
   Composition comp = malloc(sizeof(struct sComposition));
   comp-&gt;f1 = f1;
   comp-&gt;f2 = f2;
   return comp;
}
 
double CallComposed( Composition comp, double val )
{
    return comp-&gt;f1( comp-&gt;f2(val) );
}
/** * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
int main(int argc, char *argv[])
{
   int ix;
   Composition c;
 
   printf(&quot;Function1(functionA, 3.0) = %f\n&quot;, Function1(WhichFunc(0), 3.0));
 
   for (ix=0; ix&lt;4; ix++) {
       c = Compose(funcListA[ix], funcListB[ix]);
       printf(&quot;Compostion %d(0.9) = %f\n&quot;, ix, CallComposed(c, 0.9));
   }
 
   return 0;
}
