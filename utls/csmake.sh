#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o

build-x86 () {
    make 
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o
}
build-Q6 () {
    make buildQ6
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o
}
build-BB () {
    make buildBB
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o
}

build-x86
#build-Q6
#build-BB
