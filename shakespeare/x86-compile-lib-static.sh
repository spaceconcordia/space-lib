#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o
make buildX86Static
ar rcs lib/libshakespeare.a lib/shakespeare.o
