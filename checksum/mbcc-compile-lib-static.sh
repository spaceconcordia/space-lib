#!/bin/bash
make buildQ6Static 
ar rcs lib/libfletcher-mbcc.a lib/fletcher-mbcc.o
echo 'Now you can use lib/libfletcher-mbcc.a'
