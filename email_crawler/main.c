#include <curl/curl.h>

#include "util.h"


int main(int argc, char *argv[]) {
    if( argc != 2 ) {
        printf("try './email_crawler [url]'\n");
        exit (1);
    }

    CURL *ch;
    CURLcode res;

    ch = curl_easy_init();
    if (!ch) exit(1);

    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, process_data);
    curl_easy_setopt(ch, CURLOPT_URL, argv[1]);
    curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(ch);
    if (res != CURLE_OK) {
        fprintf(stderr, "error: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(ch);

    return 0;
}
