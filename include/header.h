#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct __attribute__((packed)){
    uint32_t id;
    uint64_t size;

}file_header;

int get_file_id(char *fname);
unsigned get_file_size(FILE *file);
void write_header(char *fname, FILE *file, file_header *fheader);

#endif

