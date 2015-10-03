#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
int main(int argc,char* argv[]){
/* foreach macro viewing an array of int values as a collection of int values */
#define foreach( intpvar , intary ) int* intpvar; for( intpvar=intary; intpvar &lt; (intary+(sizeof(intary)/sizeof(intary[0]))) ; intpvar++)
int a1[]={ 1 , 1 , 2 , 3 , 5 , 8 };
int a2[]={ 3 , 1 , 4 , 1, 5, 9 };
foreach( p1 , a1 ) {
 printf(&quot;loop 1 %d\n&quot;,*p1);
}
foreach( p2 , a2 ){
 printf(&quot;loop 2 %d\n&quot;,*p2);
}
exit(0);
return(0);
}

