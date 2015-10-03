#include &lt;stdio.h&gt;#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;

char *ca = &quot;/*&quot;, *cb = &quot;*/&quot;;
int al = 2, bl = 2;

char *loadfile(char *s) {
    FILE *f = fopen(s, &quot;rb&quot;);
    int l;

    if (f != NULL) {
	fseek(f, 0, SEEK_END);
	l = ftell(f);
	s = malloc(l+1);
	rewind(f);
	if (s)
	    fread(s, 1, l, f);
	fclose(f);
    }
    return s;
}

void stripcomments(char *s) {
    char *a, *b;
    int len = strlen(s) + 1;

    while ((a = strstr(s, ca)) != NULL) {
	b = strstr(a+al, cb);
	if (b == NULL)
	    break;
	b += bl;
	memmove(a, b, len-(b-a));
    }
}

int main(int argc, char **argv) {
    char *s = &quot;input.txt&quot;;

    if (argc &gt;= 2)
	s = argv[1];
    s = loadfile(s);
    if (argc == 4) {
	al = strlen(ca = argv[2]);
	bl = strlen(cb = argv[3]);
    }
    stripcomments(s);
    puts(s);
    free(s);
    return 0;
}
