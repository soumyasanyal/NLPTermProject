#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;
#include &lt;stdbool.h&gt;

#define SIDE 600
#define NUM_PARTICLES 10000

bool W[SIDE][SIDE];

int main() {
    srand((unsigned)time(NULL));
    W[SIDE / 2][SIDE / 2] = true;

    for (int i = 0; i &lt; NUM_PARTICLES; i++) {
        unsigned int x, y;
        OVER: do {
            x = rand() % (SIDE - 2) + 1;
            y = rand() % (SIDE - 2) + 1;
        } while (W[y][x]);

        while (W[y-1][x-1] + W[y-1][x] + W[y-1][x+1] +
               W[y][x-1]               + W[y][x+1] +
               W[y+1][x-1] + W[y+1][x] + W[y+1][x+1] == 0) {
            unsigned int dxy = rand() % 8;
            if (dxy &gt; 3) dxy++;
            x += (dxy % 3) - 1;
            y += (dxy / 3) - 1;
            if (x &lt; 1 || x &gt;= SIDE - 1 || y &lt; 1 || y &gt;= SIDE - 1)
                goto OVER;
        }

        W[y][x] = true;
    }

    printf(&quot;P1\n%d %d\n&quot;, SIDE, SIDE);
    for (int r = 0; r &lt; SIDE; r++) {
        for (int c = 0; c &lt; SIDE; c++)
            printf(&quot;%d &quot;, W[r][c]);
        putchar('\n');
    }
    return 0;
}
