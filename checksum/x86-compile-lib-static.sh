#!/bin/bash
#g++ -static -c src/fletcher.cpp -o lib/fletcher.o
make buildX86Static
ar rcs lib/libfletcher.a lib/fletcher.o
