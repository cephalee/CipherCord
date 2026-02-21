#include "../include/chunk.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void write_chunkheader(chunk_header* cheader, char key[16], uint32_t id ,uint32_t chunkid, uint8_t  is_last, uint32_t data_size){
    cheader->file_id = id;
    cheader->chunk_index = chunkid;
    cheader->data_size = data_size;
    cheader->is_last = is_last;
    memcpy(cheader->iv, key, 16);
}

void write_chunks(chunk_header* cheader, char key[16], uint32_t id, uint32_t chunkid, char **data, uint64_t *remaining_size, FILE* file){   
    uint8_t is_last= 0;
    unsigned read;
    if(*remaining_size < CHUNK_SIZE){
        is_last = 1;
        *data = (char *)malloc(*remaining_size + 20);
        read = *remaining_size;
    }
    else{
        *data = (char *)malloc(CHUNK_SIZE + 20);
        read = CHUNK_SIZE;
    }

    if(!*data){
        fprintf(stderr,"ERROR : malloc return NULL");
    }

    size_t bytes_actually_read = fread(*data, 1, read, file);
    *remaining_size -= bytes_actually_read;

    if (bytes_actually_read < read) {
        if (ferror(file)) {
            fprintf(stderr, "Error: reading file");
        }
    }
    write_chunkheader(cheader, key, id, chunkid, is_last, bytes_actually_read);

}