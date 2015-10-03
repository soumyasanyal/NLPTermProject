#include &lt;stdio.h&gt;typedef enum{false=0, true=!0} bool;
typedef void iterator;

#include &lt;setjmp.h&gt;
/* declare label otherwise it is not visible in sub-scope */
#define LABEL(label) jmp_buf label; if(setjmp(label))goto label;
#define GOTO(label) longjmp(label, true)

/* the following line is the only time I have ever required &quot;auto&quot; */
#define FOR(i, iterator) { auto bool lambda(i); yield_init = (void *)&amp;lambda; iterator; bool lambda(i)
#define DO {
#define     YIELD(x) if(!yield(x))return
#define     BREAK    return false
#define     CONTINUE return true
#define OD CONTINUE; } }

static volatile void *yield_init; /* not thread safe */
#define YIELDS(type) bool (*yield)(type) = yield_init

iterator fibonacci(int stop){
    YIELDS(int);
    int f[] = {0, 1};
    int i;
    for(i=0; i&lt;stop; i++){
        YIELD(f[i%2]);
        f[i%2]=f[0]+f[1];
    }
}

main(){
  printf(&quot;fibonacci: &quot;);
  FOR(int i, fibonacci(16)) DO
    printf(&quot;%d, &quot;,i);
  OD;
  printf(&quot;...\n&quot;);
}
