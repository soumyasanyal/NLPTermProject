#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

typedef struct object *BaseObj;
typedef struct sclass *Class;
typedef void (*CloneFctn)(BaseObj s, BaseObj clo);
typedef const char * (*SpeakFctn)(BaseObj s);
typedef void (*DestroyFctn)(BaseObj s);

typedef struct sclass {
    size_t csize;		/* size of the class instance */
    const char  *cname;		/* name of the class */
    Class  parent;		/* parent class */

    CloneFctn clone;		/* clone function */
    SpeakFctn speak;		/* speak function */
    DestroyFctn del;		/* delete the object */
} sClass;

typedef struct object {
    Class class;
} SObject;

static 
BaseObj obj_copy( BaseObj s, Class c )
{
    BaseObj clo;
    if (c-&gt;parent) 
        clo = obj_copy( s, c-&gt;parent);
    else 
        clo = malloc( s-&gt;class-&gt;csize );

    if (clo)
        c-&gt;clone( s, clo );
    return clo;
}

static
void obj_del( BaseObj s, Class c )
{
    if (c-&gt;del)
        c-&gt;del(s);
    if (c-&gt;parent)
        obj_del( s, c-&gt;parent);
    else
        free(s);
}

BaseObj ObjClone( BaseObj s )
{ return obj_copy( s, s-&gt;class ); }

const char * ObjSpeak( BaseObj s )
{ 
    return s-&gt;class-&gt;speak(s); 
}

void ObjDestroy( BaseObj s )
{ if (s) obj_del( s, s-&gt;class ); }

/* * * * * * */
static
void baseClone( BaseObj s, BaseObj clone)
{  
    clone-&gt;class = s-&gt;class;
}

static
const char *baseSpeak(BaseObj s)
{
    return &quot;Hello, I'm base object&quot;;
}

sClass boc = { sizeof(SObject), &quot;BaseObj&quot;, NULL, 
    &amp;baseClone, &amp;baseSpeak, NULL };
Class BaseObjClass = &amp;boc;

/* * * * * * */
/* Dog - a derived class */

typedef struct sDogPart {
    double weight;
    char color[32];
    char name[24];
} DogPart;

typedef struct sDog *Dog;

struct sDog {
    Class   class;		// parent structure
    DogPart dog;
};

static
void dogClone( BaseObj s, BaseObj c)
{  
    Dog src = (Dog)s;
    Dog clone = (Dog)c;
    clone-&gt;dog = src-&gt;dog;	/* no pointers so strncpys not needed */
}

static
const char *dogSpeak( BaseObj s)
{
    Dog d = (Dog)s;
    static char  response[90];
    sprintf(response, &quot;woof! woof! My name is %s. I'm a %s %s&quot;, 
            d-&gt;dog.name, d-&gt;dog.color, d-&gt;class-&gt;cname);
    return response;
}


sClass dogc = { sizeof(struct sDog), &quot;Dog&quot;, &amp;boc,
    &amp;dogClone, &amp;dogSpeak, NULL };
Class DogClass = &amp;dogc;

BaseObj NewDog( const char *name, const char *color, double weight )
{
    Dog dog = malloc(DogClass-&gt;csize);
    if (dog) {
        DogPart *dogp = &amp;dog-&gt;dog;
        dog-&gt;class = DogClass;
        dogp-&gt;weight = weight;
        strncpy(dogp-&gt;name, name, 23);
        strncpy(dogp-&gt;color, color, 31);
    }
    return (BaseObj)dog;
}

/* * * * * * * * * */
/* Ferret - a derived class */

typedef struct sFerretPart {
    char color[32];
    char name[24];
    int  age;
} FerretPart;

typedef struct sFerret *Ferret;

struct sFerret {
    Class   class;		// parent structure
    FerretPart ferret;
};

static
void ferretClone( BaseObj s, BaseObj c)
{  
    Ferret src = (Ferret)s;
    Ferret clone = (Ferret)c;
    clone-&gt;ferret = src-&gt;ferret;  /* no pointers so strncpys not needed */
}

static
const char *ferretSpeak(BaseObj s)
{
    Ferret f = (Ferret)s;
    static char  response[90];
    sprintf(response, &quot;My name is %s. I'm a %d mo. old %s wiley %s&quot;, 
            f-&gt;ferret.name, f-&gt;ferret.age, f-&gt;ferret.color,
            f-&gt;class-&gt;cname);
    return response;
}

sClass ferretc = { sizeof(struct sFerret), &quot;Ferret&quot;, &amp;boc, 
    &amp;ferretClone, &amp;ferretSpeak, NULL };
Class FerretClass = &amp;ferretc;

BaseObj NewFerret( const char *name, const char *color, int age )
{
    Ferret ferret = malloc(FerretClass-&gt;csize);
    if (ferret) {
        FerretPart *ferretp = &amp;(ferret-&gt;ferret);
        ferret-&gt;class = FerretClass;
        strncpy(ferretp-&gt;name, name, 23);
        strncpy(ferretp-&gt;color, color, 31);
        ferretp-&gt;age = age;
    }
    return (BaseObj)ferret;
}

/* * Now you really understand why Bjarne created C++ * */

int main()
{
    BaseObj  o1;
    BaseObj  kara = NewFerret( &quot;Kara&quot;, &quot;grey&quot;, 15 );
    BaseObj  bruce = NewDog(&quot;Bruce&quot;, &quot;yellow&quot;, 85.0 );
    printf(&quot;Ok created things\n&quot;);

    o1 = ObjClone(kara );
    printf(&quot;Karol says %s\n&quot;, ObjSpeak(o1));
    printf(&quot;Kara says %s\n&quot;, ObjSpeak(kara));
    ObjDestroy(o1);

    o1 = ObjClone(bruce );
    strncpy(((Dog)o1)-&gt;dog.name, &quot;Donald&quot;, 23);
    printf(&quot;Don says %s\n&quot;, ObjSpeak(o1));
    printf(&quot;Bruce says %s\n&quot;, ObjSpeak(bruce));
    ObjDestroy(o1);
    return 0;
}
