#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

struct {
	double val, wgt, vol;
	char * name;
} items[] = { // value in hundreds, volume in thousandths
	{30, .3, 25,	&quot;panacea&quot;},
	{18, .2, 15,	&quot;ichor&quot;},
	{25, 2.,  2,	&quot;gold&quot;},
	{0,0,0,0}
};

/* silly setup for silly task */
int best_cnt[16] = {0}, cnt[16] = {0};
double best_v = 0;

void grab_em(int idx, double cap_v, double cap_w, double v)
{
	double val;
	int t = cap_w / items[idx].wgt;
	cnt[idx] = cap_v / items[idx].vol;

	if (cnt[idx] &gt; t) cnt[idx] = t;

	while (cnt[idx] &gt;= 0) {
		val = v + cnt[idx] * items[idx].val;
		if (!items[idx + 1].name) {
			if (val &gt; best_v) {
				best_v = val;
				memcpy(best_cnt, cnt, sizeof(int) * (1 + idx));
			}
			return;
		}
		grab_em(idx + 1, cap_v - cnt[idx] * items[idx].vol,
			cap_w - cnt[idx] * items[idx].wgt, val);
		cnt[idx]--;
	}
}

int main(void)
{
	int i;

	grab_em(0, 250, 25, 0);
	printf(&quot;value: %g hundreds\n&quot;, best_v);
	for (i = 0; items[i].name; i++)
		printf(&quot;%d %s\n&quot;, best_cnt[i], items[i].name);

	return 0;
}
