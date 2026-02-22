#include <openssl/core.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "../include/base64.h"


char* base64_encode(char* buffer, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char* res = malloc(bufferPtr->length + 1);
    if (!res){
        fprintf(stderr, "Error: malloc return null");
        return NULL;
    }
    memcpy(res, bufferPtr->data, bufferPtr->length);
    res[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    return res;
}

char* encode_chunk(chunk_header *cheader, char *encrypted_data) {
    size_t header_size = sizeof(chunk_header);
    size_t data_size = cheader->data_size;
    size_t chunk_size = header_size + data_size;

    char *chunk = malloc(chunk_size);
    if (!chunk){
        fprintf(stderr, "Error: malloc return null");
        return NULL;
    }

    memcpy(chunk, cheader, header_size);
    memcpy(chunk + header_size, encrypted_data, data_size);
    char *final = base64_encode(chunk, chunk_size);

    free(chunk);
    return final;
}

