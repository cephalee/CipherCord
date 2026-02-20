#ifndef CHUNK_H
#define CHUNK_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CHUNK_SIZE 5242880

typedef struct __attribute__((packed)){
    uint32_t file_id;
    uint32_t chunk_index;
    uint8_t  is_last;
    char iv[16];

}chunk_header;

void write_chunks(chunk_header* cheader, char key[16], uint32_t id, uint32_t chunkid, char **data, uint64_t *remaining_size, FILE* file);
void write_chunkheader(chunk_header* cheader, char key[16], uint32_t id ,uint32_t chunkid, uint8_t  is_last);

#endif