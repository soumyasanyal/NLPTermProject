#include &lt;stdio.h&gt;#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/mman.h&gt;
#include &lt;errno.h&gt;
#include &lt;err.h&gt;

int read_lines(char * fname, int (*call_back)(char*, char*))
{
        int fd = open(fname, O_RDONLY);
        struct stat fs;
        char *buf, *buf_end;
        char *begin, *end, c;

        if (fd == -1) {
                err(1, &quot;open: %s&quot;, fname);
                return 0;
        }

        if (fstat(fd, &amp;fs) == -1) {
                err(1, &quot;stat: %s&quot;, fname);
                return 0;
        }

        /* fs.st_size could have been 0 actually */
        buf = mmap(0, fs.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (buf == (void*) -1) {
                err(1, &quot;mmap: %s&quot;, fname);
                close(fd);
                return 0;
        }

        buf_end = buf + fs.st_size;

        begin = end = buf;
        while (1) {
                if (! (*end == '\r' || *end == '\n')) {
                        if (++end &lt; buf_end) continue;
                } else if (1 + end &lt; buf_end) {
                        /* see if we got &quot;\r\n&quot; or &quot;\n\r&quot; here */
                        c = *(1 + end);
                        if ( (c == '\r' || c == '\n') &amp;&amp; c != *end)
                                ++end;
                }

                /* call the call back and check error indication. Announce
                   error here, because we didn't tell call_back the file name */
                if (! call_back(begin, end)) {
                        err(1, &quot;[callback] %s&quot;, fname);
                        break;
                }

                if ((begin = ++end) &gt;= buf_end)
                        break;
        }

        munmap(buf, fs.st_size);
        close(fd);
        return 1;
}

int print_line(char* begin, char* end)
{
        if (write(fileno(stdout), begin, end - begin + 1) == -1) {
                return 0;
        }
        return 1;
}

int main()
{
        return read_lines(&quot;test.ps&quot;, print_line) ? 0 : 1;
}

