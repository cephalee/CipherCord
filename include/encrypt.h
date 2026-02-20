#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>


void generate_key(char key[16]);
void encrypt_chunk(char *data, char key[16]);

#endif