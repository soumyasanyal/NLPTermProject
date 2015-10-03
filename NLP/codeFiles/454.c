#include &lt;stdio.h&gt;
int meaning_of_life() {
	return 42;
}

int __attribute__((weak)) main(int argc, char **argv) {
	printf(&quot;Main: The meaning of life is %d\n&quot;, meaning_of_life());

	return 0;
}
