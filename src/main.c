#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

#include "../include/header.h"
#include "../include/chunk.h"
#include "../include/encrypt.h"
#include "../include/base64.h"


int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "ERROR: file missing");
    }
    FILE *file = fopen(argv[1], "rb");
    if(!file){
        fprintf(stderr, "ERROR: opening file");
    }

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

    while (remaining_size > 0) {
        RAND_bytes(iv, 16);
        write_chunks(&cheader, iv, id, chunkid, &data, &remaining_size, file);
        if(!data){
            return 1;
        }
        encrypt_chunk(data, key, &cheader);
        final = encode_chunk(&cheader, data);
        if(!final){
            fprintf(stderr, "Error: something went wrong");
            return 1;
        }

        //send

        free(final);
        free(data);
        chunkid++;
    }
    
    fclose(file);
    return 0;
}