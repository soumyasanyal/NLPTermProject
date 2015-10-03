#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;locale.h&gt;

int main()
{
	setlocale(LC_CTYPE, &quot;&quot;);
	char moose[] = &quot;møøse&quot;;
	printf(&quot;bytes: %d\n&quot;, sizeof(moose) - 1);
	printf(&quot;chars: %d\n&quot;, (int)mbstowcs(0, moose, 0));

	return 0;
}
