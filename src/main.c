#include <stdio.h>
#include <stdlib.h>
#include "include/header.h"

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "ERROR: file missing");
    }
    FILE *file = fopen(argv[1], "rb");
    if(!file){
        ferror(stderr, "ERROR: opening file");
    }

    char *fname = argv[1];
    file_header fheader;
    chunk_header cheader;
 
    return 0;
}