#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbc.h"
#include "rand.h"

// Basic test function to check if encryption and decryption work
int test_encryption(void) {
    // Define a test key
    byte key[2*NBYTES];
    random_bytes(key, 2*NBYTES);

    // Create a test message
    byte message[4*NBYTES];
    random_bytes(message, 4*NBYTES);

    // Allocate space for ciphertext (message + IV)
    byte* ciphertext = malloc(4*NBYTES + NBYTES);
    byte* decrypted = malloc(4*NBYTES);

    // Encrypt
    cbc_enc(key, message, ciphertext, 4*NBYTES);

    // Decrypt
    cbc_dec(key, decrypted, ciphertext, 4*NBYTES);

    // Compare original and decrypted messages
    int result = memcmp(message, decrypted, 4*NBYTES) == 0;

    // Print result
    if (result) {
        printf("Encryption/Decryption Test: PASS\n");
    } else {
        printf("Encryption/Decryption Test: FAIL\n");
    }

    // Free memory
    free(ciphertext);
    free(decrypted);

    return result;
}

// Test different SPECK variants
void test_speck_variants(void) {
    // Test block sizes
    int variants[] = {32, 48, 64};

    for (int i = 0; i < 3; i++) {
        printf("Testing SPECK %d variant\n", variants[i]);
        
        // Simulate changing block size (in a real scenario, you'd recompile)
        // Note: In actual implementation, you'd use -DBLOCKSIZE flag
        test_encryption();
    }
}

int main(void) {
    // Run tests
    test_speck_variants();

    return 0;
}