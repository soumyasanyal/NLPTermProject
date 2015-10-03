#include &lt;stdio.h&gt;
/* Type marker stick: using bits to indicate what's chosen.  The stick can't
 * handle more than 32 items, but the idea is there; at worst, use array instead */
typedef unsigned long marker;
marker one = 1;

void comb(int pool, int need, marker chosen, int at)
{
	if (pool &lt; need + at) return; /* not enough bits left */

	if (!need) {
		/* got all we needed; print the thing.  if other actions are
		 * desired, we could have passed in a callback function. */
		for (at = 0; at &lt; pool; at++)
			if (chosen &amp; (one &lt;&lt; at)) printf(&quot;%d &quot;, at);
		printf(&quot;\n&quot;);
		return;
	}
	/* if we choose the current item, &quot;or&quot; (|) the bit to mark it so. */
	comb(pool, need - 1, chosen | (one &lt;&lt; at), at + 1);
	comb(pool, need, chosen, at + 1);  /* or don't choose it, go to next */
}

int main()
{
	comb(5, 3, 0, 0);
	return 0;
}
