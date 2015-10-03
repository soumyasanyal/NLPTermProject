#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
/* foreach macro for using a string as a collection of char */
#define foreach( ptrvar , strvar ) char* ptrvar; for( ptrvar=strvar ; (*ptrvar) != '\0' ; *ptrvar++)

int main(int argc,char* argv[]){
char* s1=&quot;abcdefg&quot;;
char* s2=&quot;123456789&quot;;
foreach( p1 , s1 ) {
 printf(&quot;loop 1 %c\n&quot;,*p1);
}
foreach( p2 , s2 ){
 printf(&quot;loop 2 %c\n&quot;,*p2);
}
exit(0);
return(0);
}

