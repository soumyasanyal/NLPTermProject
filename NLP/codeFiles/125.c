// A doubly linked list of strings;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef struct sListEntry {
    const char *value;
    struct sListEntry *next;
    struct sListEntry *prev;
} *ListEntry, *LinkedList;

typedef struct sListIterator{
    ListEntry  link;
    LinkedList head;
} *LIterator;

LinkedList NewList() {
    ListEntry le = malloc(sizeof(struct sListEntry));
    if (le) {
        le-&gt;value = NULL;
        le-&gt;next = le-&gt;prev = NULL;
    }
    return le;
}

int LL_Append(LinkedList ll, const char *newVal) 
{
    ListEntry le = malloc(sizeof(struct sListEntry));
    if (le) {
        le-&gt;value = strdup(newVal);
        le-&gt;prev = ll-&gt;prev;
        le-&gt;next = NULL;
        if (le-&gt;prev) 
            le-&gt;prev-&gt;next = le;
        else
            ll-&gt;next = le;
        ll-&gt;prev = le;
    }
    return (le!= NULL);
}

int LI_Insert(LIterator iter, const char *newVal)
{
    ListEntry crnt = iter-&gt;link;
    ListEntry le = malloc(sizeof(struct sListEntry));
    if (le) {
        le-&gt;value = strdup(newVal);
        if ( crnt == iter-&gt;head) {
            le-&gt;prev = NULL;
            le-&gt;next = crnt-&gt;next;
            crnt-&gt;next = le;
            if (le-&gt;next)
                le-&gt;next-&gt;prev = le;
            else 
                crnt-&gt;prev = le;
        }
        else {
            le-&gt;prev = ( crnt == NULL)? iter-&gt;head-&gt;prev : crnt-&gt;prev;
            le-&gt;next = crnt;
            if (le-&gt;prev)
                le-&gt;prev-&gt;next = le;
            else
                iter-&gt;head-&gt;next = le;
            if (crnt) 
                crnt-&gt;prev = le;
            else 
                iter-&gt;head-&gt;prev = le;
        }
    }
    return (le!= NULL);
}

LIterator LL_GetIterator(LinkedList ll ) 
{
    LIterator liter = malloc(sizeof(struct sListIterator));
    liter-&gt;head = ll;
    liter-&gt;link = ll;
    return liter;
}

#define LLI_Delete( iter ) \
    {free(iter); \
    iter = NULL;}

int LLI_AtEnd(LIterator iter)
{
    return iter-&gt;link == NULL;
}
const char *LLI_Value(LIterator iter)
{
    return (iter-&gt;link)? iter-&gt;link-&gt;value: NULL;
}
int LLI_Next(LIterator iter)
{
    if (iter-&gt;link) iter-&gt;link = iter-&gt;link-&gt;next;
    return(iter-&gt;link != NULL);
}
int LLI_Prev(LIterator iter)
{
    if (iter-&gt;link) iter-&gt;link = iter-&gt;link-&gt;prev;
    return(iter-&gt;link != NULL);
}

int main() 
{
    static const char *contents[] = {&quot;Read&quot;, &quot;Orage&quot;, &quot;Yeller&quot;, 
                                     &quot;Glean&quot;, &quot;Blew&quot;, &quot;Burple&quot;};
    int ix;
    LinkedList ll = NewList();    //new linked list
    LIterator iter;

    for (ix=0; ix&lt;6; ix++)        //insert contents
        LL_Append(ll, contents[ix]);

    iter = LL_GetIterator(ll);    //get an iterator
    printf(&quot;forward\n&quot;);
    while(LLI_Next(iter))         //iterate forward
        printf(&quot;value=%s\n&quot;, LLI_Value(iter));    
    LLI_Delete(iter);             //delete iterator

    printf(&quot;\nreverse\n&quot;);
    iter = LL_GetIterator(ll);
    while(LLI_Prev(iter))         //iterate reverse 
        printf(&quot;value=%s\n&quot;, LLI_Value(iter));
    LLI_Delete(iter);
                        //uhhh-- delete list??
    return 0;
}
