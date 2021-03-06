#include &lt;stdio.h&gt;#include &lt;stdint.h&gt;

uint32_t msb32(uint32_t n)
{
	uint32_t b = 1;
	if (!n) return 0;

#define step(x) if (n &gt;= ((uint32_t)1) &lt;&lt; x) b &lt;&lt;= x, n &gt;&gt;= x
	step(16); step(8); step(4); step(2); step(1);
#undef step
	return b;
}

int msb32_idx(uint32_t n)
{
	int b = 0;
	if (!n) return -1;

#define step(x) if (n &gt;= ((uint32_t)1) &lt;&lt; x) b += x, n &gt;&gt;= x
	step(16); step(8); step(4); step(2); step(1);
#undef step
	return b;
}

#define lsb32(n) ( (uint32_t)(n) &amp; -(int32_t)(n) )

/* finding the *position* of the least significant bit
   rarely makes sense, so we don't put much effort in it*/
inline int lsb32_idx(uint32_t n) { return msb32_idx(lsb32(n)); }

int main()
{
	int32_t n;
	int i;

	for (i = 0, n = 1; ; i++, n *= 42) {
		printf(&quot;42**%d = %10d(x%08x): M x%08x(%2d) L x%03x(%2d)\n&quot;,
			i, n, n,
			msb32(n), msb32_idx(n),
			lsb32(n), lsb32_idx(n));

		if (n &gt;= INT32_MAX / 42) break;
	}

	return 0;
}
