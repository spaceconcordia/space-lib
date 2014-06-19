#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o
build-x86 () {
    make buildX86Static
    ar rcs lib/libshakespeare.a lib/shakespeare.o
}
build-Q6 () {
    make buildQ6Static 
    ar rcs lib/libshakespeare-mbcc.a lib/shakespeare-mbcc.o
}
build-BB () {
    make buildBBStatic
    ar rcs lib/libshakespeare-BB.a lib/shakespeare-BB.o
}

build-x86
#build-Q6
#build-BB
