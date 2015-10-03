#include&lt;stdio.h&gt;#include&lt;stdlib.h&gt;
#include&lt;ctype.h&gt;

#define MAXLINE 1024

char *rot13(char *s)
{
        char *p=s;
        int upper;

        while(*p) {
                upper=toupper(*p);
                if(upper&gt;='A' &amp;&amp; upper&lt;='M') *p+=13;
                else if(upper&gt;='N' &amp;&amp; upper&lt;='Z') *p-=13;
                ++p;
        }
        return s;
}

void rot13file(FILE *fp)
{
        static char line[MAXLINE];
        while(fgets(line, MAXLINE, fp)&gt;0) fputs(rot13(line), stdout);
}

int main(int argc, char *argv[])
{
        int n;
        FILE *fp;

        if(argc&gt;1) {
                for(n=1; n&lt;argc; ++n) {
                        if(!(fp=fopen(argv[n], &quot;r&quot;))) {
                                fprintf(stderr, &quot;ERROR: Couldn\'t read %s\n&quot;, argv[n]);
                                exit(EXIT_FAILURE);
                        }
                        rot13file(fp);
                        fclose(fp);
                }
        } else rot13file(stdin);

        return EXIT_SUCCESS;
}
