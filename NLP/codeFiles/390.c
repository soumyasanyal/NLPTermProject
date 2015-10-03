#include &lt;inttypes.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;assert.h&gt;

typedef uint32_t pint;
typedef uint64_t xint;
typedef unsigned int uint;
#define PRIuPINT PRIu32		/* printf macro for pint */
#define PRIuXINT PRIu64		/* printf macro for xint */
#define MAX_FACTORS 63		/* because 2^64 is too large for xint */

uint8_t *pbits;

#define MAX_PRIME (~(pint)0)
#define MAX_PRIME_SQ 65535U
#define PBITS (MAX_PRIME / 30 + 1)

pint next_prime(pint);
int is_prime(xint);
void sieve(pint);

uint8_t bit_pos[30] = {
	0, 1&lt;&lt;0, 0, 0, 0,    0,
	0, 1&lt;&lt;1, 0, 0, 0, 1&lt;&lt;2,
	0, 1&lt;&lt;3, 0, 0, 0, 1&lt;&lt;4,
	0, 1&lt;&lt;5, 0, 0, 0, 1&lt;&lt;6,
	0,    0, 0, 0, 0, 1&lt;&lt;7,
};

uint8_t rem_num[] = { 1, 7, 11, 13, 17, 19, 23, 29 };

void init_primes()
{
	FILE *fp;
	pint s, tgt = 4;

	if (!(pbits = malloc(PBITS))) {
		perror(&quot;malloc&quot;);
		exit(1);
	}

	if ((fp = fopen(&quot;primebits&quot;, &quot;r&quot;))) {
		fread(pbits, 1, PBITS, fp);
		fclose(fp);
		return;
	}

	memset(pbits, 255, PBITS);
	for (s = 7; s &lt;= MAX_PRIME_SQ; s = next_prime(s)) {
		if (s &gt; tgt) {
			tgt *= 2;
			fprintf(stderr, &quot;sieve %&quot;PRIuPINT&quot;\n&quot;, s);
		}
		sieve(s);
	}
	fp = fopen(&quot;primebits&quot;, &quot;w&quot;);
	fwrite(pbits, 1, PBITS, fp);
	fclose(fp);
}

int is_prime(xint x)
{
	pint p;
	if (x &gt; 5) {
		if (x &lt; MAX_PRIME)
			return pbits[x/30] &amp; bit_pos[x % 30];

		for (p = 2; p &amp;&amp; (xint)p * p &lt;= x; p = next_prime(p))
			if (x % p == 0) return 0;

		return 1;
	}
	return x == 2 || x == 3 || x == 5;
}

void sieve(pint p)
{
	unsigned char b[8];
	off_t ofs[8];
	int i, q;

	for (i = 0; i &lt; 8; i++) {
		q = rem_num[i] * p;
		b[i] = ~bit_pos[q % 30];
		ofs[i] = q / 30;
	}

	for (q = ofs[1], i = 7; i; i--)
		ofs[i] -= ofs[i-1];

	for (ofs[0] = p, i = 1; i &lt; 8; i++)
		ofs[0] -= ofs[i];

	for (i = 1; q &lt; PBITS; q += ofs[i = (i + 1) &amp; 7])
		pbits[q] &amp;= b[i];
}

pint next_prime(pint p)
{
	off_t addr;
	uint8_t bits, rem;

	if (p &gt; 5) {
		addr = p / 30;
		bits = bit_pos[ p % 30 ] &lt;&lt; 1;
		for (rem = 0; (1 &lt;&lt; rem) &lt; bits; rem++);
		while (pbits[addr] &lt; bits || !bits) {
			if (++addr &gt;= PBITS) return 0;
			bits = 1;
			rem = 0;
		}
		if (addr &gt;= PBITS) return 0;
		while (!(pbits[addr] &amp; bits)) {
			rem++;
			bits &lt;&lt;= 1;
		}
		return p = addr * 30 + rem_num[rem];
	}

	switch(p) {
		case 2: return 3;
		case 3: return 5;
		case 5: return 7;
	}
	return 2;
}

int decompose(xint n, xint *f)
{
	pint p = 0;
	int i = 0;

	/* check small primes: not strictly necessary */
	if (n &lt;= MAX_PRIME &amp;&amp; is_prime(n)) {
		f[0] = n;
		return 1;
	}

	while (n &gt;= (xint)p * p) {
		if (!(p = next_prime(p))) break;
		while (n % p == 0) {
			n /= p;
			f[i++] = p;
		}
	}
	if (n &gt; 1) f[i++] = n;
	return i;
}

int main()
{
	int i, len;
	pint p = 0;
	xint f[MAX_FACTORS], po;

	init_primes();

	for (p = 1; p &lt; 64; p++) {
		po = (1LLU &lt;&lt; p) - 1;
		printf(&quot;2^%&quot;PRIuPINT&quot; - 1 = %&quot;PRIuXINT, p, po);
		fflush(stdout);
		if ((len = decompose(po, f)) &gt; 1)
			for (i = 0; i &lt; len; i++)
				printf(&quot; %c %&quot;PRIuXINT, i?'x':'=', f[i]);
		putchar('\n');
	}

	return 0;
}
