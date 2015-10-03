#include &lt;stdio.h&gt;#include &lt;stdint.h&gt;

void to_seq(uint64_t x, uint8_t *out)
{
	int i, j;
	for (i = 9; i &gt; 0; i--) {
		if (x &amp; 127ULL &lt;&lt; i * 7) break;
	}
	for (j = 0; j &lt;= i; j++)
		out[j] = ((x &gt;&gt; ((i - j) * 7)) &amp; 127) | 128;

	out[i] ^= 128;
}

uint64_t from_seq(uint8_t *in)
{
	uint64_t r = 0;

	do {
		r = (r &lt;&lt; 7) | (uint64_t)(*in &amp; 127);
	} while (*in++ &amp; 128);

	return r;
}

int main()
{
	uint8_t s[10];
	uint64_t x[] = { 0x7f, 0x4000, 0, 0x3ffffe, 0x1fffff, 0x200000, 0x3311a1234df31413ULL};

	int i, j;
	for (j = 0; j &lt; sizeof(x)/8; j++) {
		to_seq(x[j], s);
		printf(&quot;seq from %llx: [ &quot;, x[j]);

		i = 0;
		do { printf(&quot;%02x &quot;, s[i]); } while ((s[i++] &amp; 128));
		printf(&quot;] back: %llx\n&quot;, from_seq(s));
	}

	return 0;
}
