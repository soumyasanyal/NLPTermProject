#include &lt;stdio.h&gt;
int verbose = 0;
enum {
	clown = -1,
	abe, bob, col, dan, ed, fred, gav, hal, ian, jon,
	abi, bea, cath, dee, eve, fay, gay, hope, ivy, jan,
};
char *name[] = {
	&quot;Abe&quot;, &quot;Bob&quot;, &quot;Col&quot;,  &quot;Dan&quot;, &quot;Ed&quot;,  &quot;Fred&quot;, &quot;Gav&quot;, &quot;Hal&quot;,  &quot;Ian&quot;, &quot;Jon&quot;,
	&quot;Abi&quot;, &quot;Bea&quot;, &quot;Cath&quot;, &quot;Dee&quot;, &quot;Eve&quot;, &quot;Fay&quot;,  &quot;Gay&quot;, &quot;Hope&quot;, &quot;Ivy&quot;, &quot;Jan&quot;
};
int pref[jan + 1][jon + 1] = {
	{ abi, eve, cath, ivy, jan, dee, fay, bea, hope, gay },
	{ cath, hope, abi, dee, eve, fay, bea, jan, ivy, gay },
	{ hope, eve, abi, dee, bea, fay, ivy, gay, cath, jan },
	{ ivy, fay, dee, gay, hope, eve, jan, bea, cath, abi },
	{ jan, dee, bea, cath, fay, eve, abi, ivy, hope, gay },
	{ bea, abi, dee, gay, eve, ivy, cath, jan, hope, fay },
	{ gay, eve, ivy, bea, cath, abi, dee, hope, jan, fay },
	{ abi, eve, hope, fay, ivy, cath, jan, bea, gay, dee },
	{ hope, cath, dee, gay, bea, abi, fay, ivy, jan, eve },
	{ abi, fay, jan, gay, eve, bea, dee, cath, ivy, hope },

	{ bob, fred, jon, gav, ian, abe, dan, ed, col, hal   },
	{ bob, abe, col, fred, gav, dan, ian, ed, jon, hal   },
	{ fred, bob, ed, gav, hal, col, ian, abe, dan, jon   },
	{ fred, jon, col, abe, ian, hal, gav, dan, bob, ed   },
	{ jon, hal, fred, dan, abe, gav, col, ed, ian, bob   },
	{ bob, abe, ed, ian, jon, dan, fred, gav, col, hal   },
	{ jon, gav, hal, fred, bob, abe, col, ed, dan, ian   },
	{ gav, jon, bob, abe, ian, dan, hal, ed, col, fred   },
	{ ian, col, hal, gav, fred, bob, abe, ed, jon, dan   },
	{ ed, hal, gav, abe, bob, jon, col, ian, fred, dan   },
};
int pairs[jan + 1], proposed[jan + 1];

void engage(int man, int woman)
{
	pairs[man] = woman;
	pairs[woman] = man;
	if (verbose) printf(&quot;%4s is engaged to %4s\n&quot;, name[man], name[woman]);
}

void dump(int woman, int man)
{
	pairs[man] = pairs[woman] = clown;
	if (verbose) printf(&quot;%4s dumps %4s\n&quot;, name[woman], name[man]);
}

/* how high this person ranks that: lower is more preferred */
int rank(int this, int that)
{
	int i;
	for (i = abe; i &lt;= jon &amp;&amp; pref[this][i] != that; i++);
	return i;
}

void propose(int man, int woman)
{
	int fiance = pairs[woman];
	if (verbose) printf(&quot;%4s proposes to %4s\n&quot;, name[man], name[woman]);

	if (fiance == clown) {
		engage(man, woman);
	} else if (rank(woman, man) &lt; rank(woman, fiance)) {
		dump(woman, fiance);
		engage(man, woman);
	}
}

int covet(int man1, int wife2)
{
	if (rank(man1, wife2) &lt; rank(man1, pairs[man1]) &amp;&amp;
			rank(wife2, man1) &lt; rank(wife2, pairs[wife2])) {
		printf( &quot;    %4s (w/ %4s) and %4s (w/ %4s) prefer each other&quot;
			&quot; over current pairing.\n&quot;,
			name[man1], name[pairs[man1]], name[wife2], name[pairs[wife2]]
		);
		return 1;
	}
	return 0;
}

int thy_neighbors_wife(int man1, int man2)
{	/* +: force checking all pairs; &quot;||&quot; would shortcircuit */
	return covet(man1, pairs[man2]) + covet(man2, pairs[man1]);
}

int unstable()
{
	int i, j, bad = 0;
	for (i = abe; i &lt; jon; i++) {
		for (j = i + 1; j &lt;= jon; j++)
			if (thy_neighbors_wife(i, j)) bad = 1;
	}
	return bad;
}

int main()
{
	int i, unengaged;
	/* init: everyone marries the clown */
	for (i = abe; i &lt;= jan; i++)
		pairs[i] = proposed[i] = clown;

	/* rounds */
	do {
		unengaged = 0;
		for (i = abe; i &lt;= jon; i++) {
		//for (i = abi; i &lt;= jan; i++) { /* could let women propose */
			if (pairs[i] != clown) continue;
			unengaged = 1;
			propose(i, pref[i][++proposed[i]]);
		}
	} while (unengaged);

	printf(&quot;Pairing:\n&quot;);
	for (i = abe; i &lt;= jon; i++)
		printf(&quot;  %4s - %s\n&quot;, name[i],
			pairs[i] == clown ? &quot;clown&quot; : name[pairs[i]]);

	printf(unstable()
		? &quot;Marriages not stable\n&quot; /* draw sad face here */
		: &quot;Stable matchup\n&quot;);

	printf(&quot;\nBut if Bob and Fred were to swap:\n&quot;);
	i = pairs[bob];
	engage(bob, pairs[fred]);
	engage(fred, i);
	printf(unstable() ? &quot;Marriages not stable\n&quot; : &quot;Stable matchup\n&quot;);

	return 0;
}
