#!/bin/bash
make buildQ6Static 
ar rcs lib/libshakespeare-mbcc.a lib/shakespeare-mbcc.o
echo 'Now you can use lib/libshakespeare-mbcc.a'
