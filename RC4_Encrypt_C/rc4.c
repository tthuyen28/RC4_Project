#include "rc4.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Hoán đổi hai byte
static void rc4_swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

// KSA: khởi tạo bảng S dựa trên key
void rc4_init(RC4_CTX *ctx, const unsigned char *key, size_t keylen) {
    size_t i;
    int j = 0;

    for (i = 0; i < 256; i++) {
        ctx->S[i] = (unsigned char)i;
    }
    ctx->i = 0;
    ctx->j = 0;

    for (i = 0; i < 256; i++) {
        j = (j + ctx->S[i] + key[i % keylen]) & 0xFF;
        rc4_swap(&ctx->S[i], &ctx->S[j]);
    }
}

// PRGA + XOR input với keystream
void rc4_process(RC4_CTX *ctx,
                 const unsigned char *input,
                 unsigned char *output,
                 size_t len) {
    size_t k;
    for (k = 0; k < len; k++) {
        ctx->i = (ctx->i + 1) & 0xFF;
        ctx->j = (ctx->j + ctx->S[ctx->i]) & 0xFF;
        rc4_swap(&ctx->S[ctx->i], &ctx->S[ctx->j]);
        unsigned char t = (ctx->S[ctx->i] + ctx->S[ctx->j]) & 0xFF;
        unsigned char keystream_byte = ctx->S[t];
        output[k] = input[k] ^ keystream_byte;
    }
}

// Mã hoá dữ liệu nhị phân sang chuỗi hex
void hex_encode(const unsigned char *data, size_t len, char *hex_out) {
    const char *hex_digits = "0123456789ABCDEF";
    size_t i;
    for (i = 0; i < len; i++) {
        unsigned char b = data[i];
        hex_out[2*i]     = hex_digits[(b >> 4) & 0xF];
        hex_out[2*i + 1] = hex_digits[b & 0xF];
    }
    hex_out[2 * len] = '\0';
}

// Giải mã chuỗi hex sang dữ liệu nhị phân
int hex_decode(const char *hex, unsigned char *data_out) {
    size_t hexlen = strlen(hex);
    if (hexlen % 2 != 0) return -1;
    size_t i;
    for (i = 0; i < hexlen / 2; i++) {
        unsigned int byte;
        if (sscanf(hex + 2*i, "%2X", &byte) != 1) {
            return -1;
        }
        data_out[i] = (unsigned char)byte;
    }
    return (int)(hexlen / 2);
}
