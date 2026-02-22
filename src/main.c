#include <openssl/crypto.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <string.h>

#include "../include/header.h"
#include "../include/chunk.h"
#include "../include/encrypt.h"
#include "../include/send.h"



int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "ERROR: file missing");
    }
    FILE *file = fopen(argv[1], "rb");
    if(!file){
        fprintf(stderr, "ERROR: opening file");
        return 1;
    }

    char * hook= "^_^ not now";

    char *fname = argv[1];
    file_header fheader;
    chunk_header cheader;

    write_header(fname,file, &fheader);
    uint32_t id = fheader.id; 
    uint64_t remaining_size = fheader.size;


    int chunkid = 0;
    unsigned char key[16];
    RAND_bytes(key, 16);
    char* data;
    unsigned char iv[16];
    
    char *final;
    size_t final_size;

    while (remaining_size > 0) {
        RAND_bytes(iv, 16);
        write_chunks(&cheader, iv, id, chunkid, &data, &remaining_size, file);
        if(!data){
            return 1;
        }
    
        encrypt_chunk(data, key, &cheader);
        size_t final_size = sizeof(cheader) + cheader.data_size;
        char *final = malloc(final_size);
        memcpy(final, &cheader, sizeof(cheader));
        memcpy(final + sizeof(cheader), data, cheader.data_size);

        if(send_chunk_discord(hook, final, final_size, cheader.chunk_index, cheader.is_last)){
            fprintf(stderr, "ERROR: sending chunk\n");
            free(final);
            free(data);
            return 1;
        }

        free(final);
        free(data);
        OSSL_sleep(2000);

        chunkid++;
    }
    
    fclose(file);
    return 0;
}