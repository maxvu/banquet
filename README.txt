
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
        
        Recover the plaintext message encrypted in GOAL.PNG.ENC.
        
    DETAILS
    
        BANQUET is a block cipher that operates on 48-bit blocks using a 48-bit
        key. Provided is a C/C++ implementation of it operating in Cipher Block 
        Chaining (CBC) mode. The included MAKEFILE will generate three programs:
        BQ-ENCRYPT, BQ-DECRYPT and BQ-SOLUTION. BQ-ENCRYPT will perform 
        encryption using BANQUET and BQ-DECRYPT will perform the inverse.
        BQ-SOLUTION is provided as a convenience.
        
        A file encrypted with BQ-ENCRYPT has the following structure:
        
        +------+-+------+------+------
        |  IV  |M|  C0  |  C1  | ...
        +------+-+------+------+------
        
        ...where IV is a randomly-generated initialization vector, M is a single
        padding marker byte (whose value is in 0..5), C0 is the first encrypted 
        block, C1 is the second and so on.
        
        Both BQ-ENCRYPT and BQ-DECRYPT accept as their arguments, first, the 
        name of the input file to read from and, second, the name of the output
        file to write to. Both accept a string key from standard input.
        
        GOAL.PNG.ENC is a PNG image that contains the English-language code 
        needed to certify completion.
        
    NOTES
    
        The code written in this package was written and tested using g++
        version 4.9.2 on a Linux system.
        
        If you liked this challenge or have comments or suggestions, contact me
        at { maxwell {dot] vu {at] gmail . com }.

