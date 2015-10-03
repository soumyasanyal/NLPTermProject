#include &lt;stdio.h&gt;#include &lt;string.h&gt;

char trans[] = &quot;___#_##_&quot;;

#define v(i) (cell[i] != '_')
int evolve(char cell[], char backup[], int len)
{
	int i, diff = 0;

	for (i = 0; i &lt; len; i++) {
		/* use left, self, right as binary number bits for table index */
		backup[i] = trans[ v(i-1) * 4 + v(i) * 2 + v(i + 1) ];
		diff += (backup[i] != cell[i]);
	}

	strcpy(cell, backup);
	return diff;
}

int main()
{
	char	c[] = &quot;_###_##_#_#_#_#__#__\n&quot;,
		b[] = &quot;____________________\n&quot;;

	do { printf(c + 1); } while (evolve(c + 1, b + 1, sizeof(c) - 3));
	return 0;
}
