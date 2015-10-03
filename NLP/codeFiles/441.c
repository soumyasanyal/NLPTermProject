char *ToRoman(int num, char *buf, int buflen){
   static const char romanDgts[] = &quot;ivxlcdmVXLCDM_&quot;;
   char *roman = buf + buflen;
   int  rdix, r, v;
   *--roman = '\0';        /* null terminate return string */
   if (num &gt;= 4000000) {
      printf(&quot;Number Too Big.\n&quot;);
      return NULL;
      }
   for (rdix = 0; rdix &lt; strlen(romanDgts); rdix += 2) {
      if (num == 0) break;
      v = (num % 10) / 5;
      r = num % 5;
      num = num / 10;
      if (r == 4) {
         if (roman &lt; buf+2) {
            printf(&quot;Buffer too small.&quot;);
            return NULL;
            }
         *--roman = romanDgts[rdix+1+v];
         *--roman = romanDgts[rdix];
         }
      else {
         if (roman &lt; buf+r+v) {
            printf(&quot;Buffer too small.&quot;);
            return NULL;
            }
         while(r-- &gt; 0) {
            *--roman = romanDgts[rdix];
            }
         if (v==1) {
            *--roman = romanDgts[rdix+1];
            }
         }
      }
   return roman;
}
