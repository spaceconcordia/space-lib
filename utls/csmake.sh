#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o

copy-libs () {
    cp ./lib/*.a ../lib/
    cp ./include/* ../include/
}

build-x86 () {
    make 
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o && copy-libs
}
build-Q6 () {
    make buildQ6
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o && copy-libs
}
build-BB () {
    make buildBB
    ar rcs lib/libcs1_utls.a bin/Date.o bin/SpaceString.o && copy-libs
}

build-x86
#build-Q6
#build-BB
