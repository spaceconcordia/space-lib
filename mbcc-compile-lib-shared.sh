#!/bin/bash
echo 'Step One: Creating object file'
echo 'microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -Wall -fPIC -c shakespeare/shakespeare.cpp'
microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -Wall -fPIC -c shakespeare/shakespeare.cpp
echo 'Step Two: Creating Shared Library'
echo 'microblaze-unknown-linux-gnu-g++ -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o'
microblaze-unknown-linux-gnu-g++ -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
echo 'Move and Link Libraries'
echo 'mv libshakespeare.so.1.0 lib/
ln -sf /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1.0 /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1
ln -sf /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1.0 /home/spaceconcordia/space/space-lib/lib/libshakespeare.so'
mv libshakespeare.so.1.0 lib/
ln -sf /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1.0 /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1
ln -sf /home/spaceconcordia/space/space-lib/lib/libshakespeare.so.1.0 /home/spaceconcordia/space/space-lib/lib/libshakespeare.so
echo 'Step Three: Compiling main.cpp with shared library'
echo 'make buildQ6Shared'
make buildQ6Shared
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot -mid-shared-library /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -c -fPIC shakespeare/shakespeare.cpp -o lib/libshakespeare-0.0.1.so
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -c -fPIC shakespeare/shakespeare.cpp -o shakespeare/shakespeare-shared.o
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot -mid-shared-library /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -shared -o lib/libshakespeare-0.0.1.so shakespeare/shakespeare-shared.o
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -o lib/libshakespeare.so shakespeare/shakespeare-mbcc-shared.o 
#make buildQ6Shared 
#mv a.out a.shared.out
#scp -P 2222 a.shared.out root@lt-booboo.encs.concordia.ca:/home/CODE/
#scp -P 2222 lib/libshakespeare-0.0.1.so root@lt-booboo.encs.concordia.ca:/home/CODE/lib/
