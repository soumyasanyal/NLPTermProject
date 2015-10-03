#include &lt;stdio.h&gt;
double mapRange(double a1,double a2,double b1,double b2,double s)
{
	return b1 + (s-a1)*(b2-b1)/(a2-a1);
}

int main()
{
	int i;
	puts(&quot;Mapping [0,10] to [-1,0] at intervals of 1:&quot;);
	
	for(i=0;i&lt;=10;i++)
	{
		printf(&quot;f(%d) = %g\n&quot;,i,mapRange(0,10,-1,0,i));
	}
	
	return 0;
}

