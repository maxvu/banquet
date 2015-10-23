#ifndef FILE_HPP
#define FILE_HPP

#include <cstdint>
#include <cstdio>
#include "Block.hpp"

/*
    File
    InputFile
    OutputFile
    
    File handling that operates on Blocks. Uses C functions for access because 
    C++ seems to be tied on wchar. Does no appropriate error handling. Input-
    and Output- keep track of bytes going through, written or read.
*/

class File {
    
    protected:
    
        FILE * fh;
        
    public:
    
        ~File () {
            if ( this->fh )
                fclose( this->fh );
        }
        
};

class InputFile : public File {
    
    unsigned long long bytesLeft;
        
    public:
    
        InputFile () {
            this->fh = 0;
        }
    
        InputFile & open ( const char * filename ) {
            this->fh = 0;
            if ( !( this->fh = fopen( filename, "rb" ) ) ) {
                throw "Couldn't open file for reading.";
            }
            
            fseek( this->fh, 0, SEEK_END );
            this->bytesLeft = ftell( this->fh );
            fseek( this->fh, 0, SEEK_SET );
            return *this;
        }
        
        template <uint8_t SIZE>
        Block<SIZE> & operator>> ( Block<SIZE> & block ) {
            this->bytesLeft -= fread(
                block.getData(),
                sizeof( uint8_t ),
                block.getSize(),
                this->fh
            );
            if ( ferror( this->fh ) )
                throw "Encountered error reading from file.";
            return block;
        }
        
        unsigned long long getNumBytesLeft () {
            return this->bytesLeft;
        }
        
        explicit operator bool () const {
            return this->bytesLeft;
        }
    
};

class OutputFile : public File {
    
    protected:
    
        unsigned long long bytesWritten;
        
    public:
    
        OutputFile () {
            this->fh = 0;
            this->bytesWritten = 0;
        }
    
        OutputFile & open ( const char * filename ) {
            this->fh = 0;
            if ( !( this->fh = fopen( filename, "wb" ) ) )
                throw "Couldn't open file for writing.";
            return *this;
        }
        
        template <uint8_t SIZE>
        OutputFile & operator<< ( Block<SIZE> & block ) {
            this->bytesWritten += fwrite(
                block.getData(),
                sizeof( uint8_t ),
                block.getSize(),
                this->fh
            );
            if ( ferror( this->fh ) )
                throw "Failed to complete a write on File.";
            return *this;
        }
        
        OutputFile & writeBytes ( uint8_t * bytes, unsigned long len ) {
            this->bytesWritten += fwrite(
                bytes,
                sizeof( uint8_t ),
                len,
                this->fh
            );
            if ( ferror( this->fh ) )
                throw "Failed to complete a write on File.";
            return *this;
        }
        
        unsigned long long getNumBytesWritten () {
            return this->bytesWritten;
        }
    
};

#endif
