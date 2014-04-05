#!/bin/bash
echo 'Step One: Creating object file'
make buildX86Shared
echo 'Step Two: Creating Shared Library'
echo 'g++ -shared -Wl,-soname,libfletcher.so.1 -o libfletcher.so.1.0 *.o'
g++ -shared -Wl,-soname,libfletcher.so.1 -o libfletcher.so.1.0 *.o
echo 'Move and Link Libraries'
echo 'mv libfletcher.so.1.0 lib/
ln -sf ./lib/libfletcher.so.1.0 ./lib/libfletcher.so.1
ln -sf ./lib/libfletcher.so.1.0 ./lib/libfletcher.so'
mv libfletcher.so.1.0 lib/
ln -sf ./lib/libfletcher.so.1.0 ./lib/libfletcher.so.1
ln -sf ./lib/libfletcher.so.1.0 ./lib/libfletcher.so
echo 'Step Three: Now you can compile your code against these libs!'
