#include &lt;string.h&gt;
int palindrome(const char *s)
{
   int i,l;
   l = strlen(s);
   for(i=0; i&lt;l/2; i++)
   {
     if ( s[i] != s[l-i-1] ) return 0; 
   }
   return 1;
}
