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
- **Decryption Validation**: 
  - Original message perfectly recovered
  - No information loss during encryption/decryption

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
- **Decryption Validation**:
  - Consistent message recovery
  - Demonstrates adaptability to different block sizes

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
- **Decryption Validation**:
  - Full message recovery maintained
  - Shows scalability of the SPECK cipher design

# Exercise 2: Testing SPECK Block Cipher Variants
