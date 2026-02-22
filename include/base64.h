#include "chunk.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* base64_encode(char* buffer, size_t length);
char* encode_chunk(chunk_header *cheader, char *encrypted_data);
