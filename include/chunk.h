#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct __attribute__((packed)){
    uint32_t file_id;
    uint32_t chunk_index;
    uint8_t  is_last;
    uint64_t total_size;

}chunk_header;

typedef struct __attribute__((packed)){
    char* data;
    
}chunk;

