#include &lt;stdlib.h&gt;  /* for qsort */#include &lt;string.h&gt;  /* for strlen */
#include &lt;strings.h&gt; /* for strcasecmp */

int mycmp(const void *s1, const void *s2)
{
    const char *l = *(const char **)s1, *r = *(const char **)s2;
    size_t ll = strlen(l), lr = strlen(r);

    if (ll &gt; lr) return -1;
    if (ll &lt; lr) return 1;
    return strcasecmp(l, r);
}

int main()
{
    const char *strings[] = {
      &quot;Here&quot;, &quot;are&quot;, &quot;some&quot;, &quot;sample&quot;, &quot;strings&quot;, &quot;to&quot;, &quot;be&quot;, &quot;sorted&quot; };

    qsort(strings, sizeof(strings)/sizeof(*strings), sizeof(*strings), mycmp);
    return 0;
}
