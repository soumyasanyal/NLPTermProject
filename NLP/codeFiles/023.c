#include &lt;gmp.h&gt;#include &lt;stdio.h&gt;
#include &lt;string.h&gt;

int main()
{
	mpz_t a;
	mpz_init_set_ui(a, 5);
	mpz_pow_ui(a, a, 1 &lt;&lt; 18); /* 2**18 == 4**9 */

	int len = mpz_sizeinbase(a, 10);
	printf(&quot;GMP says size is: %d\n&quot;, len);

	/* because GMP may report size 1 too big; see doc */
	char *s = mpz_get_str(0, 10, a);
	printf(&quot;size really is %d\n&quot;, len = strlen(s));
	printf(&quot;Digits: %.20s...%s\n&quot;, s, s + len - 20);

	// free(s); /* we could, but we won't. we are exiting anyway */
	return 0;
}
