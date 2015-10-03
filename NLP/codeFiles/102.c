#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main()
{
	int i;
	printf(&quot;&lt;table style=\&quot;text-align:center; border: 1px solid\&quot;&gt;&lt;th&gt;&lt;/th&gt;&quot;
		&quot;&lt;th&gt;X&lt;/th&gt;&lt;th&gt;Y&lt;/th&gt;&lt;th&gt;Z&lt;/th&gt;&quot;);
	for (i = 0; i &lt; 4; i++) {
		printf(&quot;&lt;tr&gt;&lt;th&gt;%d&lt;/th&gt;&lt;td&gt;%d&lt;/td&gt;&lt;td&gt;%d&lt;/td&gt;&lt;td&gt;%d&lt;/td&gt;&lt;/tr&gt;&quot;, i,
			rand() % 10000, rand() % 10000, rand() % 10000);
	}
	printf(&quot;&lt;/table&gt;&quot;);

	return 0;
}
