#include &lt;stdio.h&gt;
typedef struct closure {
    void (*f)( void *elem, void *data);
    void  *data;
} *Closure;
        
typedef struct listSpec{
    void (*print)( void *);
    void *ary;
    int  count;
    size_t elem_size;
} *ListSpec;

#define LIST_SPEC( pf,typ,aa) {pf, aa, (sizeof(aa)/sizeof(typ)), sizeof(typ) }


/* calls closure's function f for each element in list */
void DoForEach( Closure c, ListSpec aspec )
{
    int i;
    void *val_ptr;
    for (i=0, val_ptr=aspec-&gt;ary; i&lt; aspec-&gt;count; i++) {
        (*c-&gt;f)(val_ptr, c-&gt;data);
         val_ptr = ((char *)val_ptr) + aspec-&gt;elem_size;
    }
}

/* Used to find the minimum array length of list of lists */
void FindMin( ListSpec *paspec, int *minCount )
{
    ListSpec aspec = *paspec;
    if (*minCount&gt;aspec-&gt;count) *minCount = aspec-&gt;count;
}

/* prints an element of a list using the list's print function */
void PrintElement( ListSpec *paspec, int *indx )
{
    ListSpec aspec = *paspec;
    (*aspec-&gt;print)( ((char*)aspec-&gt;ary) + (*indx)*aspec-&gt;elem_size);
}


/* Loop Over multiple lists (a list of lists)*/
void LoopMultiple( ListSpec arrays)
{
    int indx;
    int minCount = 100000;
    struct closure c1 = { &amp;FindMin, &amp;minCount };
    struct closure xclsr = { &amp;PrintElement, &amp;indx };
    DoForEach( &amp;c1, arrays);
    printf(&quot;min count = %d\n&quot;, minCount);

    for (indx=0; indx&lt;minCount; indx++) {
        DoForEach(&amp;xclsr, arrays );
        printf(&quot;\n&quot;);
    }
}

/* Defining our Lists */

void PrintInt( int *ival)
{  printf(&quot;%3d,&quot;, *ival);
}
int ary1[] = { 6,5,4,9,8,7 };
struct listSpec lspec1 = LIST_SPEC( &amp;PrintInt, int, ary1 );

void PrintShort( short *ival)
{  printf(&quot;%3d,&quot;, *ival);
}
short ary2[] = { 3, 66, 20, 15, 7, 22, 10 };
struct listSpec lspec2 = LIST_SPEC( &amp;PrintShort , short, ary2 );

void PrintStrg( char **strg )
{  printf(&quot; %s&quot;, *strg);
}
char *ary3[] = {&quot;Hello&quot;, &quot;all&quot;, &quot;you&quot;,&quot;good&quot;, &quot;folks&quot;,&quot;out&quot;, &quot;there&quot; };
struct listSpec lspec3 = LIST_SPEC( &amp;PrintStrg , char *, ary3 );

void PrintLstSpec( ListSpec *ls )
{  printf(&quot;not-implemented&quot;);
}
ListSpec listList[] = { &amp;lspec1, &amp;lspec2,  &amp;lspec3 };
struct listSpec llSpec = LIST_SPEC(&amp;PrintLstSpec, ListSpec, listList);

int main(int argc, char *argv[])
{
    LoopMultiple( &amp;llSpec);
    return 0;
}
