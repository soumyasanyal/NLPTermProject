#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;ctype.h&gt;

typedef struct twoStringsStruct {
    char * key, *value;
} sTwoStrings;
 
int ord( char v )
{
    static char *dgts = &quot;012345679&quot;;
    char *cp;
    for (cp=dgts; v != *cp; cp++);
    return (cp-dgts);
}

int cmprStrgs(const sTwoStrings *s1,const sTwoStrings *s2)
{
    char *p1 = s1-&gt;key; 
    char *p2 = s2-&gt;key;
    char *mrk1, *mrk2;
    while ((tolower(*p1) == tolower(*p2)) &amp;&amp; *p1) { p1++; p2++;}
    if (isdigit(*p1) &amp;&amp; isdigit(*p2)) {
        long v1, v2;
        if ((*p1 == '0') ||(*p2 == '0')) {
            while (p1 &gt; s1-&gt;key) {
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
    for(p1=s1-&gt;key, p2=s2-&gt;key; (*p1 == *p2) &amp;&amp; *p1; p1++, p2++);
    return (*p1 -*p2);
}

int maxstrlen( char *a, char *b)
{
	int la = strlen(a);
	int lb = strlen(b);
	return (la&gt;lb)? la : lb;
}

int main()
{
    sTwoStrings toBsorted[] = {
        { &quot;Beta11a&quot;, &quot;many&quot; },
        { &quot;alpha1&quot;, &quot;This&quot; },
        { &quot;Betamax&quot;, &quot;sorted.&quot; },
        { &quot;beta3&quot;, &quot;order&quot; },
        { &quot;beta11a&quot;, &quot;strings&quot; },
        { &quot;beta001&quot;, &quot;is&quot; },
        { &quot;beta11&quot;, &quot;which&quot; },
        { &quot;beta041&quot;, &quot;be&quot; },
        { &quot;beta05&quot;, &quot;in&quot; },
        { &quot;beta1&quot;, &quot;the&quot; },
        { &quot;beta40&quot;, &quot;should&quot; },
    };
#define ASIZE (sizeof(toBsorted)/sizeof(sTwoStrings))
    int k, maxlens[ASIZE];
    char format[12];
    sTwoStrings *cp;

    qsort( (void*)toBsorted, ASIZE, sizeof(sTwoStrings),cmprStrgs); 

    for (k=0,cp=toBsorted; k &lt; ASIZE; k++,cp++) {
        maxlens[k] = maxstrlen(cp-&gt;key, cp-&gt;value);   
        sprintf(format,&quot; %%-%ds&quot;, maxlens[k]);
        printf(format, toBsorted[k].value);
	}
    printf(&quot;\n&quot;);
    for (k=0; k &lt; ASIZE; k++) {
        sprintf(format,&quot; %%-%ds&quot;, maxlens[k]);
        printf(format, toBsorted[k].key);
	}
    printf(&quot;\n&quot;);

  return 0;
}
