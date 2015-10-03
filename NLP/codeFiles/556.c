#include&lt;stdio.h&gt;
typedef (void *callbackfunc)(const char *);

void doprint(const char *s) {
	printf(&quot;%s.&quot;, s);
}

void tokenize(char *s, char delim, callbackfunc *cb) {
	char *olds = s;
	char olddelim = delim;
	while(olddelim &amp;&amp; *s) {
		while(*s &amp;&amp; (delim != *s)) s++;
		*s ^= olddelim = *s; // olddelim = *s; *s = 0;
		cb(olds);
		*s++ ^= olddelim; // *s = olddelim; s++;
		olds = s;
	}
}

int main(void)
{
        char array[] = &quot;Hello,How,Are,You,Today&quot;;
	tokenize(array, ',', doprint);
	return 0;
}
