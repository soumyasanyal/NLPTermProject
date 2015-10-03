#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;
#include &lt;time.h&gt;

char *sortedWord(const char *word, char *wbuf)
{
    char *p1, *p2, *endwrd;
    char t;
    int swaps;

    strcpy(wbuf, word);
    endwrd = wbuf+strlen(wbuf);
    do {
       swaps = 0;
       p1 = wbuf; p2 = endwrd-1;
       while (p1&lt;p2) {
          if (*p2 &gt; *p1) {
             t = *p2; *p2 = *p1; *p1 = t;
             swaps = 1;
          }
          p1++; p2--;
       }
       p1 = wbuf; p2 = p1+1;
       while(p2 &lt; endwrd) {
           if (*p2 &gt; *p1) {
             t = *p2; *p2 = *p1; *p1 = t;
             swaps = 1;
           }
           p1++; p2++;
       }
    } while (swaps);
    return wbuf;
}

static
short cxmap[] = {
    0x06, 0x1f, 0x4d, 0x0c, 0x5c, 0x28, 0x5d, 0x0e, 0x09, 0x33, 0x31, 0x56,
    0x52, 0x19, 0x29, 0x53, 0x32, 0x48, 0x35, 0x55, 0x5e, 0x14, 0x27, 0x24,
    0x02, 0x3e, 0x18, 0x4a, 0x3f, 0x4c, 0x45, 0x30, 0x08, 0x2c, 0x1a, 0x03,
    0x0b, 0x0d, 0x4f, 0x07, 0x20, 0x1d, 0x51, 0x3b, 0x11, 0x58, 0x00, 0x49,
    0x15, 0x2d, 0x41, 0x17, 0x5f, 0x39, 0x16, 0x42, 0x37, 0x22, 0x1c, 0x0f,
    0x43, 0x5b, 0x46, 0x4b, 0x0a, 0x26, 0x2e, 0x40, 0x12, 0x21, 0x3c, 0x36,
    0x38, 0x1e, 0x01, 0x1b, 0x05, 0x4e, 0x44, 0x3d, 0x04, 0x10, 0x5a, 0x2a,
    0x23, 0x34, 0x25, 0x2f, 0x2b, 0x50, 0x3a, 0x54, 0x47, 0x59, 0x13, 0x57,
   };
#define CXMAP_SIZE (sizeof(cxmap)/sizeof(short))


int Str_Hash( const char *key, int ix_max )
{
   const char *cp;
   short mash;
   int  hash = 33501551;
   for (cp = key; *cp; cp++) {
      mash = cxmap[*cp % CXMAP_SIZE];
      hash = (hash &gt;&gt;4) ^ 0x5C5CF5C ^ ((hash&lt;&lt;1) + (mash&lt;&lt;5));
      hash &amp;= 0x3FFFFFFF;
      }
   return  hash % ix_max;
}

typedef struct sDictWord  *DictWord;
struct sDictWord {
    const char *word;
    DictWord next;
};

typedef struct sHashEntry *HashEntry;
struct sHashEntry {
    const char *key;
    HashEntry next;
    DictWord  words;
    HashEntry link;
    short wordCount;
};

#define HT_SIZE 8192

HashEntry hashTable[HT_SIZE];

HashEntry mostPerms = NULL;

int buildAnagrams( FILE *fin )
{
    char buffer[40];
    char bufr2[40];
    char *hkey;
    int hix;
    HashEntry he, *hep;
    DictWord  we;
    int  maxPC = 2;
    int numWords = 0;
    
    while ( fgets(buffer, 40, fin)) {
        for(hkey = buffer; *hkey &amp;&amp; (*hkey!='\n'); hkey++);
        *hkey = 0;
        hkey = sortedWord(buffer, bufr2);
        hix = Str_Hash(hkey, HT_SIZE);
        he = hashTable[hix]; hep = &amp;hashTable[hix];
        while( he &amp;&amp; strcmp(he-&gt;key , hkey) ) {
            hep = &amp;he-&gt;next;
            he = he-&gt;next;
        }
        if ( ! he ) {
            he = malloc(sizeof(struct sHashEntry));
            he-&gt;next = NULL;
            he-&gt;key = strdup(hkey);
            he-&gt;wordCount = 0;
            he-&gt;words = NULL;
            he-&gt;link = NULL;
            *hep = he;
        }
        we = malloc(sizeof(struct sDictWord));
        we-&gt;word = strdup(buffer);
        we-&gt;next = he-&gt;words;
        he-&gt;words = we;
        he-&gt;wordCount++;
        if ( maxPC &lt; he-&gt;wordCount) {
            maxPC = he-&gt;wordCount;
            mostPerms = he;
            he-&gt;link = NULL;
        }
        else if (maxPC == he-&gt;wordCount) {
            he-&gt;link = mostPerms;
            mostPerms = he;
        }
         
        numWords++;
    }
    printf(&quot;%d words in dictionary max ana=%d\n&quot;, numWords, maxPC);
    return maxPC;
}


int main( ) 
{
    HashEntry he;
    DictWord  we;
    FILE *f1;
    
    f1 = fopen(&quot;unixdict.txt&quot;,&quot;r&quot;);
    buildAnagrams(f1);
    fclose(f1);
    
    f1 = fopen(&quot;anaout.txt&quot;,&quot;w&quot;);
//    f1 = stdout;

    for (he = mostPerms; he; he = he-&gt;link) {
        fprintf(f1,&quot;%d:&quot;, he-&gt;wordCount);
        for(we = he-&gt;words; we; we = we-&gt;next) {
            fprintf(f1,&quot;%s, &quot;, we-&gt;word);
        }
        fprintf(f1, &quot;\n&quot;);
    }

    fclose(f1);
    return 0;
}
