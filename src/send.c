#include "../include/send.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int send_chunk_discord(const char *webhook, const char *data, size_t data_size, int chunk_index, int is_last)
{
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error: curl_easy_init failed\n");
        return -1;
    }

    char filename[128];
    time_t now = time(NULL);
    struct tm *t = gmtime(&now);  
    snprintf(filename, sizeof(filename), 
        "chunk_%d_%04d%02d%02d_%02d%02d%02d.bin",
        chunk_index,
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
    );

    char payload[128];
    snprintf(payload, sizeof(payload),
        "{\"content\": \"chunk:%d | last:%s\"}",
        chunk_index, is_last ? "true" : "false");

    curl_mime *mime = curl_mime_init(curl);

    curl_mimepart *part = curl_mime_addpart(mime);
    curl_mime_name(part, "payload_json");
    curl_mime_data(part, payload, CURL_ZERO_TERMINATED);
    curl_mime_type(part, "application/json");

    // Partie 2 : le fichier binaire
    part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filename(part, filename);
    curl_mime_type(part, "application/octet-stream");
    curl_mime_data(part, data, data_size); 

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    CURLcode res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Error curl: %s\n", curl_easy_strerror(res));
        return -1;
    }

    if (http_code != 200 && http_code != 204) {
        fprintf(stderr, "Error Discord HTTP: %ld\n", http_code);
        return -1;
    }

    return 0;
}