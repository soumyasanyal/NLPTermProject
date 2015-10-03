#include &lt;stdio.h&gt;#include &lt;string.h&gt;

int check_month(int y, int m)
{
	char buf[1024], *ptr;
	int bytes, *a = &amp;m;

	sprintf(buf, &quot;ncal -m %d -M %d&quot;, m, y);
	FILE *fp = popen(buf, &quot;r&quot;);
	if (!fp) return -1;

	bytes = fread(buf, 1, 1024, fp);
	fclose(fp);
	buf[bytes] = 0;

#define check_day(x) \
	ptr = strstr(buf, x);\
	if (5 != sscanf(ptr, x&quot; %d %d %d %d %d&quot;, a, a, a, a, a)) return 0

	check_day(&quot;Fr&quot;);
	check_day(&quot;Sa&quot;);
	check_day(&quot;Su&quot;);
	return 1;
}

int main()
{
	int y, m, cnt = 0;
	for (y = 1900; y &lt;= 2100; y++) {
		for (m = 1; m &lt;= 12; m++) {
			if (check_month(y, m) &lt;= 0) continue;
			printf(&quot;%d-%02d &quot;, y, m);
			if (++cnt % 16 == 0) printf(&quot;\n&quot;);
		}
	}
	printf(&quot;\nTotal: %d\n&quot;, cnt);

	return 0;
}
