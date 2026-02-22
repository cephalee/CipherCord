#ifndef SEND_H
#define SEND_H

#include <stdio.h>

int send_chunk_discord( const char *webhook, const char *data, size_t data_size, int chunk_index, int is_last);

#endif