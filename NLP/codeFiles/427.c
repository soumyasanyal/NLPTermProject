#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;regex.h&gt;
#include &lt;string.h&gt;

int main()
{
   regex_t preg;
   regmatch_t substmatch[1];
   const char *tp = &quot;string$&quot;;
   const char *t1 = &quot;this is a matching string&quot;;
   const char *t2 = &quot;this is not a matching string!&quot;;
   const char *ss = &quot;istyfied&quot;;
   
   regcomp(&amp;preg, &quot;string$&quot;, REG_EXTENDED);
   printf(&quot;'%s' %smatched with '%s'\n&quot;, t1,
                                        (regexec(&amp;preg, t1, 0, NULL, 0)==0) ? &quot;&quot; : &quot;did not &quot;, tp);
   printf(&quot;'%s' %smatched with '%s'\n&quot;, t2,
                                        (regexec(&amp;preg, t2, 0, NULL, 0)==0) ? &quot;&quot; : &quot;did not &quot;, tp);
   regfree(&amp;preg);
   /* change &quot;a[a-z]+&quot; into &quot;istifyed&quot;?*/
   regcomp(&amp;preg, &quot;a[a-z]+&quot;, REG_EXTENDED);
   if ( regexec(&amp;preg, t1, 1, substmatch, 0) == 0 )
   {
      //fprintf(stderr, &quot;%d, %d\n&quot;, substmatch[0].rm_so, substmatch[0].rm_eo);
      char *ns = (char*)malloc(substmatch[0].rm_so + 1 + strlen(ss) +
                        (strlen(t1) - substmatch[0].rm_eo) + 2);
      memcpy(ns, t1, substmatch[0].rm_so+1);
      memcpy(&amp;ns[substmatch[0].rm_so], ss, strlen(ss));
      memcpy(&amp;ns[substmatch[0].rm_so+strlen(ss)], &amp;t1[substmatch[0].rm_eo],
                strlen(&amp;t1[substmatch[0].rm_eo]));
      ns[ substmatch[0].rm_so + strlen(ss) +
          strlen(&amp;t1[substmatch[0].rm_eo]) ] = 0;
      printf(&quot;mod string: '%s'\n&quot;, ns);
      free(ns); 
   } else {
      printf(&quot;the string '%s' is the same: no matching!\n&quot;, t1);
   }
   regfree(&amp;preg);
   
   return 0;
}
