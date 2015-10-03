/* rotate x to the right by s bits */unsigned int rotr(unsigned int x, unsigned int s)
{
	return (x &gt;&gt; s) | (x &lt;&lt; 32 - s);
}
