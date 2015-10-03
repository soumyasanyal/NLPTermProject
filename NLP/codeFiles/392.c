#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdint.h&gt;
 
typedef uint32_t pint;
typedef uint64_t xint;
typedef unsigned int uint;
 
int is_prime(xint);
 
inline int next_prime(pint p)
{
	if (p == 2) return 3;
	for (p += 2; p &gt; 1 &amp;&amp; !is_prime(p); p += 2);
	if (p == 1) return 0;
	return p;
}
 
int is_prime(xint n)
{
#	define NCACHE 256
#	define S (sizeof(uint) * 2)
	static uint cache[NCACHE] = {0};
 
	pint p = 2;
	int ofs, bit = -1;
 
	if (n &lt; NCACHE * S) {
		ofs = n / S;
		bit = 1 &lt;&lt; ((n &amp; (S - 1)) &gt;&gt; 1);
		if (cache[ofs] &amp; bit) return 1;
	}
 
	do {
		if (n % p == 0) return 0;
		if (p * p &gt; n) break;
	} while ((p = next_prime(p)));
 
	if (bit != -1) cache[ofs] |= bit;
	return 1;
}
 
int decompose(xint n, pint *out)
{
	int i = 0;
	pint p = 2;
	while (n &gt; p * p) {
		while (n % p == 0) {
			out[i++] = p;
			n /= p;
		}
		if (!(p = next_prime(p))) break;
	}
	if (n &gt; 1) out[i++] = n;
	return i;
}
 
int main()
{
	int i, j, len;
	xint z;
	pint out[100];
	for (i = 2; i &lt; 64; i = next_prime(i)) {
		z = (1ULL &lt;&lt; i) - 1;
		printf(&quot;2^%d - 1 = %llu = &quot;, i, z);
		fflush(stdout);
		len = decompose(z, out);
		for (j = 0; j &lt; len; j++)
			printf(&quot;%u%s&quot;, out[j], j &lt; len - 1 ? &quot; x &quot; : &quot;\n&quot;);
	}
 
	return 0;
}
