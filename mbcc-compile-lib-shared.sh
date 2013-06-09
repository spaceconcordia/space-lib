#!/bin/bash
microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -c -fPIC -shared shakespeare/shakespeare.cpp -o lib/libshakespeare-0.0.1.so
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot -mid-shared-library /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -c -fPIC shakespeare/shakespeare.cpp -o lib/libshakespeare-0.0.1.so
#microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -o lib/libshakespeare.so shakespeare/shakespeare-mbcc-shared.o 
make buildQ6Shared 
mv a.out a.shared.out
scp -P 2222 a.shared.out root@lt-booboo.encs.concordia.ca:/home/CODE/
scp -P 2222 lib/libshakespeare-0.0.1.so root@lt-booboo.encs.concordia.ca:/home/CODE/lib/
