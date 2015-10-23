#include <iostream>
#include "../../lib/Block.hpp"
#include "../../lib/BlockCipher.hpp"
#include "../../lib/CipherBlockChain.hpp"
#include "../../lib/File.hpp"
#include "../../lib/Banquet.hpp"
#include "../../lib/Random.hpp"
#include "../../lib/IO.hpp"

int main ( int argc, char ** argv ) {
    
    std::cout << std::endl;
    
    if ( argc != 3 ) {
        std::cout << "  usage: " << argv[0] << " plaintext ciphertext-output";
        std::cout << std::endl;
        return 1;
    }
    
    InputFile plaintextFile;
    OutputFile ciphertextFile;
    
    try {
        plaintextFile.open( argv[1] );
    } catch ( const char * error ) {
        std::cout << "  ERROR: Couldn't open " << argv[1] << " for reading.";
        std::cout << std::endl;
        return 1;
    }
    
    try {
        ciphertextFile.open( argv[2] );
    } catch ( const char * error ) {
        std::cout << "  ERROR: Couldn't open " << argv[2] << " for writing.";
        std::cout << std::endl;
        return 1;
    }
    
    // Set aside a byte in the ciphertext to indicate to the decryptor how many
    // bytes we padded to the last block.
    Block<1> paddingMarker;
    paddingMarker[0] = plaintextFile.getNumBytesLeft() % 6;
    
    // Read a C-string key in from STDIN and hash it.
    char stringKey[256];
    IO::readFromStdin( stringKey, 255, "       key: " );
    std::cout << std::endl;
    Block<6> key = Banquet::hashKey( stringKey );
    
    // Generate a random IV.
    Block<6> iv = Random::generate<6>();
    
    std::cout << "  key hash: " << key.dump() << std::endl;
    std::cout << "        iv: " << iv.dump()  << std::endl;
    std::cout << "   padding: " << ( 6 - paddingMarker[0] ) % 6 << std::endl;
    
    // Write the IV block (6 bytes) and the padding marker (1 byte) out.
    ciphertextFile << iv << paddingMarker;
    
    // The CBC will carry ciphertext between rounds.
    CipherBlockChain<Banquet,6> cbc( key, iv );
    
    // Successively read in blocks from PT, encrypt, write to CT.
    Block<6> buffer;
    while ( plaintextFile ) {
        try {
            plaintextFile >> buffer;
            buffer = cbc.encrypt( buffer );
            ciphertextFile << buffer;
        } catch ( const char * error ) {
            std::cout << "Something awful happened." << std::endl;
        }
    }

    std::cout << std::endl
        << "  Wrote " << ciphertextFile.getNumBytesWritten()
        << " bytes to " << argv[2] << std::endl << std::endl;
    return 0;

}
