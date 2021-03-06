...char *string_repeat(char *str, int n)
{
   char *pa, *pb;
   size_t slen = strlen(str);
   char *dest = malloc(n*slen+1);

   pa = dest + (n-1)*slen;
   strcpy(pa, str);
   pb = --pa + slen; 
   while (pa&gt;=dest) *pa-- = *pb--;
   return dest;
}
