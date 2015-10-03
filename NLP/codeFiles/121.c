#include &lt;pthread.h&gt;#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;

typedef struct philData {
    pthread_mutex_t *fork_lft, *fork_rgt;
    const char *name;
    pthread_t thread;
    int   fail;
} Philosopher;

int running = 1;

void *PhilPhunction(void *p) {
    Philosopher *phil = (Philosopher*)p;
    int failed;
    int tries_left;
    pthread_mutex_t *fork_lft, *fork_rgt, *fork_tmp;

    while (running) {
        printf(&quot;%s is sleeping --er thinking\n&quot;, phil-&gt;name);
        sleep( 1+ rand()%8);

        fork_lft = phil-&gt;fork_lft;
        fork_rgt = phil-&gt;fork_rgt;
        printf(&quot;%s is hungry\n&quot;, phil-&gt;name);
        tries_left = 2;   /* try twice before being forceful */
        do {
            failed = pthread_mutex_lock( fork_lft);
            failed = (tries_left&gt;0)? pthread_mutex_trylock( fork_rgt )
                                   : pthread_mutex_lock(fork_rgt);
            if (failed) {
                pthread_mutex_unlock( fork_lft);
                fork_tmp = fork_lft;
                fork_lft = fork_rgt;
                fork_rgt = fork_tmp;
                tries_left -= 1;
            }
        } while(failed &amp;&amp; running);

        if (!failed) {
            printf(&quot;%s is eating\n&quot;, phil-&gt;name);
            sleep( 1+ rand() % 8);
            pthread_mutex_unlock( fork_rgt);
            pthread_mutex_unlock( fork_lft);
        }
    }
    return NULL;
}

void Ponder()
{
    const char *nameList[] = { &quot;Kant&quot;, &quot;Guatma&quot;, &quot;Russel&quot;, &quot;Aristotle&quot;, &quot;Bart&quot; };
    pthread_mutex_t forks[5];
    Philosopher philosophers[5];
    Philosopher *phil;
    int i;
    int failed;

    for (i=0;i&lt;5; i++) {
        failed = pthread_mutex_init(&amp;forks[i], NULL);
        if (failed) {
            printf(&quot;Failed to initialize mutexes.&quot;);
            exit(1);
        }
    }

    for (i=0;i&lt;5; i++) {
        phil = &amp;philosophers[i];
        phil-&gt;name = nameList[i];
        phil-&gt;fork_lft = &amp;forks[i];
        phil-&gt;fork_rgt = &amp;forks[(i+1)%5];
        phil-&gt;fail = pthread_create( &amp;phil-&gt;thread, NULL, PhilPhunction, phil);
    }

    sleep(40);
    running = 0;
    printf(&quot;cleanup time\n&quot;);

    for(i=0; i&lt;5; i++) {
        phil = &amp;philosophers[i];
        if ( !phil-&gt;fail &amp;&amp; pthread_join( phil-&gt;thread, NULL) ) {
            printf(&quot;error joining thread for %s&quot;, phil-&gt;name);
            exit(1);
        }
    }
}

int main()
{
    Ponder();
    return 0;
}
