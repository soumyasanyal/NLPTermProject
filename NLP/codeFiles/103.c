#include &lt;stdio.h&gt;
int main(int argc, char **argv) {

   int user1 = 0, user2 = 0;
   printf(&quot;Enter two integers.  Space delimited, please:  &quot;);
   scanf(&quot;%d %d&quot;,&amp;user1, &amp;user2);
   int array[user1][user2];
   array[user1/2][user2/2] = user1 + user2;
   printf(&quot;array[%d][%d] is %d\n&quot;,user1/2,user2/2,array[user1/2][user2/2]);

   return 0;
}
