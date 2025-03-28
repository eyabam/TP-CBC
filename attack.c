#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "attack.h"   
#include "speck.h"    
#include "rand.h" 

enum { NBLOCKS = 1 << 16 }; // Default to 65536 blocks

// We define a structure to hold block data and its hash for the attack
typedef struct {
    uint8_t block_content[NBYTES];  
    size_t block_position;          
    uint32_t block_hash_value;
} BlockEntry;

// We compute the hash of a given block of size NBYTES
static inline uint32_t compute_block_hash(const uint8_t* block) {
    uint32_t hash_value = 0;
    for (size_t i = 0; i < NBYTES; ++i) {
        hash_value = (hash_value << 5) - hash_value + block[i]; 
    }
    return hash_value;
}

// We perform the attack to find a collision in the ciphertext
void attack(const byte* c, size_t clen, size_t collision[2], byte xor[NBYTES]){
    const size_t num_blocks = clen / NBYTES - 1;  
    BlockEntry* hash_table = calloc(num_blocks * 2, sizeof(BlockEntry));  // We Create a hash table to store the blocks
    if (!hash_table) { 
        collision[0] = collision[1] = SIZE_MAX; 
        for (size_t i = 0; i < NBYTES; ++i) {
            xor[i] = 0; 
        }
        return;
    }
    collision[0] = collision[1] = SIZE_MAX; 
    for (size_t i = 0; i < NBYTES; ++i) {
        xor[i] = 0;
    }
    for (size_t i = 0; i < num_blocks; ++i) {
        const uint8_t* block = c + (i + 1) * NBYTES;  
        const uint32_t block_hash_value = compute_block_hash(block); 
        size_t table_index = block_hash_value % (num_blocks * 2); 
        while (1) {
            // If the slot in the hash table is empty, store the block's data and hash
            if (hash_table[table_index].block_hash_value == 0) {
                hash_table[table_index].block_hash_value = block_hash_value;
                hash_table[table_index].block_position = i;
                for (size_t j = 0; j < NBYTES; ++j) {
                    hash_table[table_index].block_content[j] = block[j];
                }
                break;
            } 
            // If the block is already in the table (hash and content match), we found a collision
            else if (hash_table[table_index].block_hash_value == block_hash_value && 
                     ({ int equal = 1; for (size_t k = 0; k < NBYTES; ++k) { if (hash_table[table_index].block_content[k] != block[k]) { equal = 0; break; } } equal; }) == 1) {
                const size_t prev_index = hash_table[table_index].block_position;
                const size_t current_index = i;
                const uint8_t* prev_block = c + prev_index * NBYTES;  
                const uint8_t* curr_block = c + current_index * NBYTES; 
                // We XOR the two colliding blocks to find the difference
                for (size_t j = 0; j < NBYTES; ++j) {
                    xor[j] = prev_block[j] ^ curr_block[j];
                }
                collision[0] = prev_index;  
                collision[1] = current_index;  
                free(hash_table);
                return; 
            }
            // We use linear probing to find an empty slot in the hash table
            table_index = (table_index + 1) % (num_blocks * 2);
        }
    }
    free(hash_table);
}

// We generate a random challenge message and corresponding ciphertext
size_t challenge(byte** m, byte** c){
    const size_t message_len = NBLOCKS * NBYTES; 
    *m = malloc(message_len); 
    *c = malloc(message_len + NBYTES);
    uint8_t encryption_key[2 * NBYTES]; 
    uint8_t IV[NBYTES]; 
    random_bytes(*m, message_len);  
    random_bytes(encryption_key, sizeof(encryption_key)); 
    random_bytes(IV, sizeof(IV));
    // We copy the IV into the ciphertext
    for (size_t i = 0; i < NBYTES; ++i) {
        (*c)[i] = IV[i];
    }
    uint8_t prev_block[NBYTES]; 
    for (size_t i = 0; i < NBYTES; ++i) {
        prev_block[i] = IV[i]; 
    }
    // We encrypt the message block by block
    for (size_t i = 0; i < NBLOCKS; ++i) {
        uint8_t temp[NBYTES];
        for (size_t j = 0; j < NBYTES; ++j) {
            temp[j] = (*m)[i * NBYTES + j] ^ prev_block[j];
        }
        speck_enc(encryption_key, temp, (*c) + (i + 1) * NBYTES);  
        for (size_t j = 0; j < NBYTES; ++j) {
            prev_block[j] = (*c)[(i + 1) * NBYTES + j];  
        }
    }
    return message_len;
}
