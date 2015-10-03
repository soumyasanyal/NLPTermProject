#include &lt;stdio.h&gt; 
int main()
{
	printf(&quot;This code was in file %s in function %s, at line %d\n&quot;,\
		__FILE__, __FUNCTION__, __LINE__);
	return 0;
}
