#include <stdio.h>     
#include <stdlib.h>
#include <string.h>
#include "rc4.h"

int main() {
    const char *key = "mysecretkey";  // bạn có thể đổi key này
    const char *plaintext = "Hanoi University of Science and Technology";

    size_t textlen = strlen(plaintext);

    unsigned char *cipher = (unsigned char *)malloc(textlen);
    if (!cipher) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    RC4_CTX ctx;
    rc4_init(&ctx, (const unsigned char *)key, strlen(key));

    rc4_process(&ctx, (const unsigned char *)plaintext, cipher, textlen);

    // chuyển ciphertext sang hex để dễ hiển thị
    char *hex_out = (char *)malloc(2 * textlen + 1);
    if (!hex_out) {
        fprintf(stderr, "Memory allocation failed\n");
        free(cipher);
        return 1;
    }
    hex_encode(cipher, textlen, hex_out);

    printf("Ciphertext (hex): %s\n", hex_out);

    free(cipher);
    free(hex_out);

    return 0;
}
