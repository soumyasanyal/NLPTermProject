#define cSize( a )  ( sizeof(a)/sizeof(a[0]) ) /* a.size() */int ar[10];               /* Collection&lt;Integer&gt; ar = new ArrayList&lt;Integer&gt;(10); */
ar[0] = 1;                /* ar.set(0, 1); */
ar[1] = 2;

int* p;                   /* Iterator&lt;Integer&gt; p; Integer pValue; */
for (p=ar;                /* for( p = ar.itereator(), pValue=p.next(); */
       p&lt;(ar+cSize(ar));  /*        p.hasNext(); */
       p++) {             /*        pValue=p.next() ) { */
  printf(&quot;%d\n&quot;,*p);      /*   System.out.println(pValue); */
}                         /* } */
