#include &lt;stdlib.h&gt; /* for bsearch */#include &lt;stdio.h&gt;

int intcmp(const void *a, const void *b)
{
    /* this is only correct if it doesn't overflow */
    return *(const int *)a - *(const int *)b;
}

int main()
{
    int nums[5] = {2, 3, 5, 6, 8};
    int desired = 6;
    int *ptr = bsearch(&amp;desired, nums, 5, sizeof(int), intcmp);
    if (ptr == NULL)
        printf(&quot;not found\n&quot;);
    else
        printf(&quot;index = %d\n&quot;, ptr - nums);

    return 0;
}
