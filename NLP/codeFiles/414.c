#include &lt;inttypes.h&gt;#include &lt;stdio.h&gt;

#include &lt;openssl/err.h&gt;
#include &lt;openssl/rand.h&gt;

int
main()
{
	uint32_t v;

	if (RAND_bytes((unsigned char *)&amp;v, sizeof v) == 0) {
		ERR_print_errors_fp(stderr);
		return 1;
	}
	printf(&quot;%&quot; PRIu32 &quot;\n&quot;, v);
	return 0;
}
