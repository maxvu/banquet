#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdint>
#include <cstring>
#include <sstream>
#include <iomanip>

/*
    Block
    
    A simple buffer aware of its size. Has many functions for access, operations
    involving blocks of identical size.
*/

template <uint8_t SIZE>
class Block {
    
    protected:
    
        const uint8_t size = SIZE;
        uint8_t data[ SIZE ];
        
    public:
    
        // Base constructor
        Block () {
            memset( this->data, 0, SIZE );
        }
        
        // Copy constructor
        Block ( const Block<SIZE> & other ) {
            memcpy( this->data, other.data, SIZE );
        }
        
        // Constructor, form from arbitrary memory.
        Block ( uint8_t * data ) {
            memcpy( this->data, data, SIZE );
        }
        
        // Get the pointer to the buffer. No qualifiers -- dangerous.
        uint8_t * getData () {
            return this->data;
        }
        
        uint8_t getSize () {
            return this->size;
        }
        
        Block<SIZE> & operator= ( const char * data ) {
            memcpy( this->data, data, SIZE );
            return *this;
        }
        
        Block<SIZE> & operator= ( const uint8_t * data ) {
            memcpy( this->data, data, SIZE );
            return *this;
        }
        
        Block<SIZE> & operator= ( Block<SIZE> other ) {
            memcpy( this->data, other.data, SIZE );
            return *this;
        }
        
        bool operator== ( Block<SIZE> other ) {
            return !memcmp( this->data, other.data, this->size );
        }
        
        // Rvalue subscript access
        const uint8_t & operator[] ( uint8_t idx ) const {
            if ( idx >= this->size )
                throw "Out-of-bounds access on Block data.";
            return this->data[ idx ];
        }
        
        // Lvalue subscript access
        uint8_t & operator[] ( const uint8_t idx ) {
            if ( idx >= this->size )
                throw "Out-of-bounds access on Block data.";
            return this->data[ idx ];
        }
        
        // Bitwise XOR with other
        Block<SIZE> operator^ ( const Block<SIZE> & other ) {
            Block<SIZE> xored( *this );
            for ( uint8_t i = 0; i < this->size; i++ )
                xored[ i ] ^= other[ i ];
            return xored;
        }
        
        // Bitwise AND with other
        Block<SIZE> operator& ( const Block & other ) {
            Block anded( *this );
            for ( uint8_t i = 0; i < this->size; i++ )
                anded[ i ] &= other[ i ];
            return anded;
        }
        
        // "Left shift" block. First byte becomes last.
        Block<SIZE> operator<< ( uint8_t n ) {
            n = n % this->size;
            uint8_t m = this->size - n;
            Block shifted( *this );
            memcpy( shifted.getData(), this->data + n, sizeof( uint8_t ) * m );
            memcpy( shifted.getData() + m, this->data, n );
            return shifted;
        }

        // "Right shift" block. Last byte becomes first.
        Block<SIZE> operator>> ( uint8_t n ) {
            return this->operator<<( this->size - n );
        }

        // Get something you can pipe to std::cout.
        // Doesn't reset stream flags, so numbers piped after it may be garbage.
        std::string dump () {
            std::stringstream dumpStream;
            dumpStream << std::hex << std::uppercase << std::setfill( '0' );
            for ( uint8_t i = 0; i < this->size; i++ ) {
                dumpStream << std::setw( 2 );
                dumpStream << static_cast<int>( this->data[ i ] );
                dumpStream << ' ';
            }
            return std::string( dumpStream.str() );
        }
        
    
};

#endif
