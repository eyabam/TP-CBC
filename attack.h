#ifndef ATTACK_H
#define ATTACK_H
#include "speck.h"


size_t challenge(byte** m, byte** c);
void attack(const byte* c, size_t clen, size_t collision[2], byte xor[NBYTES]);
#endif // ATTACK_H
