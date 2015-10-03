#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int main(int c, char *v[])
{
	int days[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	int m, y, w;

	if (c &lt; 2 || (y = atoi(v[1])) &lt;= 1700) return 1;
 	days[1] -= (y % 4) || (!(y % 100) &amp;&amp; (y % 400));
	w = y * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400 + 6;

	for(m = 0; m &lt; 12; m++) {
		w = (w + days[m]) % 7;
		printf(&quot;%d-%02d-%d\n&quot;, y, m + 1,
			days[m] + (w &lt; 5 ? -2 : 5) - w);
	}

	return 0;
}
