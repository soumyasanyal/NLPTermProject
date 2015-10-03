#include &lt;stdio.h&gt;#include &lt;stdint.h&gt;
typedef uint64_t ulong;

int kaprekar(ulong n, int base)
{
	ulong nn = n * n, r, tens = 1;

	if ((nn - n) % (base - 1)) return 0;

	while (tens &lt; n) tens *= base;
	if (n == tens) return 1 == n;

	while ((r = nn % tens) &lt; n) {
		if (nn / tens + r == n) return tens;
		tens *= base;
	}

	return 0;
}

void print_num(ulong n, int base)
{
	ulong q, div = base;

	while (div &lt; n) div *= base;
	while (n &amp;&amp; (div /= base)) {
		q = n / div;
		if (q &lt; 10)     putchar(q + '0');
		else            putchar(q + 'a' - 10);
		n -= q * div;
	}
}

int main()
{
	ulong i, tens;
	int cnt = 0;
	int base = 10;

	printf(&quot;base 10:\n&quot;);
	for (i = 1; i &lt; 1000000; i++)
		if (kaprekar(i, base))
			printf(&quot;%3d: %llu\n&quot;, ++cnt, i);

	base = 17;
	printf(&quot;\nbase %d:\n  1: 1\n&quot;, base);
	for (i = 2, cnt = 1; i &lt; 1000000; i++)
		if ((tens = kaprekar(i, base))) {
			printf(&quot;%3d: %llu&quot;, ++cnt, i);
			printf(&quot; \t&quot;); print_num(i, base);
			printf(&quot;\t&quot;);  print_num(i * i, base);
			printf(&quot;\t&quot;);  print_num(i * i / tens, base);
			printf(&quot; + &quot;); print_num(i * i % tens, base);
			printf(&quot;\n&quot;);
		}

	return 0;
}
