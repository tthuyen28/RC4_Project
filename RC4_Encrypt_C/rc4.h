#ifndef RC4_H
#define RC4_H

#include <stddef.h>  // để có size_t

typedef struct {
    unsigned char S[256];
    int i, j;
} RC4_CTX;

void rc4_init(RC4_CTX *ctx, const unsigned char *key, size_t keylen);
void rc4_process(RC4_CTX *ctx,
                 const unsigned char *input,
                 unsigned char *output,
                 size_t len);
void hex_encode(const unsigned char *data, size_t len, char *hex_out);
int hex_decode(const char *hex, unsigned char *data_out);

#endif /* RC4_H */
