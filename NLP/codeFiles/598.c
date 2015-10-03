#include &lt;stdio.h&gt;
void draw_yinyang(int trans, double scale)
{
	printf(&quot;&lt;use xlink:href='#y' transform='translate(%d,%d) scale(%g)'/&gt;&quot;,
		trans, trans, scale);
}

int main()
{	printf(
	&quot;&lt;?xml version='1.0' encoding='UTF-8' standalone='no'?&gt;\n&quot;
	&quot;&lt;!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 1.1//EN'\n&quot;
	&quot;	'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'&gt;\n&quot;
	&quot;&lt;svg xmlns='http://www.w3.org/2000/svg' version='1.1'\n&quot;
	&quot;	xmlns:xlink='http://www.w3.org/1999/xlink'\n&quot;
	&quot;		width='30' height='30'&gt;\n&quot;
	&quot;	&lt;defs&gt;&lt;g id='y'&gt;\n&quot;
	&quot;		&lt;circle cx='0' cy='0' r='200' stroke='black'\n&quot;
	&quot;			fill='white' stroke-width='1'/&gt;\n&quot;
	&quot;		&lt;path d='M0 -200 A 200 200 0 0 0 0 200\n&quot;
	&quot;			100 100 0 0 0 0 0 100 100 0 0 1 0 -200\n&quot;
	&quot;			z' fill='black'/&gt;\n&quot;
	&quot;		&lt;circle cx='0' cy='100' r='33' fill='white'/&gt;\n&quot;
	&quot;		&lt;circle cx='0' cy='-100' r='33' fill='black'/&gt;\n&quot;
	&quot;	&lt;/g&gt;&lt;/defs&gt;\n&quot;);
	draw_yinyang(20, .05);
	draw_yinyang(8, .02);
	printf(&quot;&lt;/svg&gt;&quot;);
	return 0;
}
