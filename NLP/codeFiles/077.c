#include &lt;stdio.h&gt;#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;omp.h&gt;

int main()
{
        int jobs = 41, tid;
        omp_set_num_threads(5);

        #pragma omp parallel shared(jobs) private(tid)
        {
                tid = omp_get_thread_num();
                while (jobs &gt; 0) {
                        /* this is the checkpoint */
                        #pragma omp barrier
                        if (!jobs) break;

                        printf(&quot;%d: taking job %d\n&quot;, tid, jobs--);
                        usleep(100000 + rand() / (double) RAND_MAX * 3000000);
                        printf(&quot;%d: done job\n&quot;, tid);
                }

                printf(&quot;[%d] leaving\n&quot;, tid);

                /* this stops jobless thread from exiting early and killing workers */
                #pragma omp barrier
        }

        return 0;
}
