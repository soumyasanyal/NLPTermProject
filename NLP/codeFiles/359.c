#include &lt;stdlib.h&gt;#include &lt;stdarg.h&gt;
#include &lt;stdio.h&gt;
#include &lt;ctype.h&gt;
#include &lt;string.h&gt;

typedef const char * String;
typedef struct sTable {
    String * *rows;
    int      n_rows,n_cols;
} *Table;

typedef int (*CompareFctn)(String a, String b);

struct {
   CompareFctn  compare;
   int   column;
   int   reversed;
} sortSpec;

int CmprRows( const void *aa, const void *bb)
{
   String *rA = *(String **)aa;
   String *rB = *(String **)bb;
   int sortCol = sortSpec.column;

   String left = sortSpec.reversed ? rB[sortCol] : rA[sortCol];
   String right = sortSpec.reversed ? rA[sortCol] : rB[sortCol];
   return sortSpec.compare( left, right );
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * tbl parameter is a table of rows of strings
 * argSpec is a string containing zero or more of the letters o,c,r
 * if o is present - the corresponding optional argument is a function which 
 *      determines the ordering of the strings.
 * if c is present - the corresponding optional argument is an integer that
 *      specifies the column to sort on.
 * if r is present - the corresponding optional argument is either 
 *      true(nonzero) or false(zero) and if true, the sort will b in reverse order
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int sortTable(Table tbl, const char* argSpec,... )
{
   va_list vl;
   const char *p;
   int c;
   sortSpec.compare = &amp;strcmp;
   sortSpec.column = 0;
   sortSpec.reversed = 0;

   va_start(vl, argSpec);
   if (argSpec)
      for (p=argSpec; *p; p++) {
         switch (*p) {
         case 'o':
            sortSpec.compare = va_arg(vl,CompareFctn);
            break;
         case 'c':
            c = va_arg(vl,int);
            if ( 0&lt;=c &amp;&amp; c&lt;tbl-&gt;n_cols)
               sortSpec.column  = c;
            break;
         case 'r':
            sortSpec.reversed = (0!=va_arg(vl,int));
            break;
         }
      }
   va_end(vl);
   qsort( tbl-&gt;rows, tbl-&gt;n_rows, sizeof(String *), &amp;CmprRows);
   return 0;
}

void printTable( Table tbl, FILE *fout, const char *colFmts[])
{
   int row, col;

   for (row=0; row&lt;tbl-&gt;n_rows; row++) {
      fprintf(fout, &quot;   &quot;);
      for(col=0; col&lt;tbl-&gt;n_cols; col++) {
         fprintf(fout, colFmts[col], tbl-&gt;rows[row][col]);
      }
      fprintf(fout, &quot;\n&quot;);
   }
   fprintf(fout, &quot;\n&quot;);
}

int ord(char v)
{
    return v-'0';
}

/* an alternative comparison function */
int cmprStrgs(String s1, String s2)
{
    const char *p1 = s1; 
    const char *p2 = s2;
    const char *mrk1, *mrk2;
    while ((tolower(*p1) == tolower(*p2)) &amp;&amp; *p1) {
       p1++; p2++;
    }
    if (isdigit(*p1) &amp;&amp; isdigit(*p2)) {
        long v1, v2;
        if ((*p1 == '0') ||(*p2 == '0')) {
            while (p1 &gt; s1) {
                p1--; p2--;
                if (*p1 != '0') break;
            }
            if (!isdigit(*p1)) {
                p1++; p2++;
            }
        }
        mrk1 = p1; mrk2 = p2;
        v1 = 0;
        while(isdigit(*p1)) {
            v1 = 10*v1+ord(*p1);
            p1++;
        }
        v2 = 0;
        while(isdigit(*p2)) {
            v2 = 10*v2+ord(*p2);
            p2++;
        }
        if (v1 == v2) 
           return(p2-mrk2)-(p1-mrk1);
        return v1 - v2;
    }
    if (tolower(*p1) != tolower(*p2))
       return (tolower(*p1) - tolower(*p2));
    for(p1=s1, p2=s2; (*p1 == *p2) &amp;&amp; *p1; p1++, p2++);
    return (*p1 -*p2);
}

int main()
{
   const char *colFmts[] = {&quot; %-5.5s&quot;,&quot; %-5.5s&quot;,&quot; %-9.9s&quot;};
   String r1[] = { &quot;a101&quot;, &quot;red&quot;,  &quot;Java&quot; };
   String r2[] = { &quot;ab40&quot;, &quot;gren&quot;, &quot;Smalltalk&quot; };
   String r3[] = { &quot;ab9&quot;,  &quot;blue&quot;, &quot;Fortran&quot; };
   String r4[] = { &quot;ab09&quot;, &quot;ylow&quot;, &quot;Python&quot; };
   String r5[] = { &quot;ab1a&quot;, &quot;blak&quot;, &quot;Factor&quot; };
   String r6[] = { &quot;ab1b&quot;, &quot;brwn&quot;, &quot;C Sharp&quot; };
   String r7[] = { &quot;Ab1b&quot;, &quot;pink&quot;, &quot;Ruby&quot; };
   String r8[] = { &quot;ab1&quot;,  &quot;orng&quot;, &quot;Scheme&quot; };

   String *rows[] = { r1, r2, r3, r4, r5, r6, r7, r8 };
   struct sTable table;
   table.rows = rows;
   table.n_rows = 8;
   table.n_cols = 3;

   sortTable(&amp;table, &quot;&quot;);
   printf(&quot;sort on col 0, ascending\n&quot;);
   printTable(&amp;table, stdout, colFmts);

   sortTable(&amp;table, &quot;ro&quot;, 1, &amp;cmprStrgs);
   printf(&quot;sort on col 0, reverse.special\n&quot;);
   printTable(&amp;table, stdout, colFmts);

   sortTable(&amp;table, &quot;c&quot;, 1);
   printf(&quot;sort on col 1, ascending\n&quot;);
   printTable(&amp;table, stdout, colFmts);

   sortTable(&amp;table, &quot;cr&quot;, 2, 1);
   printf(&quot;sort on col 2, reverse\n&quot;);
   printTable(&amp;table, stdout, colFmts);
   return 0;
}
