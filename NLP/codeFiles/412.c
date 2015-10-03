#include &lt;inttypes.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdint.h&gt;

int main(int argc, char **argv)
{
    uint32_t v;
    FILE *r = fopen(&quot;/dev/urandom&quot;, &quot;r&quot;);
    if (r == NULL)
    {
	perror(&quot;/dev/urandom&quot;);
	return 1;
    }

    size_t br = fread(&amp;v, sizeof v, 1, r);
    if (br &lt; 1)
    {
	fputs(&quot;/dev/urandom: Not enough bytes\n&quot;, stderr);
	return 1;
    }

    printf(&quot;%&quot; PRIu32 &quot;\n&quot;, v);
    fclose(r);
    return 0;
}
