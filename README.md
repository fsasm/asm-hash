# asm-hash
A collection of common [cryptographic hash functions](https://en.wikipedia.org/wiki/Cryptographic_hash) written in C and assembly.

## Goal
This project began as an exercise to learn and practice assembly for ARMv6-CPUs and also to learn about cryptographic hash functions. Because these hash functions only need simple arithmetic and logical integer operations, it's a great exercise for beginners. In order to be portable and fast, everything is written in portable C and the critical parts are written in assembly. The assembly code is tested on the [Raspberry Pi](http://www.raspberrypi.org/). 

## Implemented Hash Algorithms
* MD5
* SHA-1
* SHA-2 (224, 256, 384, 512, 512/224 and 512/256 variants)
* Whirlpool
* BLAKE (224, 256 384 and 512 variants)
* Gr&#248;stl (224, 256 384 and 512 variants)
* JH (224, 256 384 and 512 variants)

## License
All the source code in this project is licensed under the 2-clause BSD License. The full text of the license can be found in the file LICENSE. 
