#include &lt;stdlib.h&gt;#include &lt;stdio.h&gt;

#define BOTTLE(nstr) nstr &quot; bottles of beer&quot;

#define WALL(nstr) BOTTLE(nstr) &quot; on the wall&quot;

#define PART1(nstr) WALL(nstr) &quot;\n&quot; BOTTLE(nstr) \
                    &quot;\nTake one down, pass it around\n&quot;

#define PART2(nstr) WALL(nstr) &quot;\n\n&quot;

#define MIDDLE(nstr) PART2(nstr) PART1(nstr)

#define SONG PART1(&quot;100&quot;) CD2 PART2(&quot;0&quot;)

#define CD2 CD3(&quot;9&quot;) CD3(&quot;8&quot;) CD3(&quot;7&quot;) CD3(&quot;6&quot;) CD3(&quot;5&quot;) \
        CD3(&quot;4&quot;) CD3(&quot;3&quot;) CD3(&quot;2&quot;) CD3(&quot;1&quot;) CD4(&quot;&quot;)

#define CD3(pre) CD4(pre) MIDDLE(pre &quot;0&quot;)

#define CD4(pre) MIDDLE(pre &quot;9&quot;) MIDDLE(pre &quot;8&quot;) MIDDLE(pre &quot;7&quot;) \
 MIDDLE(pre &quot;6&quot;) MIDDLE(pre &quot;5&quot;) MIDDLE(pre &quot;4&quot;) MIDDLE(pre &quot;3&quot;) \
 MIDDLE(pre &quot;2&quot;) MIDDLE(pre &quot;1&quot;)

int main(void)
{
  (void) printf(SONG);
  return EXIT_SUCCESS;
}
