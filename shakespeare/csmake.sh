#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o

set -e

quit () {
  echo -e "${green}$1${NC}"
  exit 0
}

fail () {
  echo -e "${red}Aborting... $1 ${NC}"
  exit 0
}

build-x86 () {
    make clean
    make buildX86Static || fail
    ar rcs lib/libshakespeare.a lib/shakespeare.o || fail
}
build-x86-shared () {
    make clean
    make buildX86Shared || fail
    g++ -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 lib/*.o || fail
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1 || fail
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so || fail
}

build-Q6 () {
    make clean
    make buildQ6Static || fail
    ar rcs lib/libshakespeare-mbcc.a lib/shakespeare-mbcc.o || fail
}
build-Q6-shared () {
    make clean
    make buildQ6Shared || fail
    microblazeel-xilinx-linux-gnu-g++ -mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall-shared -Wl,-soname,lib/libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1 || fail
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so || fail
} 

build-BB () { make buildBBStatic
    ar rcs lib/libshakespeare-BB.a lib/shakespeare-BB.o
}

make_run_tests () {
    build-x86
    cd gtest
    make clean || fail
    make || fail
    ./shakespeare_test
}

for arg in "$@"; do
    case $arg in
        "Q6")
            build-Q6
        ;;
        "Q6-shared")
            build-Q6-shared
        ;;
        "PC")
            build-x86
        ;;
        "PC-shared")
            build-x86-shared
        ;;
        "BB")
            build-BB
        ;;
        "test")
            make_run_tests
    esac
done
if [ $# == 0 ] ; then 
    build-x86
fi
