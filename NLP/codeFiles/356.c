#include &lt;stdio.h&gt; 
char trans[] = &quot;___#_##_&quot;;
 
int evolve(char c[], int len)
{
	int i, diff = 0;
#	define v(i) ((c[i] &amp; 15) == 1)
#	define each for (i = 0; i &lt; len; i++)

	each c[i]  = (c[i] == '#');
	each c[i] |= (trans[(v(i-1)*4 + v(i)*2 + v(i+1))] == '#') &lt;&lt; 4;
	each diff += (c[i] &amp; 0xf) ^ (c[i] &gt;&gt; 4);
	each c[i]  = (c[i] &gt;&gt; 4) ? '#' : '_';

#	undef each
#	undef v
	return diff;
}
 
int main()
{
	char c[] = &quot;_###_##_#_#_#_#__#__\n&quot;;
 
	do { printf(c + 1); } while (evolve(c + 1, sizeof(c) - 3));
	return 0;
}
