#include &lt;stdio.h&gt;
int digits[26] = { 0, 0, 100, 500, 0, 0, 0, 0, 1, 1, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 10, 0, 0 };

/* assuming ASCII, do upper case and get index in alphabet. could also be
        inline int VALUE(char x) { return digits [ (~0x20 &amp; x) - 'A' ]; }
   if you think macros are evil */
#define VALUE(x) digits[(~0x20 &amp; (x)) - 'A']

int decode(char * roman)
{
        char *bigger;
        int current;
        int arabic = 0;
        while (*roman != '\0') {
                current = VALUE(*roman);
                /*      if (!current) return -1;
                        note: -1 can be used as error code; Romans didn't even have zero
                */
                bigger = roman;

                /* look for a larger digit, like IV or XM */
                while (VALUE(*bigger) &lt;= current &amp;&amp; *++bigger != '\0');

                if (*bigger == '\0')
                        arabic += current;
                else {
                        arabic += VALUE(*bigger);
                        while (roman &lt; bigger)
                                arabic -= VALUE(* (roman++) );
                }

                roman ++;
        }
        return arabic;
}

int main()
{
        char * romans[] = { &quot;MCmxC&quot;, &quot;MMVIII&quot;, &quot;MDClXVI&quot;, &quot;MCXLUJ&quot; };
        int i;

        for (i = 0; i &lt; 4; i++)
                printf(&quot;%s\t%d\n&quot;, romans[i], decode(romans[i]));

        return 0;
}
