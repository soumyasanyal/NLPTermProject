#include &lt;stdio.h&gt;#include &lt;unistd.h&gt;
#include &lt;pthread.h&gt;

pthread_mutex_t condm = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int bang = 0;

#define WAITBANG() do { \
   pthread_mutex_lock(&amp;condm); \
   while( bang == 0 ) \
   { \
      pthread_cond_wait(&amp;cond, &amp;condm); \
   } \
   pthread_mutex_unlock(&amp;condm); } while(0);\

void *t_enjoy(void *p)
{
  WAITBANG();
  printf(&quot;Enjoy\n&quot;);
  pthread_exit(0);
}

void *t_rosetta(void *p)
{
  WAITBANG();
  printf(&quot;Rosetta\n&quot;);
  pthread_exit(0);
}

void *t_code(void *p)
{
  WAITBANG();
  printf(&quot;Code\n&quot;);
  pthread_exit(0);
}

typedef void *(*threadfunc)(void *);
int main()
{
   int i;
   pthread_t a[3];
   threadfunc p[3] = {t_enjoy, t_rosetta, t_code};
   
   for(i=0;i&lt;3;i++)
   {
     pthread_create(&amp;a[i], NULL, p[i], NULL);
   }
   sleep(1);
   bang = 1;
   pthread_cond_broadcast(&amp;cond);
   for(i=0;i&lt;3;i++)
   {
     pthread_join(a[i], NULL);
   }
}
