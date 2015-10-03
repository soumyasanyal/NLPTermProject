#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;sys/socket.h&gt;
#include &lt;sys/select.h&gt;
#include &lt;netinet/in.h&gt;
#include &lt;netinet/ip.h&gt;

int tsocket;
struct sockaddr_in tsockinfo;
fd_set status, current;
void ClientText(int handle, char *buf, int buf_len);

struct client
{
    char buffer[4096];
    int pos;
    char name[32];
} *connections[FD_SETSIZE];

void AddConnection(int handle)
{
    connections[handle] = malloc(sizeof(struct client));
    connections[handle]-&gt;buffer[0] = '\0';
    connections[handle]-&gt;pos = 0;
    connections[handle]-&gt;name[0] = '\0';
}

void CloseConnection(int handle)
{
    char buf[512];
    int j;

    FD_CLR(handle, &amp;status);
    
    if (connections[handle]-&gt;name[0])
    {
        sprintf(buf, &quot;* Disconnected: %s\r\n&quot;, connections[handle]-&gt;name);

        for (j = 0; j &lt; FD_SETSIZE; j++)
        {
            if (handle != j &amp;&amp; j != tsocket &amp;&amp; FD_ISSET(j, &amp;status))
            {
                if (write(j, buf, strlen(buf)) &lt; 0)
                {
                    CloseConnection(j);
                }
            }
        }
    } else
    {
        printf (&quot;-- Connection %d disconnected\n&quot;, handle);
    }
    if (connections[handle])
    {
        free(connections[handle]);
    }
    close(handle);
}

void strip(char *buf)
{
    char *x;
    
    x = strchr(buf, '\n');
    if (x) { *x='\0'; }
    x = strchr(buf, '\r');
    if (x) { *x='\0'; }
}

int RelayText(int handle)
{
    char *begin, *end;
    int ret = 0;
    begin = connections[handle]-&gt;buffer;
    if (connections[handle]-&gt;pos == 4000)
    {
        if (begin[3999] != '\n')
            begin[4000] = '\0';
        else {
            begin[4000] = '\n';
            begin[4001] = '\0';
        }
    } else {
        begin[connections[handle]-&gt;pos] = '\0';
    }
    
    end = strchr(begin, '\n');
    while (end != NULL)
    {
        char output[8000];
        output[0] = '\0';
        if (!connections[handle]-&gt;name[0])
        {
            strncpy(connections[handle]-&gt;name, begin, 31);
            connections[handle]-&gt;name[31] = '\0';
            
            strip(connections[handle]-&gt;name);
            sprintf(output, &quot;* Connected: %s\r\n&quot;, connections[handle]-&gt;name);
            ret = 1;
        } else 
        {
            sprintf(output, &quot;%s: %.*s\r\n&quot;, connections[handle]-&gt;name, 
                    end-begin, begin);
            ret = 1;
        }
        
        if (output[0])
        {
            int j;
            for (j = 0; j &lt; FD_SETSIZE; j++)
            {
                if (handle != j &amp;&amp; j != tsocket &amp;&amp; FD_ISSET(j, &amp;status))
                {
                    if (write(j, output, strlen(output)) &lt; 0)
                    {
                        CloseConnection(j);
                    }
                }
            }
        }
        begin = end+1;
        end = strchr(begin, '\n');
    }
    
    strcpy(connections[handle]-&gt;buffer, begin);
    connections[handle]-&gt;pos -= begin - connections[handle]-&gt;buffer;
    return ret;
}

void ClientText(int handle, char *buf, int buf_len)
{
    int i, j;
    if (!connections[handle])
        return;
    j = connections[handle]-&gt;pos; 
    
    for (i = 0; i &lt; buf_len; ++i, ++j)
    {
        connections[handle]-&gt;buffer[j] = buf[i];
        
        if (j == 4000)
        {
            while (RelayText(handle));
            j = connections[handle]-&gt;pos;
        }
    }
    connections[handle]-&gt;pos = j;
    
    while (RelayText(handle));
}


int ChatLoop()
{
    int i, j;
    FD_ZERO(&amp;status);

    FD_SET(tsocket, &amp;status);
    FD_SET(0, &amp;status);

    while(1)
    {
        current = status;
        if (select(FD_SETSIZE, &amp;current, NULL, NULL, NULL)==-1)
        {
            perror(&quot;Select&quot;);
            return 0;
        }
        for (i = 0; i &lt; FD_SETSIZE; ++i)
        {
            if (FD_ISSET(i, &amp;current))
            {
                if (i == tsocket)
                {
                    struct sockaddr_in cliinfo;
                    socklen_t addrlen = sizeof(cliinfo);
                    int handle;
                    handle = accept(tsocket, &amp;cliinfo, &amp;addrlen);
                    if (handle == -1)
                    {
                        perror (&quot;Couldn't accept connection&quot;);
                    } else if (handle &gt; FD_SETSIZE)
                    {
                        printf (&quot;Unable to accept new connection.\n&quot;);
                        close(handle);
                    }
                    else
                    {
                        if (write(handle, &quot;Enter name: &quot;, 12) &gt;= 0)
                        {
                            printf(&quot;-- New connection %d from %s:%hu\n&quot;,
                                handle, 
                                inet_ntoa (cliinfo.sin_addr),
                                ntohs(cliinfo.sin_port));
                            FD_SET(handle, &amp;status);

                            AddConnection(handle);
                        }
                    }
                } /* Read data, relay to others. */
                else
                {
                    char buf[512];
                    int b;

                    b = read(i, buf, 500);
                    if (b &lt;= 0)
                    {
                        CloseConnection(i);
                    }
                    else
                    {
                        ClientText(i, buf, b);
                    }
                }
            }
        }
    } /* While 1 */
}

int main (int argc, char*argv[])
{
    tsocket = socket(PF_INET, SOCK_STREAM, 0);

    tsockinfo.sin_family = AF_INET;
    tsockinfo.sin_port = htons(7070);
    if (argc &gt; 1)
    {
        tsockinfo.sin_port = htons(atoi(argv[1]));
    }
    tsockinfo.sin_addr.s_addr = htonl(INADDR_ANY);
    printf (&quot;Socket %d on port %hu\n&quot;, tsocket, ntohs(tsockinfo.sin_port));

    if (bind(tsocket, &amp;tsockinfo, sizeof(tsockinfo)) == -1)
    {
        perror(&quot;Couldn't bind socket&quot;);
        return -1;
    }

    if (listen(tsocket, 10) == -1)
    {
        perror(&quot;Couldn't listen to port&quot;);
    }

    ChatLoop();

    return 0;
}
