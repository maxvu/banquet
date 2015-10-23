#include <iostream>
#include <cstdio>
#include "../../lib/Block.hpp"
#include "../../lib/BlockCipher.hpp"
#include "../../lib/CipherBlockChain.hpp"
#include "../../lib/File.hpp"
#include "../../lib/Banquet.hpp"
#include "../../lib/Random.hpp"
#include "../../lib/IO.hpp"

int main ( int argc, char ** argv ) {

    if ( argc != 3 ) {
        std::cout << "  usage: " << argv[0] << " ciphertext plaintext-output";
        std::cout << std::endl;
        return 1;
    }
    
    InputFile ciphertextFile;
    OutputFile plaintextFile;
    
    try {
        ciphertextFile.open( argv[1] );
    } catch ( const char * error ) {
        std::cout << "  ERROR: Couldn't open " << argv[1] << " for reading.";
        std::cout << std::endl;
        return 1;
    }
    
    try {
        plaintextFile.open( argv[2] );
    } catch ( const char * error ) {
        std::cout << "  ERROR: Couldn't open " << argv[2] << " for writing.";
        std::cout << std::endl;
        return 1;
    }
    
    if (
        ciphertextFile.getNumBytesLeft() % 6 != 1
        || ciphertextFile.getNumBytesLeft() == 1
    ) {
        std::cout << "ERROR: Ciphertext " << argv[2] << " is malformed.";
        std::cout << std::endl;
        return 1;
    }
    
    std::cout << "???" << std::endl;
    
    return 0;

}
