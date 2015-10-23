#ifndef CIPHERBLOCKCHAIN_HPP
#define CIPHERBLOCKCHAIN_HPP

#include <cstdint>
#include "Block.hpp"

/*
    CipherBlockChain
    
    CBC mode-of-operation XOR's all output with the previous round's ciphertext
    (with the exception of the first round, in which case it is XOR'ed with IV). 
    Trivially, this happens before encryption and after decryption. Template is
    strange, but SIZE must match BLOCKCIPHER's templated SIZE.
*/

template <class BLOCKCIPHER, uint8_t SIZE>
class CipherBlockChain {
    
    protected:
    
        BLOCKCIPHER cipher;
        Block<SIZE> key;
        Block<SIZE> previous;
        
    public:
    
        CipherBlockChain ( Block<SIZE> key, Block<SIZE> iv ) {
            this->key = key;
            this->previous = iv;
        }
        
        Block<SIZE> encrypt ( Block<SIZE> plaintext ) {
            this->previous = cipher.encrypt(
                plaintext ^ this->previous, this->key
            );
            return this->previous;
        }
        
        Block<SIZE> decrypt ( Block<SIZE> ciphertext ) {
            Block<SIZE> previousPrevious = this->previous;
            this->previous = ciphertext;
            return cipher.decrypt( ciphertext, this->key ) ^ previousPrevious;
        }
    
};

#endif
