#!/bin/bash
echo 'Step One: Creating object file'
make buildQ6Shared
echo 'Step Two: Creating Shared Library'
echo 'microblazeel-xilinx-linux-gnu-g++ -mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall-shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o'
microblazeel-xilinx-linux-gnu-g++ -mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall-shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
echo 'Move and Link Libraries'
echo 'mv libshakespeare.so.1.0 lib/
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so'
mv libshakespeare.so.1.0 lib/
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
echo 'Step Three: Now you can compile your code against libshakespeare.so'
