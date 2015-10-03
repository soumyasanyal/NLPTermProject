#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
int main(int argc, char **argv)
{
   int user1 = 0, user2 = 0;
   int *a1, **array, row;

   printf(&quot;Enter two integers.  Space delimited, please:  &quot;);
   scanf(&quot;%d %d&quot;,&amp;user1, &amp;user2);

   a1 = malloc(user1*user2*sizeof(int));
   array = malloc(user2*sizeof(int*));
   for (row=0; row&lt;user1; row++) array[row]=a1+row*user2;

   array[user1/2][user2/2] = user1 + user2;
   printf(&quot;array[%d][%d] is %d\n&quot;,user1/2,user2/2,array[user1/2][user2/2]);
   free(array);
   free(a1);
   return 0;
}
