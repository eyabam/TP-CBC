CC = gcc

CFLAGS = -O2 -Wall -Werror

all: test_cbc \
    test_attack_32 test_attack_48 test_attack_64

test_cbc:
	$(CC) $(CFLAGS) rand.c speck.c cbc.c test_cbc.c -o test_cbc

test_attack_32:
	$(CC) $(CFLAGS) rand.c speck.c attack.c test_attack.c -o $@ -DBLOCKSIZE=32

test_attack_48:
	$(CC) $(CFLAGS) rand.c speck.c attack.c test_attack.c -o $@ -DBLOCKSIZE=48

test_attack_64:
	$(CC) $(CFLAGS) rand.c speck.c attack.c test_attack.c -o $@ -DBLOCKSIZE=64

clean:
	rm -f test_cbc \
		test_attack_32 test_attack_48 test_attack_64

.PHONY: all clean