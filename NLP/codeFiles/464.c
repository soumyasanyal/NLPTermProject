#include &lt;stdio.h&gt;#include &lt;stdbool.h&gt;

bool a(bool in)
{
  printf(&quot;I am a\n&quot;);
  return in;
}

bool b(bool in)
{
  printf(&quot;I am b\n&quot;);
  return in;
}

#define TEST(X,Y,O)						\
  do {								\
    x = a(X) O b(Y);						\
    printf(#X &quot; &quot; #O &quot; &quot; #Y &quot; = %s\n\n&quot;, x ? &quot;true&quot; : &quot;false&quot;);	\
  } while(false);

int main()
{
  bool x;

  TEST(false, true, &amp;&amp;); // b is not evaluated
  TEST(true, false, ||); // b is not evaluated
  TEST(true, false, &amp;&amp;); // b is evaluated
  TEST(false, false, ||); // b is evaluated 

  return 0;
}
