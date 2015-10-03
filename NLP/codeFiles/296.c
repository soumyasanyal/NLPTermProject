#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
int main(int argc,char* argv[]){
#define foreach( idxtype , idxpvar , col , colsiz ) idxtype* idxpvar; for( idxpvar=col ; idxpvar &lt; (col+(colsiz)) ; idxpvar++)
#define arraylen( ary ) ( sizeof(ary)/sizeof(ary[0]) )
char* c1=&quot;collection&quot;;
int c2[]={ 3 , 1 , 4 , 1, 5, 9 };
double* c3;
int c3len=4;
c3=(double*)calloc(c3len,sizeof(double)); 
c3[0]=1.2;c3[1]=3.4;c3[2]=5.6;c3[3]=7.8;  
foreach( char,p1   , c1, strlen(c1) ) {
 printf(&quot;loop 1 : %c\n&quot;,*p1);
}
foreach( int,p2    , c2, arraylen(c2) ){
 printf(&quot;loop 2 : %d\n&quot;,*p2);
}
foreach( double,p3 , c3, c3len ){
 printf(&quot;loop 3 : %3.1lf\n&quot;,*p3);
}
exit(0);
return(0);
}

