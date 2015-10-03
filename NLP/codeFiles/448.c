#include &lt;stdio.h&gt;#include &lt;math.h&gt;

int main()
{
	double a, c, s, PI2 = atan2(1, 1) * 8;
	int n, i;

	for (n = 1; n &lt; 10; n++) for (i = 0; i &lt; n; i++) {
		c = s = 0;
		if (!i )		c =  1;
		else if(n == 4 * i)	s =  1;
		else if(n == 2 * i)	c = -1;
		else if(3 * n == 4 * i)	s = -1;
		else
			a = i * PI2 / n, c = cos(a), s = sin(a);

		if (c) printf(&quot;%.2g&quot;, c);
		printf(s == 1 ? &quot;i&quot; : s == -1 ? &quot;-i&quot; : s ? &quot;%+.2gi&quot; : &quot;&quot;, s);
		printf(i == n - 1 ?&quot;\n&quot;:&quot;,  &quot;);
	}

	return 0;
}
