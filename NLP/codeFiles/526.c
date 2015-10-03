#include &lt;stdio.h&gt;#include &lt;wchar.h&gt;

int main(void) 
{
   wchar_t *s = L&quot;\x304A\x306F\x3088\x3046&quot;; /* Japanese hiragana ohayou */
   size_t length;

   length = wcslen(s);
   printf(&quot;Length in characters = %d\n&quot;, length);
   printf(&quot;Length in bytes      = %d\n&quot;, sizeof(s) * sizeof(wchar_t));
   
   return 0;
}
