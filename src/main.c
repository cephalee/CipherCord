#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/header.h"
#include "../include/chunk.h"
#include "../include/encrypt.h"

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

    char* data;
    char key[16];
    int chunkid = 0;

    while (remaining_size > 0) {
        write_chunks(&cheader, key, id, chunkid, &data, &remaining_size, file);
        if(!data){
            return 1;
        }
        
        generate_key(key);
        encrypt_chunk(data,key);
        free(data);
        chunkid++;
    }
    
    
    return 0;
}