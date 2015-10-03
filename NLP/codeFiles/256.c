#include &lt;openssl/bn.h&gt;		/* BN_*() */#include &lt;openssl/err.h&gt;	/* ERR_*() */
#include &lt;stdio.h&gt;		/* fprintf(), puts() */

void
fail(const char *message)
{
	fprintf(stderr, &quot;%s: error 0x%08lx\n&quot;, ERR_get_error());
	exit(1);
}

int
main()
{
	BIGNUM i;
	char *s;

	BN_init(&amp;i);
	for (;;) {
		if (BN_add_word(&amp;i, 1) == 0)
			fail(&quot;BN_add_word&quot;);
		s = BN_bn2dec(&amp;i);
		if (s == NULL)
			fail(&quot;BN_bn2dec&quot;);
		puts(s);
		OPENSSL_free(s);
	}
	/* NOTREACHED */
}
