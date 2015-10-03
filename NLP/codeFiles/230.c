#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/types.h&gt; 
#include &lt;sys/socket.h&gt;
#include &lt;netinet/in.h&gt;
#include &lt;netdb.h&gt;
#include &lt;arpa/inet.h&gt;
#include &lt;err.h&gt;

char response[] = &quot;HTTP/1.1 200 OK\r\n&quot;
&quot;Content-Type: text/html; charset=UTF-8\r\n\r\n&quot;
&quot;&lt;doctype !html&gt;&lt;html&gt;&lt;head&gt;&lt;title&gt;Bye-bye baby bye-bye&lt;/title&gt;&quot;
&quot;&lt;style&gt;body { background-color: #111 }&quot;
&quot;h1 { font-size:4cm; text-align: center; color: black;&quot;
&quot; text-shadow: 0 0 2mm red}&lt;/style&gt;&lt;/head&gt;&quot;
&quot;&lt;body&gt;&lt;h1&gt;Goodbye, world!&lt;/h1&gt;&lt;/body&gt;&lt;/html&gt;\r\n&quot;;

int main()
{
	int one = 1, client_fd;
	struct sockaddr_in svr_addr, cli_addr;
	socklen_t sin_len = sizeof(cli_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock &lt; 0)
		err(1, &quot;can't open socket&quot;);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &amp;one, sizeof(int));

	int port = 8080;
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *) &amp;svr_addr, sizeof(svr_addr)) == -1) {
		close(sock);
		err(1, &quot;Can't bind&quot;);
	}

	listen(sock, 5);
	while (1) {
		client_fd = accept(sock, (struct sockaddr *) &amp;cli_addr, &amp;sin_len);
		printf(&quot;got connection\n&quot;);

		if (client_fd == -1) {
			perror(&quot;Can't accept&quot;);
			continue;
		}

		write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
		close(client_fd);
	}
}
