#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {

    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;

}

int main(void) {

    CURL* curl;
    FILE* fp;
    CURLcode res;
    char* url = "http://pimg.tradeindia.com/01063301/b/1/CRO-Oscilloscope.jpg";
    char outfilename[FILENAME_MAX] = "image.jpg";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    return 0;

}