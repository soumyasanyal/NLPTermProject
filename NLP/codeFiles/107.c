#include &lt;stdio.h&gt;
char input[] = 
	&quot;Character,Speech\n&quot;
	&quot;The multitude,The messiah! Show us the messiah!\n&quot;
	&quot;Brians mother,&lt;angry&gt;Now you listen here! He's not the messiah; &quot;
		&quot;he's a very naughty boy! Now go away!&lt;/angry&gt;\n&quot;
	&quot;The multitude,Who are you?\n&quot;
	&quot;Brians mother,I'm his mother; that's who!\n&quot;
	&quot;The multitude,Behold his mother! Behold his mother!&quot;;

int main()
{
	char *s = input;
	printf(&quot;&lt;table&gt;\n&lt;tr&gt;&lt;td&gt;&quot;);
	for (s = input; *s; s++) {
		switch(*s) {
		case '\n': printf(&quot;&lt;/td&gt;&lt;/tr&gt;\n&lt;tr&gt;&lt;td&gt;&quot;); break;
		case ',':  printf(&quot;&lt;/td&gt;&lt;td&gt;&quot;); break;
		case '&lt;':  printf(&quot;&amp;lt;&quot;); break;
		case '&gt;':  printf(&quot;&amp;gt;&quot;); break;
		case '&amp;':  printf(&quot;&amp;amp;&quot;); break;
		default:   putchar(*s);
		}
	}
	puts(&quot;&lt;/td&gt;&lt;/tr&gt;\n&lt;/table&gt;&quot;);

	return 0;
}
