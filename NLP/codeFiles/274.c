/* declare array */int frequency[26];
int ch;
FILE* txt_file = fopen (&quot;a_text_file.txt&quot;, &quot;rt&quot;);

/* init the freq table: */
for (ch = 0; ch &lt; 26; ch++)
    frequency[ch] = 0;

while (1) {
    ch = fgetc(txt_file);
    if (ch == EOF) break; /* end of file or read error.  EOF is typically -1 */

    /* assuming ASCII; &quot;letters&quot; means &quot;a to z&quot; */
    if ('a' &lt;= ch &amp;&amp; ch &lt;= 'z')      /* lower case */
        frequency[ch-'a']++;
    else if ('A' &lt;= ch &amp;&amp; ch &lt;= 'Z') /* upper case */
        frequency[ch-'A']++;
}
