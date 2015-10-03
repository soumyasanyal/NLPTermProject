int* ar;                  /* Collection&lt;Integer&gt; ar; */
int arSize;
arSize = (rand() % 6) + 1; 
ar = calloc(arSize, sizeof(int) ); /* ar = new ArrayList&lt;Integer&gt;(arSize); */
ar[0] = 1;                /* ar.set(0, 1); */

int* p;                   /* Iterator&lt;Integer&gt; p; Integer pValue; */
for (p=ar;                /* p=ar.itereator(); for( pValue=p.next(); */
       p&lt;(ar+arSize);     /*                         p.hasNext(); */
       p++) {             /*                         pValue=p.next() ) { */
  printf(&quot;%d\n&quot;,*p);      /*   System.out.println(pValue); */
}                         /* }    */
