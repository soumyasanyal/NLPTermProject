#include &lt;stdio.h&gt;#include &lt;string.h&gt;
/* testing */
int main()
{
   const char *t = &quot;ingirumimusnocteetconsumimurigni&quot;;
   const char *template = &quot;sequence \&quot;%s\&quot; is%s palindrome\n&quot;;
   int l = strlen(t);
   
   printf(template,
          t, palindrome(t) ? &quot;&quot; : &quot;n't&quot;);
   printf(template,
          t, palindrome_r(t, 0, l) ? &quot;&quot; : &quot;n't&quot;);
   return 0;
}
