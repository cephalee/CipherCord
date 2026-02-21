#include <openssl/evp.h>
#include "../include/encrypt.h"

void encrypt_chunk(char *data, char key[16], chunk_header *cheader) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (unsigned char*)key, (unsigned char*)cheader->iv);
    
    int out_len;
    int final_len;
    
    EVP_EncryptUpdate(ctx, (unsigned char*)data, &out_len, (unsigned char*)data, cheader->data_size);
    
    EVP_EncryptFinal_ex(ctx, (unsigned char*)data + out_len, &final_len);

    cheader->data_size = out_len + final_len;

    EVP_CIPHER_CTX_free(ctx);
}