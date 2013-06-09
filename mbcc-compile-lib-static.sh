#!/bin/bash
microblaze-unknown-linux-gnu-g++ -c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -static -c shakespeare/shakespeare.cpp -o shakespeare/shakespeare-mbcc.o
ar rcs lib/libshakespeare-mbcc.a shakespeare/shakespeare-mbcc.o
make buildQ6  
scp -P 2222 a.out root@lt-booboo.encs.concordia.ca:/home/CODE/
