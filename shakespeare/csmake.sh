#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o
build-x86 () {
    make buildX86Static
    ar rcs lib/libshakespeare.a lib/shakespeare.o
}
build-x86-shared () {
    make buildX86Shared
    ar rcs lib/libshakespeare.a lib/shakespeare.o
    g++ -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
}

build-Q6 () {
    make buildQ6Static 
    ar rcs lib/libshakespeare-mbcc.a lib/shakespeare-mbcc.o
}
build-Q6-shared () {
    make buildQ6Shared 
    microblazeel-xilinx-linux-gnu-g++ -mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall-shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
}

build-BB () {
    make buildBBStatic
    ar rcs lib/libshakespeare-BB.a lib/shakespeare-BB.o
}

build-x86
#build-Q6
#build-BB
