#include <stdio.h>
#include <stdlib.h>
#include "attack.h"
#include "speck.h"

#define PRINT(label, data, len) do { \
    printf("%s: ", label); \
    for (size_t _i = 0; _i < (len); _i++) \
        printf("%02x ", (data)[_i]); \
    printf("\n"); } while(0)

int main(void) {
    const int attempts = 20;
    int collisions_found = 0;    
    printf("Starting CBC attack test (%d attempts)\n", attempts);
    for (int i = 0; i < attempts; i++) {
        byte *m = NULL;
        byte *c = NULL;
        size_t collision[2] = {SIZE_MAX, SIZE_MAX};
        byte xor[NBYTES] = {0};
        size_t mlen = challenge(&m, &c);
        attack(c, mlen + NBYTES, collision, xor);
        printf("Attempt %d/%d: ", i+1, attempts);
        if (collision[0] != SIZE_MAX && collision[1] != SIZE_MAX) {
            printf("Collision [%zu ↔ %zu]\n", collision[0], collision[1]);
            PRINT("  XOR", xor, NBYTES);
            collisions_found++;
        } else {
            printf("No collision found\n");
        }
        free(m);
        free(c);
    }
    printf("\nFinal result:\n");
    printf("Success rate of the attack: %.1f%% (%d/%d)\n", 
           (collisions_found * 100.0)/attempts, 
           collisions_found, 
           attempts);    
    return EXIT_SUCCESS;
}
