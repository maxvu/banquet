#ifndef BANQUET_HPP
#define BANQUET_HPP
#define BANQUET_ROUNDCOUNT     13
#define BANQUET_HASHROUNDCOUNT 55691

#include <cstdint>
#include <cstdio>
#include "Block.hpp"
#include "BlockCipher.hpp"

/*
    Banquet
    
    48-bit block cipher. It has three round operations, in order:
    
        1. XOR buffer with cipher key
        2. Rotate bytes in buffer one to the right.
        3. Substitute bytes in the buffer using the S-box.
*/

class Banquet : public BlockCipher<6> {
    
    protected:
    
        // S-box
        uint8_t sbox[256] = {
            0x51, 0xC8, 0x0A, 0x5B, 0xCD, 0x8C, 0x8F, 0x4F,
            0x88, 0x40, 0xD2, 0x83, 0xD4, 0x95, 0x9F, 0x1F,
            0x41, 0xD0, 0x9A, 0x82, 0xD5, 0x8D, 0xDE, 0x4E,
            0x10, 0x01, 0x0B, 0x5A, 0x0D, 0x1D, 0x86, 0x5F,
            0xA9, 0xF8, 0x23, 0xEB, 0x35, 0x6C, 0x67, 0xB7,
            0xF0, 0xA1, 0x6A, 0xAB, 0xED, 0x3D, 0xBE, 0xAE,
            0x68, 0x69, 0x3A, 0x2B, 0xBC, 0x3C, 0x6F, 0x26,
            0xF9, 0x71, 0xEA, 0xFA, 0xB5, 0x7C, 0x27, 0xEF,
            0xC0, 0x59, 0x43, 0x13, 0x45, 0x04, 0x16, 0xC7,
            0x09, 0xD8, 0x03, 0x93, 0x0C, 0xC5, 0x07, 0x0E,
            0x99, 0xD9, 0x9B, 0x12, 0x4C, 0x1C, 0xCF, 0x5E,
            0x80, 0xC9, 0x92, 0x4A, 0x85, 0xC4, 0x17, 0x97,
            0xB1, 0x60, 0xE2, 0x3B, 0x7D, 0xA5, 0xA6, 0x37,
            0x61, 0x70, 0xF3, 0xB3, 0xBD, 0xFC, 0xBF, 0xE6,
            0xB9, 0x30, 0x72, 0x22, 0x74, 0xFD, 0x66, 0x76,
            0x28, 0xE0, 0xA2, 0xB2, 0xB4, 0xAC, 0xF7, 0xA7,
            0x98, 0x08, 0x42, 0xDA, 0xCC, 0x84, 0x8E, 0x56,
            0x50, 0x11, 0xC3, 0xCB, 0x44, 0x5C, 0xCE, 0x06,
            0x48, 0xC1, 0x8B, 0xC2, 0xDD, 0x9D, 0x9E, 0xDF,
            0x18, 0x90, 0x4B, 0xD3, 0x55, 0x94, 0x47, 0xD6,
            0xB0, 0x21, 0x2A, 0xA3, 0x34, 0x64, 0x36, 0xE7,
            0xA0, 0xE1, 0xFB, 0xAA, 0x2D, 0xA4, 0x7E, 0x6E,
            0x29, 0x20, 0x62, 0xBB, 0x25, 0xF4, 0x3E, 0x3F,
            0xE8, 0xA8, 0x33, 0x63, 0xF5, 0x75, 0xF6, 0xFF,
            0x49, 0x89, 0x52, 0x1A, 0x54, 0x9C, 0x46, 0x96,
            0x19, 0xD1, 0x02, 0xDB, 0x4D, 0x05, 0x87, 0xD7,
            0x91, 0x81, 0x8A, 0xCA, 0x5D, 0xDC, 0x57, 0x1E,
            0x58, 0x00, 0x53, 0x1B, 0x15, 0x14, 0xC6, 0x0F,
            0x38, 0x39, 0xBA, 0xF2, 0xE4, 0xAD, 0xEE, 0x2F,
            0x31, 0x78, 0x32, 0x6B, 0x6D, 0x65, 0x2E, 0x7F,
            0xB8, 0xE9, 0x7B, 0x7A, 0xEC, 0x2C, 0xB6, 0x77,
            0xF1, 0x79, 0xE3, 0x73, 0x24, 0xE5, 0xAF, 0xFE,
        };    
        
        // Inverted S-box ( sboxInverse[ sbox[ i ] ] == i for i in 0..255 )
        uint8_t sboxInverse[256] = {
            0xD9, 0x19, 0xCA, 0x4A, 0x45, 0xCD, 0x8F, 0x4E,
            0x81, 0x48, 0x02, 0x1A, 0x4C, 0x1C, 0x4F, 0xDF,
            0x18, 0x89, 0x53, 0x43, 0xDD, 0xDC, 0x46, 0x5E,
            0x98, 0xC8, 0xC3, 0xDB, 0x55, 0x1D, 0xD7, 0x0F,
            0xB1, 0xA1, 0x73, 0x22, 0xFC, 0xB4, 0x37, 0x3E,
            0x78, 0xB0, 0xA2, 0x33, 0xF5, 0xAC, 0xEE, 0xE7,
            0x71, 0xE8, 0xEA, 0xBA, 0xA4, 0x24, 0xA6, 0x67,
            0xE0, 0xE1, 0x32, 0x63, 0x35, 0x2D, 0xB6, 0xB7,
            0x09, 0x10, 0x82, 0x42, 0x8C, 0x44, 0xC6, 0x9E,
            0x90, 0xC0, 0x5B, 0x9A, 0x54, 0xCC, 0x17, 0x07,
            0x88, 0x00, 0xC2, 0xDA, 0xC4, 0x9C, 0x87, 0xD6,
            0xD8, 0x41, 0x1B, 0x03, 0x8D, 0xD4, 0x57, 0x1F,
            0x61, 0x68, 0xB2, 0xBB, 0xA5, 0xED, 0x76, 0x26,
            0x30, 0x31, 0x2A, 0xEB, 0x25, 0xEC, 0xAF, 0x36,
            0x69, 0x39, 0x72, 0xFB, 0x74, 0xBD, 0x77, 0xF7,
            0xE9, 0xF9, 0xF3, 0xF2, 0x3D, 0x64, 0xAE, 0xEF,
            0x58, 0xD1, 0x13, 0x0B, 0x85, 0x5C, 0x1E, 0xCE,
            0x08, 0xC1, 0xD2, 0x92, 0x05, 0x15, 0x86, 0x06,
            0x99, 0xD0, 0x5A, 0x4B, 0x9D, 0x0D, 0xC7, 0x5F,
            0x80, 0x50, 0x12, 0x52, 0xC5, 0x95, 0x96, 0x0E,
            0xA8, 0x29, 0x7A, 0xA3, 0xAD, 0x65, 0x66, 0x7F,
            0xB9, 0x20, 0xAB, 0x2B, 0x7D, 0xE5, 0x2F, 0xFE,
            0xA0, 0x60, 0x7B, 0x6B, 0x7C, 0x3C, 0xF6, 0x27,
            0xF0, 0x70, 0xE2, 0xB3, 0x34, 0x6C, 0x2E, 0x6E,
            0x40, 0x91, 0x93, 0x8A, 0x5D, 0x4D, 0xDE, 0x47,
            0x01, 0x59, 0xD3, 0x8B, 0x84, 0x04, 0x8E, 0x56,
            0x11, 0xC9, 0x0A, 0x9B, 0x0C, 0x14, 0x9F, 0xCF,
            0x49, 0x51, 0x83, 0xCB, 0xD5, 0x94, 0x16, 0x97,
            0x79, 0xA9, 0x62, 0xFA, 0xE4, 0xFD, 0x6F, 0xA7,
            0xB8, 0xF1, 0x3A, 0x23, 0xF4, 0x2C, 0xE6, 0x3F,
            0x28, 0xF8, 0xE3, 0x6A, 0xB5, 0xBC, 0xBE, 0x7E,
            0x21, 0x38, 0x3B, 0xAA, 0x6D, 0x75, 0xFF, 0xBF,
        };
        
    public:
        
        // Perform substitution.
        Block<6> substitute ( Block<6> block ) {
            for ( uint8_t i = 0; i < 6; i++ )
                block[ i ] = sbox[ block[ i ] ];
            return block;
        }
        
        // Undo substitution.
        Block<6> unsubstitute ( Block<6> block ) {
            for ( uint8_t i = 0; i < 6; i++ )
                block[ i ] = sboxInverse[ block[ i ] ];
            return block;
        }
        
        // Perform encryption on one block.
        Block<6> encrypt ( Block<6> plaintext, Block<6> key ) {
            Block<6> ciphertext( plaintext );
            for ( unsigned i = 0; i < BANQUET_ROUNDCOUNT; i++ )
                ciphertext = substitute( ( ciphertext ^ key ) >> 1 );
            return ciphertext;
        }
        
        // Perform decryption on one block.
        Block<6> decrypt ( Block<6> ciphertext, Block<6> key ) {
            Block<6> plaintext( ciphertext );
            for ( unsigned i = 0; i < BANQUET_ROUNDCOUNT; i++ )
                plaintext = ( unsubstitute( plaintext ) << 1 ) ^ key;
            return plaintext;
        }
        
        // Hash a C-string into a key block.
        static Block<6> hashKey ( const char * key ) {
            uint8_t keyInit[] = { 0x1B, 0x48, 0x0A, 0x4A, 0xE5, 0x6D };
            Block<6> hash( keyInit );
            
            for ( unsigned long i = 0; i < BANQUET_HASHROUNDCOUNT; i++ ) {
                for ( const char * k = key; *k; k++ ) {
                    // 31, 19, 17, 5, 3, 2
                    hash[0] = ( hash[0] << 5 ) - hash[1] + *k;
                    hash[1] = ( hash[1] << 4 ) + ( hash[1] << 1 ) + *k;
                    hash[2] = ( hash[2] << 4 ) + hash[2] - *k;
                    hash[3] = ( hash[3] << 2 ) + hash[3] - *k;
                    hash[4] = ( hash[4] << 2 ) - hash[4] + *k;
                    hash[5] = ( hash[5] << 1 ) + *k;
                    hash = hash >> 1;
                }
            }
            
            return hash;
        }
        
};

#endif
