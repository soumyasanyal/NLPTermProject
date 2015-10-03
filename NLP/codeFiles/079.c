typedef struct sMyClass{
  int variable;
} *MyClass;

MyClass  MyClass_new()
{
  MyClass pthis = malloc( sizeof(struct sMyClass) );
  //memset(pthis, 0, sizeof(struct sMyClass) );
  pthis-&gt;variable = 0;
  return pthis;
}

void MyClass_delete(MyClass* pthis)
{
  if(pthis &amp;&amp; *pthis)
  {
    free(*pthis);
    *pthis = NULL;
  }
}

void MyClass_someMethod(MyClass pthis)
{
  pthis-&gt;variable = 1;
}

MyClass obj = MyClass_new();
MyClass_someMethod(obj);
MyClass_delete(&amp;obj);
