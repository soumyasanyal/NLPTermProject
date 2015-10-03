#include&lt;string.h&gt;#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;

int main(void)
{
	char *a[5];
	const char *s=&quot;Hello,How,Are,You,Today&quot;;
	int n=0, nn;

	char *ds=strdup(s);

	a[n]=strtok(ds, &quot;,&quot;);
	while(a[n] &amp;&amp; n&lt;4) a[++n]=strtok(NULL, &quot;,&quot;);

	for(nn=0; nn&lt;=n; ++nn) printf(&quot;%s.&quot;, a[nn]);
	putchar('\n');

	free(ds);

	return 0;
}
