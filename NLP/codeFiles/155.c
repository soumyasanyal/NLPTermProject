#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;

typedef struct {
    int *list;
    short count; 
} Factors;

void xferFactors( Factors *fctrs, int *flist, int flix ) 
{
    int ix, ij;
    int newSize = fctrs-&gt;count + flix;
    if (newSize &gt; flix)  {
        fctrs-&gt;list = realloc( fctrs-&gt;list, newSize * sizeof(int));
    }
    else {
        fctrs-&gt;list = malloc(  newSize * sizeof(int));
    }
    for (ij=0,ix=fctrs-&gt;count; ix&lt;newSize; ij++,ix++) {
        fctrs-&gt;list[ix] = flist[ij];
    }
    fctrs-&gt;count = newSize;
}

Factors *factor( int num, Factors *fctrs)
{
    int flist[301], flix;
    int dvsr;
    flix = 0;
    fctrs-&gt;count = 0;
    free(fctrs-&gt;list);
    fctrs-&gt;list = NULL;
    for (dvsr=1; dvsr*dvsr &lt; num; dvsr++) {
        if (num % dvsr != 0) continue;
        if ( flix == 300) {
            xferFactors( fctrs, flist, flix );
            flix = 0;
        }
        flist[flix++] = dvsr;
        flist[flix++] = num/dvsr;
    }
    if (dvsr*dvsr == num) 
        flist[flix++] = dvsr;
    if (flix &gt; 0)
        xferFactors( fctrs, flist, flix );

    return fctrs;
}
        
int main(int argc, char*argv[])
{
    int nums2factor[] = { 2059, 223092870, 3135, 45 };
    Factors ftors = { NULL, 0};
    char sep;
    int i,j;

    for (i=0; i&lt;4; i++) {
        factor( nums2factor[i], &amp;ftors );
        printf(&quot;\nfactors of %d are:\n  &quot;, nums2factor[i]);
        sep = ' ';
        for (j=0; j&lt;ftors.count; j++) {
            printf(&quot;%c %d&quot;, sep, ftors.list[j]);
            sep = ',';
        }
        printf(&quot;\n&quot;);
    }
    return 0;
}
