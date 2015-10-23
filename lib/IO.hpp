#ifndef IO_HPP
#define IO_HPP

#include <cstdio>

/*
    IO
    
    A lonely wrapper for fgets().
*/

class IO {

    public:

        static void readFromStdin (
            char * buffer,
            unsigned long len,
            const char * prompt
        ) {
            if ( prompt ) 
                printf( "%s", prompt );
            strcpy( buffer, "" );
            if ( fgets ( buffer, len, stdin ) ) {
                unsigned long bytesRead = strlen( buffer );
                if ( buffer[ bytesRead - 1 ] == '\n' )
                    buffer[ bytesRead - 1 ] = '\0';
            }
        }

};

#endif
