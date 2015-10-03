#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

int b[3][3]; /* board. 0: blank; -1: computer; 1: human */

int check_winner()
{
	int i;
	for (i = 0; i &lt; 3; i++) {
		if (b[i][0] &amp;&amp; b[i][1] == b[i][0] &amp;&amp; b[i][2] == b[i][0])
			return b[i][0];
		if (b[0][i] &amp;&amp; b[1][i] == b[0][i] &amp;&amp; b[2][i] == b[0][i])
			return b[0][i];
	}
	if (!b[1][1]) return 0;

	if (b[1][1] == b[0][0] &amp;&amp; b[2][2] == b[0][0]) return b[0][0];
	if (b[1][1] == b[2][0] &amp;&amp; b[0][2] == b[1][1]) return b[1][1];

	return 0;
}

void showboard()
{
	char *t = &quot;X O&quot;;
	int i, j;
	for (i = 0; i &lt; 3; i++, putchar('\n'))
		for (j = 0; j &lt; 3; j++)
			printf(&quot;%c &quot;, t[ b[i][j] + 1 ]);
	printf(&quot;-----\n&quot;);
}

#define for_ij for (i = 0; i &lt; 3; i++) for (j = 0; j &lt; 3; j++)
int best_i, best_j;
int test_move(int val, int depth)
{
	int i, j, score;
	int best = -1, changed = 0;

	if ((score = check_winner())) return (score == val) ? 1 : -1;

	for_ij {
		if (b[i][j]) continue;

		changed = b[i][j] = val;
		score = -test_move(-val, depth + 1);
		b[i][j] = 0;

		if (score &lt;= best) continue;
		if (!depth) {
			best_i = i;
			best_j = j;
		}
		best = score;
	}

	return changed ? best : 0;
}

char* game(int user)
{
	int i, j, k, move, win = 0;
	for_ij b[i][j] = 0;

	printf(&quot;Board postions are numbered so:\n1 2 3\n4 5 6\n7 8 9\n&quot;);
	printf(&quot;You have O, I have X.\n\n&quot;);
	for (k = 0; k &lt; 9; k++, user = !user) {
		while(user) {
			printf(&quot;your move: &quot;);
			if (!scanf(&quot;%d&quot;, &amp;move)) {
				scanf(&quot;%*s&quot;);
				continue;
			}
			if (--move &lt; 0 || move &gt;= 9) continue;
			if (b[i = move / 3][j = move % 3]) continue;

			b[i][j] = 1;
			break;
		}
		if (!user) {
			if (!k) { /* randomize if computer opens, less boring */
				best_i = rand() % 3;
				best_j = rand() % 3;
			} else
				test_move(-1, 0);

			b[best_i][best_j] = -1;
			printf(&quot;My move: %d\n&quot;, best_i * 3 + best_j + 1);
		}

		showboard();
		if ((win = check_winner())) 
			return win == 1 ? &quot;You win.\n\n&quot;: &quot;I win.\n\n&quot;;
	}
	return &quot;A draw.\n\n&quot;;
}

int main()
{
	int first = 0;
	while (1) printf(game(first = !first));
	return 0;
}
