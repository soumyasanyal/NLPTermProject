/* 5432.c */
#include &lt;openssl/bn.h&gt;		/* BN_*() */
#include &lt;openssl/err.h&gt;	/* ERR_*() */
#include &lt;stdlib.h&gt;		/* exit() */
#include &lt;stdio.h&gt;		/* fprintf() */
#include &lt;string.h&gt;		/* strlen() */

void
fail(const char *message)
{
	fprintf(stderr, &quot;%s: error 0x%08lx\n&quot;, ERR_get_error());
	exit(1);
}

int
main()
{
	BIGNUM two, three, four, five;
	BIGNUM answer;
	BN_CTX *context;
	size_t length;
	char *string;

	context = BN_CTX_new();
	if (context == NULL)
		fail(&quot;BN_CTX_new&quot;);

	/* answer = 5 ** 4 ** 3 ** 2 */
	BN_init(&amp;two);
	BN_init(&amp;three);
	BN_init(&amp;four);
	BN_init(&amp;five);
	if (BN_set_word(&amp;two, 2) == 0 ||
	    BN_set_word(&amp;three, 3) == 0 ||
	    BN_set_word(&amp;four, 4) == 0 ||
	    BN_set_word(&amp;five, 5) == 0)
		fail(&quot;BN_set_word&quot;);
	BN_init(&amp;answer);
	if (BN_exp(&amp;answer, &amp;three, &amp;two, context) == 0 ||
	    BN_exp(&amp;answer, &amp;four, &amp;answer, context) == 0 ||
	    BN_exp(&amp;answer, &amp;five, &amp;answer, context) == 0)
		fail(&quot;BN_exp&quot;);

	/* string = decimal answer */
	string = BN_bn2dec(&amp;answer);
	if (string == NULL)
		fail(&quot;BN_bn2dec&quot;);

	length = strlen(string);
	printf(&quot; First 20 digits: %.20s\n&quot;, string);
	if (length &gt;= 20)
		printf(&quot;  Last 20 digits: %.20s\n&quot;, string + length - 20);
	printf(&quot;Number of digits: %zd\n&quot;, length);

	OPENSSL_free(string);
	BN_free(&amp;answer);
	BN_free(&amp;five);
	BN_free(&amp;four);
	BN_free(&amp;three);
	BN_free(&amp;two);
	BN_CTX_free(context);

	return 0;
}
