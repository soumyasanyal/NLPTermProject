#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;stdbool.h&gt;
#include &lt;unistd.h&gt;
#include &lt;time.h&gt;
#include &lt;pthread.h&gt;

#define N_BUCKETS 15

pthread_mutex_t bucket_mutex[N_BUCKETS];
int buckets[N_BUCKETS];

pthread_t equalizer;
pthread_t randomizer;

void transfer_value(int from, int to, int howmuch)
{
  bool swapped = false;

  if ( (from == to) || ( howmuch &lt; 0 ) ||
       (from &lt; 0 ) || (to &lt; 0) || (from &gt;= N_BUCKETS) || (to &gt;= N_BUCKETS) ) return;
  
  if ( from &gt; to ) {
    int temp1 = from;
    from = to;
    to = temp1;
    swapped = true;
    howmuch = -howmuch;
  }

  pthread_mutex_lock(&amp;bucket_mutex[from]);
  pthread_mutex_lock(&amp;bucket_mutex[to]);

  if ( howmuch &gt; buckets[from] &amp;&amp; !swapped )
    howmuch = buckets[from];
  if ( -howmuch &gt; buckets[to] &amp;&amp; swapped )
    howmuch = -buckets[to];
  
  buckets[from] -= howmuch;
  buckets[to] += howmuch;

  pthread_mutex_unlock(&amp;bucket_mutex[from]);
  pthread_mutex_unlock(&amp;bucket_mutex[to]);
}

void print_buckets()
{
  int i;
  int sum=0;

  for(i=0; i &lt; N_BUCKETS; i++) pthread_mutex_lock(&amp;bucket_mutex[i]);
  for(i=0; i &lt; N_BUCKETS; i++) {
    printf(&quot;%3d &quot;, buckets[i]);
    sum += buckets[i];
  }
  printf(&quot;= %d\n&quot;, sum);
  for(i=0; i &lt; N_BUCKETS; i++) pthread_mutex_unlock(&amp;bucket_mutex[i]);
}

void *equalizer_start(void *t)
{
  for(;;) {
    int b1 = rand()%N_BUCKETS;
    int b2 = rand()%N_BUCKETS;
    int diff = buckets[b1] - buckets[b2];
    if ( diff &lt; 0 )
      transfer_value(b2, b1, -diff/2);
    else
      transfer_value(b1, b2, diff/2);
  }
  return NULL;
}

void *randomizer_start(void *t)
{
  for(;;) {
    int b1 = rand()%N_BUCKETS;
    int b2 = rand()%N_BUCKETS;
    int diff = rand()%(buckets[b1]+1);
    transfer_value(b1, b2, diff);
  }
  return NULL;
}

int main()
{
  int i, total=0;

  for(i=0; i &lt; N_BUCKETS; i++) pthread_mutex_init(&amp;bucket_mutex[i], NULL);

  for(i=0; i &lt; N_BUCKETS; i++) {
    buckets[i] = rand() % 100;
    total += buckets[i];
    printf(&quot;%3d &quot;, buckets[i]);
  }
  printf(&quot;= %d\n&quot;, total);

  // we should check if these succeeded
  pthread_create(&amp;equalizer, NULL, equalizer_start, NULL);
  pthread_create(&amp;randomizer, NULL, randomizer_start, NULL);

  for(;;) {
    sleep(1);
    print_buckets();
  }

  // we do not provide a &quot;good&quot; way to stop this run, so the following
  // is never reached indeed...
  for(i=0; i &lt; N_BUCKETS; i++) pthread_mutex_destroy(bucket_mutex+i);
  return EXIT_SUCCESS;
}
