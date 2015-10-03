#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int icmp(const void *a, const void *b)
{
	return *(int*)a &lt; *(int*)b ? -1 : *(int*)a &gt; *(int*)b;
}

void leaf_plot(int *x, int len)
{
	int i, j, d;

	qsort(x, len, sizeof(int), icmp);

	i = x[0] / 10 - 1;
	for (j = 0; j &lt; len; j++) {
		d = x[j] / 10;
		while (d &gt; i) printf(&quot;%s%3d |&quot;, j ? &quot;\n&quot; : &quot;&quot;, ++i);
		printf(&quot; %d&quot;, x[j] % 10);
	}
}

int main()
{
	int data[] = {
	  12, 127,  28,  42,  39, 113,  42,  18,  44, 118,  44,  37, 113, 124,
	  37,  48, 127,  36,  29,  31, 125, 139, 131, 115, 105, 132, 104, 123,
	  35, 113, 122,  42, 117, 119,  58, 109,  23, 105,  63,  27,  44, 105,
	  99,  41, 128, 121, 116, 125,  32,  61,  37, 127,  29, 113, 121,  58,
	 114, 126,  53, 114,  96,  25, 109,   7,  31, 141,  46,  13,  27,  43,
	 117, 116,  27,   7,  68,  40,  31, 115, 124,  42, 128,  52,  71, 118,
	 117,  38,  27, 106,  33, 117, 116, 111,  40, 119,  47, 105,  57, 122,
	 109, 124, 115,  43, 120,  43,  27,  27,  18,  28,  48, 125, 107, 114,
	  34, 133,  45, 120,  30, 127,  31, 116, 146 };

	leaf_plot(data, sizeof(data)/sizeof(data[0]));

	return 0;
}
