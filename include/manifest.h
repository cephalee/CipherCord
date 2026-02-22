#ifndef MANIFEST_H
#define MANIFEST_H

#include <stdint.h>
#include "chunk.h"

typedef struct {
    char        filename[256];
    uint32_t    file_id;
    uint64_t    size;
    char        key_b64[64];     // clé AES encodée en base64
    char        timestamp[32];
    cJSON       *chunks_array;   // tableau JSON des chunks
    cJSON       *root;           // objet JSON racine
} manifest;

// Initialise le manifest en début de programme
manifest* manifest_init(const char *fname, uint32_t file_id, uint64_t size, unsigned char key[16]);

// Ajoute un chunk au manifest (à appeler après chaque envoi)
void manifest_add_chunk(manifest *m, int chunk_index, const char *discord_filename, int is_last);

// Sauvegarde le JSON sur disque
int manifest_save(manifest *m, const char *output_path);

void manifest_free(manifest *m);

#endif