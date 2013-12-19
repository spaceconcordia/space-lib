#!/bin/bash
echo 'Step One: Creating object file'
#echo 'g++ -Wall -fPIC -c shakespeare/shakespeare.cpp'
#g++ -Wall -fPIC -c shakespeare/shakespeare.cpp
make buildX86Shared
echo 'Step Two: Creating Shared Library'
echo 'g++ -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o'
g++ -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
echo 'Move and Link Libraries'
echo 'mv libshakespeare.so.1.0 lib/
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so'
mv libshakespeare.so.1.0 lib/
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
echo 'Step Three: Now you can compile your code against these libs!'
