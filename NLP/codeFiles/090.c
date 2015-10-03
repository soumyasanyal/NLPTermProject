#include &lt;stdio.h&gt;#include &lt;omp.h&gt;

int main()
{
	char *str[] = { &quot;Enjoy&quot;, &quot;Rosetta&quot;, &quot;Code&quot; };
	#pragma omp parallel for num_threads(3)
	for (int i = 0; i &lt; 3; i++)
		printf(&quot;%s\n&quot;, str[i]);
}
