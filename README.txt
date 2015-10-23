


          '||                                                   .   
           || ...   ....   .. ...     ... .  ... ...    ....  .||.  
           ||'  || '' .||   ||  ||  .'   ||   ||  ||  .|...||  ||   
           ||    | .|' ||   ||  ||  |.   ||   ||  ||  ||       ||   
           '|...'  '|..'|' .||. ||. '|..'||   '|..'|.  '|...'  '|.' 
                                         ||                         
                                        ''''                        
                                      
    FILES
    
        .
        ├── bin
        ├── data
        │   └── goal.png.enc                2d2f4fd8458d1e1562fdb7f526d089bd
        ├── lib
        │   ├── Banquet.hpp                 076c10714fceecc2b849c45a0787cefa
        │   ├── BlockCipher.hpp             baf2cf43b67f4a0a3def9a42b5937e15
        │   ├── Block.hpp                   e8609a196ea06dd2c7ddff54e9ed94a6
        │   ├── CipherBlockChain.hpp        3760e7d28ebb4a0626e27b6d22ad2c95
        │   ├── File.hpp                    a1812e859c715bbd59009b55e032ac2a
        │   ├── IO.hpp                      d9c014c62f550ecfc65c89f1b30e92d0
        │   └── Random.hpp                  61f0863fcbfc2452af2503d68a620774
        ├── Makefile                        d4515555ee34754faf53ecc82fb4d6ef
        ├── README.txt                      ...
        └── src
            ├── decrypt
            │   └── Main.cpp                05b608d2dc041e621923eb56d2e7a615
            ├── encrypt
            │   └── Main.cpp                d9759f314d2fd11ac5307ff8fb222155
            └── solution
                └── Main.cpp                4e990c35fd3d427373663d9efed1c64f
    
    CHALLENGE
    
        Given a block cipher with a significant cryptographic weakness
        introduced and an encrypted message, identify the weakness and exploit 
        it to recover the original message.
        
    DETAILS
    
        The encrypted message is contained in GOAL.PNG.ENC. The original message
        is a PNG image with a set of English-language codewords that can 
        certify completion.
    
        BANQUET is a block cipher that operates on 48-bit blocks with a 48-bit 
        key. The source of an C++ library implementing it can be found in LIB/,
        along with other tooling needed to build BIN/BQ-ENCRYPT and 
        BIN/BQ-DECRYPT, command-line programs that will (respectively) encrypt 
        and decrypt arbitrary files.
        
        In these programs, the cipher will operate in Cipher Block Chaining 
        (CBC) mode and will take two arguments: the name of an input file to 
        read from and the name of an output file to write to. The governing key 
        will be accepted via standard input.
        
        BQ-SOLUTION is a scaffold for a tentative solution and is provided as a
        convenience.
        
        All three programs can be built using the `make` command:
        
            make clean && make
            
        An example of BQ-ENCRYPT being built and run:
        
            $ make clean

                rm -f bin/*
                
            $ make
            
                g++ -Wall -std=c++11  src/encrypt/Main.cpp -o bin/bq-encrypt
                g++ -Wall -std=c++11  src/decrypt/Main.cpp -o bin/bq-decrypt
                g++ -Wall -std=c++11  src/solution/Main.cpp -o bin/bq-solution

            $ bin/bq-encrypt data/mymsg data/mymsg.enc < data/mykey

                   key:
              key hash: 10 81 D2 FB 75 D7
                    iv: DF 7B 60 7F FA 3D
               padding: 0

              Wrote 40894471 bytes to data/mymsg.enc
        
        A file encrypted with BQ-ENCRYPT has the following structure:
        
            +------+-+------+------+------     +------+
            |  IV  |M|  C0  |  C1  | ...       |    Cn|
            +------+-+------+------+------     +------+
        
        ...where IV is a randomly-generated initialization vector of size six 
        bytes, M is a single padding marker byte whose value is in 0..5, C0 is 
        the first encrypted block (six bytes), C1 is the second (six bytes) 
        and so on until Cn, the last block. All valid output should be greater
        than 5 bytes in size and should have a total file size congruent to one
        over modulo six.
        
    NOTES
    
        The code written in this package was written and tested using g++
        version 4.9.2 on a Linux system.
        
        If you liked this challenge or have comments or suggestions, contact me
        at { maxwell {dot] vu {at] gmail . com }.

