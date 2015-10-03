#include &lt;sys/types.h&gt; #include &lt;sys/stat.h&gt;
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;

/* Check for regular file. */
int check_reg(const char *path) {
	struct stat sb;
	return stat(path, &amp;sb) == 0 &amp;&amp; S_ISREG(sb.st_mode);
}

/* Check for directory. */
int check_dir(const char *path) {
	struct stat sb;
	return stat(path, &amp;sb) == 0 &amp;&amp; S_ISDIR(sb.st_mode);
}

int main() {
	printf(&quot;input.txt is a regular file? %s\n&quot;,
	    check_reg(&quot;input.txt&quot;) ? &quot;yes&quot; : &quot;no&quot;);
	printf(&quot;docs is a directory? %s\n&quot;,
	    check_dir(&quot;docs&quot;) ? &quot;yes&quot; : &quot;no&quot;);
	printf(&quot;/input.txt is a regular file? %s\n&quot;,
	    check_reg(&quot;/input.txt&quot;) ? &quot;yes&quot; : &quot;no&quot;);
	printf(&quot;/docs is a directory? %s\n&quot;,
	    check_dir(&quot;/docs&quot;) ? &quot;yes&quot; : &quot;no&quot;);
	return 0;
}
