#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;

void upper_case(char *src)
{
        while (*src != '\0') {
                if (islower(*src)) *src &amp;= ~0x20;
                src++;
        }
}

char* encipher(char *src, char *key, int is_encode)
{
        int i, klen, slen;
        char *dest;

        dest = strdup(src);
        upper_case(dest);
        upper_case(key);

        /* strip out non-letters */
        for (i = 0, slen = 0; dest[slen] != '\0'; slen++)
                if (isupper(dest[slen]))
                        dest[i++] = dest[slen];

        dest[slen = i] = '\0'; /* null pad it, make it safe to use */

        klen = strlen(key);
        for (i = 0; i &lt; slen; i++) {
                if (!isupper(dest[i])) continue;
                dest[i] = 'A' + (is_encode
                                ? dest[i] - 'A' + key[i % klen] - 'A'
                                : dest[i] - key[i % klen] + 26) % 26;
        }

        return dest;
}

int main()
{
        char *str = &quot;Beware the Jabberwock, my son! The jaws that bite, &quot;
                    &quot;the claws that catch!&quot;;
        char *cod, *dec;
        char key[] = &quot;VIGENERECIPHER&quot;;

        printf(&quot;Text: %s\n&quot;, str);
        printf(&quot;key:  %s\n&quot;, key);

        cod = encipher(str, key, 1); printf(&quot;Code: %s\n&quot;, cod);
        dec = encipher(cod, key, 0); printf(&quot;Back: %s\n&quot;, dec);

        /* free(dec); free(cod); */ /* nah */
        return 0;
}
