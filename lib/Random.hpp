#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <ctime>
#include <cstdint>

/*
    Random
    
    Generate random binary data.
*/

class Random {

    public:

        template<uint8_t SIZE>
        static Block<SIZE> generate () {
            Block<SIZE> random;
            srand( ( unsigned int ) time( 0 ) );
            for ( uint8_t i = 0; i < SIZE; i++ )
                random[ i ] = rand();
            return random;
        }

};

#endif
