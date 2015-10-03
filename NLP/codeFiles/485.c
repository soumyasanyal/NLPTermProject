#include &lt;stdlib.h&gt;  /* qsort() */#include &lt;stdio.h&gt;   /* printf() */

int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a &lt; *b) ? -1 : (*a &gt; *b);
}

int main()
{
    int nums[5] = {2,4,3,1,2};
    qsort(nums, 5, sizeof(int), intcmp);
    printf(&quot;result: %d %d %d %d %d\n&quot;,
      nums[0], nums[1], nums[2], nums[3], nums[4]);
    return 0;
}
