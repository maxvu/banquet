#ifndef BLOCKCIPHER_HPP
#define BLOCKCIPHER_HPP

#include <cstdint>
#include "Block.hpp"

/*
    BlockCipher
    
    Simple interface for a block cipher.
*/

template <uint8_t SIZE>
class BlockCipher {
    
        public:
    
            virtual Block<SIZE> encrypt (
                Block<SIZE> plaintext,
                Block<SIZE> key
            ) =0;
            
            virtual Block<SIZE> decrypt (
                Block<SIZE> ciphertext,
                Block<SIZE> key
            ) =0;
        
};

#endif
