#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "chunk.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>


void encrypt_chunk(char *data, char key[16], chunk_header *cheader);

#endif