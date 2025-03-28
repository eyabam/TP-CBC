# Exercise 1: Testing SPECK Block Cipher Variants

### Observations for 32/64
- **Block Size**: 8 * 4 = 32 bits (4 bytes)
- **Key Size**: 16 * 4 = 64 bits (8 bytes)
- **Key Characteristics**: 
  - Random key generation shows variability
  - Hexadecimal representation of key
- **Message Block**: 4 bytes long
- **Encryption Process**: 
  - Transforms 4-byte message block
  - Produces a 4-byte ciphertext block

### Observations for 48/96
- **Block Size**: 8 * 6 = 48 bits (6 bytes)
- **Key Size**: 16 * 6 = 96 bits (12 bytes)
- **Key Characteristics**:
  - Longer key compared to 32/64 variant
  - Increased cryptographic complexity
- **Message Block**: 6 bytes long
- **Encryption Process**:
  - Handles 6-byte message blocks
  - Generates 6-byte ciphertext blocks

### Observations for 64/128
- **Block Size**: 8 * 8 = 64 bits (8 bytes)
- **Key Size**: 16 * 8 = 128 bits (16 bytes)
- **Key Characteristics**:
  - Largest key in the SPECK family tested
  - Provides highest level of cryptographic security
- **Message Block**: 8 bytes long
- **Encryption Process**:
  - Processes 8-byte message blocks
  - Produces 8-byte ciphertext blocks

# Exercise 2: CBC Mode of Operation

## Problem Description

### 1. **CBC Mode of Operation**
**CBC** is a mode of operation for block ciphers where each ciphertext block depends on the current plaintext block as well as the previous ciphertext block. This chaining mechanism ensures that even identical plaintext blocks will produce different ciphertext blocks when encrypted with the same key.

### 2. **Task Details**
- **`cbc_enc` Function**: This function performs encryption using CBC mode. It takes a 2n-bit key, a message `m`, and its byte length `mlen`, and fills the ciphertext `c` by encrypting the message in blocks.
- **`cbc_dec` Function**: This function performs decryption using CBC mode. It takes the 2n-bit key, a ciphertext `c`, and the byte length of the corresponding message `mlen`, and returns the original message by decrypting the ciphertext.

### 1. **`cbc_enc` Function**

- **Purpose**: This function encrypts a message `m` using **CBC mode** and the **SPECK** block cipher. The message is processed in blocks of `NBYTES` bytes.
- **Parameters**: 
    - **`k[2*NBYTES]`**: The encryption key (2n bits).
    - **`m`**: The message to be encrypted (input).
    - **`c`**: The resulting ciphertext (output).
    - **`mlen`**: The length of the message `m` in bytes.
- **How It Works**:
    - The function begins by generating a random **IV (Initialization Vector)** and storing it in the ciphertext `c` at the beginning.
    - Then, it encrypts the message in blocks of size `NBYTES`, where each block is XORed with the previous ciphertext block before being encrypted.

### 2. **`cbc_dec` Function**
- **Purpose**: This function decrypts a ciphertext `c` using CBC mode and the SPECK block cipher.
- **Parameters**:
  - `k[2*NBYTES]`: The decryption key (2n bits).
  - `m`: The decrypted message (output).
  - `c`: The ciphertext (input).
  - `mlen`: The length of the message `m` in bytes.
- **How It Works**:
  - The IV is extracted from the beginning of the ciphertext.
  - The ciphertext is decrypted block by block. After decryption, each block is XORed with the previous ciphertext block (or the IV for the first block) to retrieve the original message.

### 3. Size of the Ciphertext
The size of the ciphertext is equal to the size of the message plus the size of the IV. Since we store the IV at the beginning of the ciphertext, the total length of the ciphertext will be `mlen + NBYTES`, where `NBYTES` is the size of the IV.

### 4. Decryption Check
You need to verify that the decryption of a ciphertext correctly returns the original message. We will test the CBC decryption against the CBC encryption to ensure correctness.

## Code Walkthrough

### `cbc_enc` Function
- **Initialization**: The function begins by generating a random IV and storing it in the ciphertext.
- **Encryption**: The message is divided into blocks of `NBYTES`, and each block is XORed with the previous ciphertext block (or IV for the first block) before being encrypted using `speck_enc`.
- **Randomization**: The use of a random IV ensures that the encryption is non-deterministic, i.e., encrypting the same message multiple times will produce different ciphertexts.

### `cbc_dec` Function
- **Extract IV**: The IV is extracted from the beginning of the ciphertext.
- **Decryption**: The ciphertext is decrypted block by block. After decryption, each block is XORed with the previous ciphertext block (or IV for the first block) to retrieve the original message.

# Exercise 3: The Birthday Attack

## 1. The Birthday Attack for CBC Mode
The birthday attack in CBC mode exploits the birthday paradox, which suggests that given a sufficiently large number of random ciphertext blocks, the likelihood of finding two blocks that are the same (collisions) increases significantly.

### Key Concept
The attack works by finding two identical ciphertext blocks, which indicates that the corresponding plaintext blocks are also identical due to the XOR operation in CBC mode.

### Collision Detection
The attacker checks for collisions in the ciphertext blocks and finds the corresponding plaintext blocks that produce the same ciphertext.

## Implementation Details

### 1. `challenge` Function
- **Purpose**: This function generates a random message `m`, encrypts it using a random key, and returns the message length `mlen`.
- **Parameters**:
  - `m`: Pointer to the message (output).
  - `c`: Pointer to the ciphertext (output).
- **Implementation**:
  - A random message `m` is generated with a size determined by `NBLOCKS * NBYTES`.
  - A random key and IV (Initialization Vector) are generated.
  - The ciphertext is computed by encrypting the message in CBC mode using the random key and IV.

### 2. `attack` Function
- **Purpose**: This function implements the birthday attack for CBC mode. It tries to find two ciphertext blocks that are the same and returns the indices of those blocks and their XOR result.
- **Parameters**:
  - `c`: The ciphertext.
  - `clen`: The length of the ciphertext.
  - `collision[2]`: An array to hold the indices of the colliding blocks.
  - `xor[NBYTES]`: An array to store the XOR of the colliding blocks of plaintext.
- **Implementation**:
  - We create a hash table to store the hash of each block.
  - We use linear probing to find collisions in the ciphertext.
  - If a collision is found, the XOR of the corresponding plaintext blocks is computed.

## Compilation and Execution

- Compile the CBC Test:

  - make test_cbc

- Compile the Birthday Attack Test for Block Size 32:

  - make test_attack_32

- Compile the Birthday Attack Test for Block Size 48:

  - make test_attack_48

- Compile the Birthday Attack Test for Block Size 64:

  - make test_attack_64

- Compile All Tests (Optional):

  - make all

- Clean Up Compiled Executables:

  - make clean




