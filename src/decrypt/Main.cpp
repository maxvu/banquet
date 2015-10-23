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
    
    char stringKey[256];
    IO::readFromStdin( stringKey, 255, "       key: " );
    std::cout << std::endl;
    Block<6> key = Banquet::hashKey( stringKey );
    
    Block<1> paddingMarker;
    Block<6> iv;
    
    ciphertextFile >> iv;
    ciphertextFile >> paddingMarker;
    
    std::cout << "  key hash: " << key.dump() << std::endl;
    std::cout << "        iv: " << iv.dump()  << std::endl;
    std::cout << "   padding: " << ( 6 - paddingMarker[0] ) % 6 << std::endl;

    CipherBlockChain<Banquet,6> cbc( key, iv );
    Block<6> buffer;
    while ( ciphertextFile.getNumBytesLeft() > 6 ) {
        try {
            ciphertextFile >> buffer;
            buffer = cbc.decrypt( buffer );
            plaintextFile << buffer;
        } catch ( const char * error ) {
            std::cout << "Something awful happened." << std::endl;
        }
    }
    
    // If the last block isn't written separately, then junk data that 
    // was previously padding bytes will be appended to the plaintext.
    ciphertextFile >> buffer;
    buffer = cbc.decrypt( buffer );
    plaintextFile.writeBytes( buffer.getData(), paddingMarker[0] );

    std::cout << std::endl
        << "  Wrote " << plaintextFile.getNumBytesWritten()
        << " bytes to " << argv[2] << std::endl << std::endl;
    return 0;

}
