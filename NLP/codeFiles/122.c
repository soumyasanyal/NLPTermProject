#include &lt;sys/types.h&gt;#include &lt;sys/socket.h&gt;
#include &lt;netdb.h&gt;		/* getaddrinfo, getnameinfo */
#include &lt;stdio.h&gt;		/* fprintf, printf */
#include &lt;stdlib.h&gt;		/* exit */
#include &lt;string.h&gt;		/* memset */

int
main()
{
	struct addrinfo hints, *res, *res0;
	int error;
	char host[NI_MAXHOST];

	/*
	 * Request only one socket type from getaddrinfo(). Else we
	 * would get both SOCK_DGRAM and SOCK_STREAM, and print two
	 * copies of each numeric address.
	 */
	memset(&amp;hints, 0, sizeof hints);
	hints.ai_family = PF_UNSPEC;     /* IPv4, IPv6, or anything */
	hints.ai_socktype = SOCK_DGRAM;  /* Dummy socket type */

	/*
	 * Use getaddrinfo() to resolve &quot;www.kame.net&quot; and allocate
	 * a linked list of addresses.
	 */
	error = getaddrinfo(&quot;www.kame.net&quot;, NULL, &amp;hints, &amp;res0);
	if (error) {
		fprintf(stderr, &quot;%s\n&quot;, gai_strerror(error));
		exit(1);
	}

	/* Iterate the linked list. */
	for (res = res0; res; res = res-&gt;ai_next) {
		/*
		 * Use getnameinfo() to convert res-&gt;ai_addr to a
		 * printable string.
		 *
		 * NI_NUMERICHOST means to present the numeric address
		 * without doing reverse DNS to get a domain name.
		 */
		error = getnameinfo(res-&gt;ai_addr, res-&gt;ai_addrlen,
		    host, sizeof host, NULL, 0, NI_NUMERICHOST);

		if (error) {
			fprintf(stderr, &quot;%s\n&quot;, gai_strerror(error));
		} else {
			/* Print the numeric address. */
			printf(&quot;%s\n&quot;, host);
		}
	}

	/* Free the linked list. */
	freeaddrinfo(res0);

	return 0;
}
