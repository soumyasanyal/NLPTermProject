#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef const char * (*Responder)( int p1);

typedef struct sDelegate {
    Responder operation;
} *Delegate;

/* Delegate class constructor */
Delegate NewDelegate( Responder rspndr )
{
    Delegate dl = malloc(sizeof(struct sDelegate));
    dl-&gt;operation = rspndr;
    return dl;
}

/* Thing method of Delegate */
const char *DelegateThing(Delegate dl, int p1)
{
    return  (dl-&gt;operation)? (*dl-&gt;operation)(p1) : NULL;
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
typedef struct sDelegator {
    int     param;
    char    *phrase;
    Delegate delegate;
} *Delegator;

const char * defaultResponse( int p1)
{
    return &quot;default implementation&quot;;
}

static struct sDelegate defaultDel = { &amp;defaultResponse };

/* Delegator class constructor */
Delegator NewDelegator( int p, char *phrase)
{
    Delegator d  = malloc(sizeof(struct sDelegator));
    d-&gt;param = p;
    d-&gt;phrase = phrase;
    d-&gt;delegate = &amp;defaultDel;	/* default delegate */
    return d;
}

/* Operation method of Delegator */
const char *Delegator_Operation( Delegator theDelegator, int p1, Delegate delroy)
{
    const char *rtn;
    if (delroy) {
        rtn = DelegateThing(delroy, p1);
        if (!rtn) {			/* delegate didn't handle 'thing' */
            rtn = DelegateThing(theDelegator-&gt;delegate, p1);
        }
    }
    else 		/* no delegate */
        rtn = DelegateThing(theDelegator-&gt;delegate, p1);

    printf(&quot;%s\n&quot;, theDelegator-&gt;phrase );
    return rtn;
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
const char *thing1( int p1)
{
    printf(&quot;We're in thing1 with value %d\n&quot; , p1);
    return &quot;delegate implementation&quot;;
}

int main()
{
    Delegate del1 = NewDelegate(&amp;thing1);
    Delegate del2 = NewDelegate(NULL);
    Delegator theDelegator = NewDelegator( 14, &quot;A stellar vista, Baby.&quot;);

    printf(&quot;Delegator returns %s\n\n&quot;, 
            Delegator_Operation( theDelegator, 3, NULL));
    printf(&quot;Delegator returns %s\n\n&quot;, 
            Delegator_Operation( theDelegator, 3, del1));
    printf(&quot;Delegator returns %s\n\n&quot;,
            Delegator_Operation( theDelegator, 3, del2));
    return 0;
}
