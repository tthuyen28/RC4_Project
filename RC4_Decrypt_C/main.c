#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rc4.h"

int main() {
    const char *key = "mysecretkey";
    // Đây là ciphertext hex bạn có được từ chương trình encrypt
    const char *hex_cipher = "A2B216D7A9696BFEA97B5B4F892BB0C7293AC33A51C1164A27EE156737B9291E414FA9C62A36657ABF09";

    int decoded_len;
    size_t hexlen = strlen(hex_cipher);
    if (hexlen % 2 != 0) {
        fprintf(stderr, "Hex string length must be even\n");
        return 1;
    }
    decoded_len = hexlen / 2;

    unsigned char *cipher_bytes = (unsigned char *)malloc(decoded_len);
    if (!cipher_bytes) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (hex_decode(hex_cipher, cipher_bytes) < 0) {
        fprintf(stderr, "Hex decode error\n");
        free(cipher_bytes);
        return 1;
    }

    unsigned char *plaintext = (unsigned char *)malloc(decoded_len + 1);
    if (!plaintext) {
        fprintf(stderr, "Memory allocation failed\n");
        free(cipher_bytes);
        return 1;
    }

    RC4_CTX ctx;
    rc4_init(&ctx, (const unsigned char *)key, strlen(key));
    rc4_process(&ctx, cipher_bytes, plaintext, (size_t)decoded_len);

    plaintext[decoded_len] = '\0';  // đảm bảo kết thúc chuỗi

    printf("Decrypted text: %s\n", (char *)plaintext);

    free(cipher_bytes);
    free(plaintext);

    return 0;
}
