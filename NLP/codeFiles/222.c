#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define KeyType const char *
#define ValType int

#define HASH_SIZE 4096

// hash function useful when KeyType is char * (string)
unsigned strhashkey( const char * key, int max)
{
    unsigned h=0;
    unsigned hl, hr;

    while(*key) {
        h += *key;
        hl= 0x5C5 ^ (h&amp;0xfff00000 )&gt;&gt;18;
        hr =(h&amp;0x000fffff );
        h = hl ^ hr ^ *key++;
    }
    return h % max;
}

typedef struct sHme {
    KeyType    key;
    ValType    value;
    struct sHme  *link;
} *MapEntry;

typedef struct he {
    MapEntry  first, last;
} HashElement;

HashElement hash[HASH_SIZE];
    
typedef void (*KeyCopyF)(KeyType *kdest, KeyType ksrc);
typedef void (*ValCopyF)(ValType *vdest, ValType vsrc);
typedef unsigned (*KeyHashF)( KeyType key, int upperBound );
typedef int (*KeyCmprF)(KeyType key1, KeyType key2);

void HashAddH( KeyType key, ValType value,
        KeyCopyF copyKey, ValCopyF copyVal, KeyHashF hashKey, KeyCmprF keySame )
{
    unsigned hix = (*hashKey)(key, HASH_SIZE);
    MapEntry m_ent;

    for (m_ent= hash[hix].first;
            m_ent &amp;&amp; !(*keySame)(m_ent-&gt;key,key); m_ent=m_ent-&gt;link);
    if (m_ent) {
        (*copyVal)(&amp;m_ent-&gt;value, value);
    }
    else {
        MapEntry last;
        MapEntry hme = malloc(sizeof(struct sHme));
        (*copyKey)(&amp;hme-&gt;key, key);
        (*copyVal)(&amp;hme-&gt;value, value);
        hme-&gt;link = NULL;
        last = hash[hix].last;
        if (last) {
//	    printf(&quot;Dup. hash key\n&quot;);
            last-&gt;link = hme;
        }
        else
            hash[hix].first = hme;
        hash[hix].last = hme;
    }
}

int HashGetH(ValType *val, KeyType key, KeyHashF hashKey, KeyCmprF keySame )
{
    unsigned hix = (*hashKey)(key, HASH_SIZE);
    MapEntry m_ent;
    for (m_ent= hash[hix].first;
            m_ent &amp;&amp; !(*keySame)(m_ent-&gt;key,key); m_ent=m_ent-&gt;link);
    if (m_ent) {
        *val = m_ent-&gt;value;
    }
    return (m_ent != NULL);
}

void copyStr(const char**dest, const char *src)
{
    *dest = strdup(src);
}
void copyInt( int *dest, int src)
{
    *dest = src;
}
int strCompare( const char *key1, const char *key2)
{
    return strcmp(key1, key2) == 0;
}
    
void HashAdd( KeyType key, ValType value )
{
    HashAddH( key, value, &amp;copyStr, &amp;copyInt, &amp;strhashkey, &amp;strCompare);
}

int HashGet(ValType *val, KeyType key)
{
    return HashGetH( val, key, &amp;strhashkey, &amp;strCompare);
}

int main() 
{
    static const char * keyList[] = {&quot;red&quot;,&quot;orange&quot;,&quot;yellow&quot;,&quot;green&quot;, &quot;blue&quot;, &quot;violet&quot; };
    static int valuList[] = {1,43,640, 747, 42, 42};
    int ix;

    for (ix=0; ix&lt;6; ix++) {
        HashAdd(keyList[ix], valuList[ix]);
    }
    return 0;
}
