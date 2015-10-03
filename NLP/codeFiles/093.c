#include &lt;stdlib.h&gt;	/* exit(), free() */#include &lt;stdio.h&gt;	/* fputs(), perror(), printf() */
#include &lt;string.h&gt;

int
main()
{
	size_t len;
	char src[] = &quot;Hello&quot;;
	char dst1[80], dst2[80];
	char *dst3, *ref;

	/*
	 * Option 1. Use strcpy() from &lt;string.h&gt;.
	 *
	 * DANGER! strcpy() can overflow the destination buffer.
	 * strcpy() is only safe is the source string is shorter than
	 * the destination buffer. We know that &quot;Hello&quot; (6 characters
	 * with the final '\0') easily fits in dst1 (80 characters).
	 */
	strcpy(dst1, src);

	/*
	 * Option 2. Use strlen() and memcpy() from &lt;string.h&gt;, to copy
	 * strlen(src) + 1 bytes including the final '\0'.
	 */
	len = strlen(src);
	if (len &gt;= sizeof dst2) {
		fputs(&quot;The buffer is too small!\n&quot;, stderr);
		exit(1);
	}
	memcpy(dst2, src, len + 1);

	/*
	 * Option 3. Use strdup() from &lt;string.h&gt;, to allocate a copy.
	 */
	dst3 = strdup(src);
	if (dst3 == NULL) {
		/* Failed to allocate memory! */
		perror(&quot;strdup&quot;);
		exit(1);
	}

	/* Create another reference to the source string. */
	ref = src;

	/* Modify the source string, not its copies. */
	memset(src, '-', 5);

	printf(&quot; src: %s\n&quot;, src);   /*  src: ----- */
	printf(&quot;dst1: %s\n&quot;, dst1);  /* dst1: Hello */
	printf(&quot;dst2: %s\n&quot;, dst2);  /* dst2: Hello */
	printf(&quot;dst3: %s\n&quot;, dst3);  /* dst3: Hello */
	printf(&quot; ref: %s\n&quot;, ref);   /*  ref: ----- */

	/* Free memory from strdup(). */
	free(dst3);

	return 0;
}
