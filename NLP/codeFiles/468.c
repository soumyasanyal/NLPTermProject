#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef struct sCarpet {
    int dim;      // dimension
    char *data;   // character data
    char **rows;  // pointers to data rows
} *Carpet;

/* Clones a tile into larger carpet, or blank if center */
void TileCarpet( Carpet d, int r, int c, Carpet tile )
{
    int y0 = tile-&gt;dim*r;
    int x0 = tile-&gt;dim*c;
    int k,m;

    if ((r==1) &amp;&amp; (c==1)) {
        for(k=0; k &lt; tile-&gt;dim; k++) {
           for (m=0; m &lt; tile-&gt;dim; m++) {
               d-&gt;rows[y0+k][x0+m] = ' ';
           }
        }
    }
    else {
        for(k=0; k &lt; tile-&gt;dim; k++) {
           for (m=0; m &lt; tile-&gt;dim; m++) {
               d-&gt;rows[y0+k][x0+m] = tile-&gt;rows[k][m];
           }
        }
    }
}

/* define a 1x1 starting carpet */
static char s1[]= &quot;#&quot;;
static char *r1[] = {s1};
static struct sCarpet single = { 1, s1, r1};

Carpet Sierpinski( int n )
{
   Carpet carpet;
   Carpet subCarpet;
   int row,col, rb;
   int spc_rqrd;

   subCarpet = (n &gt; 1) ? Sierpinski(n-1) : &amp;single;

   carpet = malloc(sizeof(struct sCarpet));
   carpet-&gt;dim = 3*subCarpet-&gt;dim;
   spc_rqrd = (2*subCarpet-&gt;dim) * (carpet-&gt;dim);
   carpet-&gt;data = malloc(spc_rqrd*sizeof(char));
   carpet-&gt;rows = malloc( carpet-&gt;dim*sizeof(char *));
   for (row=0; row&lt;subCarpet-&gt;dim; row++) {
       carpet-&gt;rows[row] = carpet-&gt;data + row*carpet-&gt;dim;
       rb = row+subCarpet-&gt;dim;
       carpet-&gt;rows[rb] = carpet-&gt;data + rb*carpet-&gt;dim;
       rb = row+2*subCarpet-&gt;dim;
       carpet-&gt;rows[rb] = carpet-&gt;data + row*carpet-&gt;dim;
   }
 
    for (col=0; col &lt; 3; col++) {
      /* 2 rows of tiles to copy - third group points to same data a first */
      for (row=0; row &lt; 2; row++)
         TileCarpet( carpet, row, col, subCarpet );
    }
    if (subCarpet != &amp;single ) {
       free(subCarpet-&gt;rows);
       free(subCarpet-&gt;data);
       free(subCarpet);
    }

    return carpet;
}

void CarpetPrint( FILE *fout, Carpet carp)
{
    char obuf[730];
    int row;
    for (row=0; row &lt; carp-&gt;dim; row++) {
       strncpy(obuf, carp-&gt;rows[row], carp-&gt;dim);
       fprintf(fout, &quot;%s\n&quot;, obuf);
    }
    fprintf(fout,&quot;\n&quot;);
}

int main(int argc, char *argv[])
{
//    FILE *f = fopen(&quot;sierp.txt&quot;,&quot;w&quot;);
    CarpetPrint(stdout, Sierpinski(3));
//    fclose(f);
    return 0;
}
