#include &lt;stdio.h&gt;	/* printf */#include &lt;windows.h&gt;
#include &lt;wincrypt.h&gt;	/* CryptAcquireContext, CryptGenRandom */

int
main()
{
	HCRYPTPROV p;
	ULONG i;

	if (CryptAcquireContext(&amp;p, NULL, NULL,
	    PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == FALSE) {
		fputs(&quot;CryptAcquireContext failed.\n&quot;, stderr);
		return 1;
	}
	if (CryptGenRandom(p, sizeof i, (BYTE *)&amp;i) == FALSE) {
		fputs(&quot;CryptGenRandom failed.\n&quot;, stderr);
		return 1;
	}
	printf(&quot;%lu\n&quot;, i);
	CryptReleaseContext(p, 0);
	return 0;
}
