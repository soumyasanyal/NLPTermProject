#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;curl/curl.h&gt;

int
main(void)
{
        CURL *curl;
        char buffer[CURL_ERROR_SIZE];

        if ((curl = curl_easy_init()) != NULL) {
                curl_easy_setopt(curl, CURLOPT_URL, &quot;https://sourceforge.net/&quot;);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
                curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, buffer);
                if (curl_easy_perform(curl) != CURLE_OK) {
                        fprintf(stderr, &quot;%s\n&quot;, buffer);
                        return EXIT_FAILURE;
                }
                curl_easy_cleanup(curl);
        }
        return EXIT_SUCCESS;
}

