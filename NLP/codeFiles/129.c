#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;errno.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/socket.h&gt;
#include &lt;netdb.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/wait.h&gt;
#include &lt;signal.h&gt;

#define MAX_ENQUEUED 20
#define BUF_LEN 256
#define PORT_STR &quot;12321&quot;

/* ------------------------------------------------------------ */
/* How to clean up after dead child processes                   */
/* ------------------------------------------------------------ */

void wait_for_zombie(int s)
{
    while(waitpid(-1, NULL, WNOHANG) &gt; 0) ;
}

/* ------------------------------------------------------------ */
/* Core of implementation of a child process                    */
/* ------------------------------------------------------------ */

void echo_lines(int csock)
{
    char buf[BUF_LEN];
    int r;

    while( (r = read(csock, buf, BUF_LEN)) &gt; 0 ) {
        (void)write(csock, buf, r);
    }
    exit(EXIT_SUCCESS);
}

/* ------------------------------------------------------------ */
/* Core of implementation of the parent process                 */
/* ------------------------------------------------------------ */

void take_connections_forever(int ssock)
{
    for(;;) {
        struct sockaddr addr;
        socklen_t addr_size = sizeof(addr);
        int csock;

        /* Block until we take one connection to the server socket */
        csock = accept(ssock, &amp;addr, &amp;addr_size);

        /* If it was a successful connection, spawn a worker process to service it */
        if ( csock == -1 ) {
            perror(&quot;accept&quot;);
        } else if ( fork() == 0 ) {
            close(ssock);
            echo_lines(csock);
        } else {
            close(csock);
        }
    }
}

/* ------------------------------------------------------------ */
/* The server process's one-off setup code                      */
/* ------------------------------------------------------------ */

int main()
{
    struct addrinfo hints, *res;
    struct sigaction sa;
    int sock;

    /* Look up the address to bind to */
    memset(&amp;hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ( getaddrinfo(NULL, PORT_STR, &amp;hints, &amp;res) != 0 ) {
        perror(&quot;getaddrinfo&quot;);
        exit(EXIT_FAILURE);
    }

    /* Make a socket */
    if ( (sock = socket(res-&gt;ai_family, res-&gt;ai_socktype, res-&gt;ai_protocol)) == -1 ) {
        perror(&quot;socket&quot;);
        exit(EXIT_FAILURE);
    }

    /* Arrange to clean up child processes (the workers) */
    sa.sa_handler = wait_for_zombie;
    sigemptyset(&amp;sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if ( sigaction(SIGCHLD, &amp;sa, NULL) == -1 ) {
        perror(&quot;sigaction&quot;);
        exit(EXIT_FAILURE);
    }

    /* Associate the socket with its address */
    if ( bind(sock, res-&gt;ai_addr, res-&gt;ai_addrlen) != 0 ) {
        perror(&quot;bind&quot;);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    /* State that we've opened a server socket and are listening for connections */
    if ( listen(sock, MAX_ENQUEUED) != 0 ) {
        perror(&quot;listen&quot;);
        exit(EXIT_FAILURE);
    }

    /* Serve the listening socket until killed */
    take_connections_forever(sock);
    return EXIT_SUCCESS;
}
