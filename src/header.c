#include "../include/header.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>


int get_file_id(char *fname){
    int length = sizeof(EXTENSIONS_MAP) / sizeof(EXTENSIONS_MAP[0]);
    char *ext = strrchr(fname, '.');
    if(ext){
        for(int i = 0; i < length; i++){
            if(!strcmp(EXTENSIONS_MAP[i], ext)){
                return i;
            }
        }
    }
    return 0;
}

unsigned get_file_size(FILE *file){
    fseek(file, 0, SEEK_END);
    unsigned size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

void write_header(char *fname, FILE *file, file_header *fheader){
    fheader->id = get_file_id(fname);
    fheader->size = get_file_size(file);
}