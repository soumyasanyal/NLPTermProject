#include &lt;stdio.h&gt;
void IntToBitString(unsigned int number)
{
    int num_bits = sizeof(unsigned int) * 8;

    bool startPrinting = false;
    for (int bit_pos=num_bits-1; bit_pos &gt;= 0; bit_pos--)
    {
        bool isBitSet = (number &amp; (1&lt;&lt;bit_pos)) != 0;

        if (!startPrinting &amp;&amp; isBitSet)
            startPrinting = true;

        if (startPrinting || bit_pos==0)
            printf(&quot;%s&quot;, isBitSet ? &quot;1&quot;:&quot;0&quot;);
    }

    printf(&quot;\r\n&quot;);
}

int main()
{
    IntToBitString(0);
    IntToBitString(5);
    IntToBitString(50);
    IntToBitString(9000);

    return 0;
}
