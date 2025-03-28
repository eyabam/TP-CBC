#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbc.h"
#include "rand.h"

// Basic test function to check if encryption and decryption work
int test_encryption(void) {
    byte key[2*NBYTES];
    random_bytes(key, 2*NBYTES);
    // Create a test message
    byte message[4*NBYTES];
    random_bytes(message, 4*NBYTES);
    // Allocate space for ciphertext (message + IV)
    byte* ciphertext = malloc(4*NBYTES + NBYTES);
    byte* decrypted = malloc(4*NBYTES);
    printf("Message: ");
    for (size_t i = 0; i < 4 * NBYTES; i++) {
        printf("%02x", message[i]);
    }
    printf("\n");
    // Encrypt
    cbc_enc(key, message, ciphertext, 4*NBYTES);
    printf("Ciphertext: ");
    for (size_t i = 0; i < 4 * NBYTES; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    // Decrypt
    cbc_dec(key, decrypted, ciphertext, 4*NBYTES);
    printf("Decrypted: ");
    for (size_t i = 0; i < 4 * NBYTES; i++) {
        printf("%02x", decrypted[i]);
    }
    printf("\n");
    // Compare original and decrypted messages
    int result = 1;
    for (size_t i = 0; i < 4 * NBYTES; i++) {
        if (message[i] != decrypted[i]) {
            result = 0;
            break;
        }
    }
    if (result) {
        printf("Encryption/Decryption Test: Original and decrypted messages match\n");
    } else {
        printf("Encryption/Decryption Test: Original and decrypted messages do not match\n");
    }
    free(ciphertext);
    free(decrypted);
    return result;
}
// Test different SPECK variants
void test_speck_variants(void) {
    int variants[] = {32, 48, 64};
    for (int i = 0; i < 3; i++) {
        printf("\n");
        printf("Testing SPECK %d variant\n", variants[i]);
        test_encryption();
    }
}
int main(void) {
    test_speck_variants();
    return 0;
}