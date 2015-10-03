#include &lt;stdio.h&gt;#include &lt;unistd.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;dlfcn.h&gt;
#include &lt;sys/wait.h&gt;
#include &lt;err.h&gt;

typedef int (*intfunc)(int);
typedef void (*pfunc)(int*, int);

pfunc partial(intfunc fin)
{
	pfunc f;
	static int idx = 0;
	char cc[256], lib[256];
	FILE *fp;
	sprintf(lib, &quot;/tmp/stuff%d.so&quot;, ++idx);
	sprintf(cc, &quot;cc -pipe -x c -shared -o %s -&quot;, lib);

	fp = popen(cc, &quot;w&quot;);
	fprintf(fp, &quot;#define t typedef\xat int _i,*i;t _i(*__)(_i);__ p =(__)%p;&quot;
		&quot;void _(i _1, _i l){while(--l&gt;-1)l[_1]=p(l[_1]);}&quot;, fin);
	fclose(fp);

	*(void **)(&amp;f) = dlsym(dlopen(lib, RTLD_LAZY), &quot;_&quot;);
	unlink(lib);
	return f;
}

int square(int a)
{
	return a * a;
}

int dbl(int a)
{
	return a + a;
}

int main()
{
	int x[] = { 1, 2, 3, 4 };
	int y[] = { 1, 2, 3, 4 };
	int i;

	pfunc f = partial(square);
	pfunc g = partial(dbl);

	printf(&quot;partial square:\n&quot;);
	f(x, 4);
	for (i = 0; i &lt; 4; i++) printf(&quot;%d\n&quot;, x[i]);

	printf(&quot;partial double:\n&quot;);
	g(y, 4);
	for (i = 0; i &lt; 4; i++) printf(&quot;%d\n&quot;, y[i]);

	return 0;
}
