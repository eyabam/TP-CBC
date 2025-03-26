#include <stdlib.h>
#include <string.h>
#include "cbc.h"
#include "rand.h"

void xor_array(const byte* m0, const byte* m1, byte* c, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        c[i] = m0[i] ^ m1[i];
    }
}

void cbc_enc(const byte k[2*NBYTES], const byte* m, byte* c, size_t mlen) {
    byte IV[NBYTES];
    random_bytes(IV, NBYTES);
    // Copy the IV to the beginning of the ciphertext
    for (size_t i = 0; i < NBYTES; i++) {
        c[i] = IV[i];
    }
    byte xor_block[NBYTES];
    byte enc_block[NBYTES];
    // Encrypt the message block by block
    for (size_t i = 0; i < mlen; i += NBYTES) {
        if (i == 0) {
            xor_array(m + i, IV, xor_block, NBYTES);
        } else {
            xor_array(m + i, c + i, xor_block, NBYTES);
        }        
        speck_enc(k, xor_block, enc_block);        
        for (size_t j = 0; j < NBYTES; j++) {
            c[i + NBYTES + j] = enc_block[j];
        }
    }
}

void cbc_dec(const byte k[2*NBYTES], byte* m, const byte* c, size_t mlen) {
    byte IV[NBYTES];
    for (size_t i = 0; i < NBYTES; i++) {
        IV[i] = c[i];
    }
    byte dec_block[NBYTES];    
    // Decrypt the ciphertext block by block
    for (size_t i = 0; i < mlen; i += NBYTES) {
        speck_dec(k, dec_block, c + i + NBYTES);       
        // XOR the decrypted block with the previous ciphertext block (or IV)
        if (i == 0) {
            xor_array(dec_block, IV, m + i, NBYTES);
        } else {
            xor_array(dec_block, c + i, m + i, NBYTES);
        }
    }
}