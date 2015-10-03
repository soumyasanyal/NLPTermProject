#include &lt;glib.h&gt;gchar *srev (gchar *s) {
    if (g_utf8_validate(s,-1,NULL)) {
        return g_utf8_strreverse (s,-1);
}   }
// main
int main (void) {
    gchar t[]=&quot;asdf&quot;;
    gchar u[]=&quot;as⃝df̅&quot;;
    printf (&quot;%s\n&quot;,srev(t));
    printf (&quot;%s\n&quot;,srev(u));
    return 0;
}
