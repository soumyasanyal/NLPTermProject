#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int rand_i(int n)
{
	int rand_max = RAND_MAX - (RAND_MAX % n);
	int ret;
	while ((ret = rand()) &gt;= rand_max);
	return ret/(rand_max / n);
}

int weighed_rand(int *tbl, int len)
{
	int i, sum, r;
	for (i = 0, sum = 0; i &lt; len; sum += tbl[i++]);
	if (!sum) return rand_i(len);

	r = rand_i(sum) + 1;
	for (i = 0; i &lt; len &amp;&amp; (r -= tbl[i]) &gt; 0; i++);
	return i;
}

int main()
{
	int user_action, my_action;
	int user_rec[] = {0, 0, 0};
	char *names[] = { &quot;Rock&quot;, &quot;Paper&quot;, &quot;Scissors&quot; };
	char str[2];
	char *winner[] = { &quot;We tied.&quot;, &quot;Meself winned.&quot;, &quot;You win.&quot; };

	while (1) {
		my_action = (weighed_rand(user_rec, 3) + 1) % 3;

		printf(&quot;\nYour choice [1-3]:\n&quot;
			&quot;  1. Rock\n  2. Paper\n  3. Scissors\n&gt; &quot;);

		/* scanf is a terrible way to do input.  should use stty and keystrokes */
		if (!scanf(&quot;%d&quot;, &amp;user_action)) {
			scanf(&quot;%1s&quot;, str);
			if (*str == 'q') return 0;
			continue;
		}
		user_action --;
		if (user_action &gt; 2 || user_action &lt; 0) {
			printf(&quot;invalid choice; again\n&quot;);
			continue;
		}
		printf(&quot;You chose %s; I chose %s. %s\n&quot;,
			names[user_action], names[my_action],
			winner[(my_action - user_action + 3) % 3]);

		user_rec[user_action]++;
	}
}
