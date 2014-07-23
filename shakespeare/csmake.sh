#!/bin/bash
#g++ -static -c src/shakespeare.cpp -o lib/shakespeare.o

quit () {
  echo -e "${green}$1${NC}"
  exit 1
}

build-x86 () {
    make clean
    make buildX86Static
    ar rcs lib/libshakespeare.a lib/shakespeare.o
}
build-x86-shared () {
    make clean
    make buildX86Shared
    g++ -shared -Wl,-soname,libshakespeare.so.1 -o libshakespeare.so.1.0 lib/*.o
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
}

build-Q6 () {
    make clean
    make buildQ6Static 
    ar rcs lib/libshakespeare-mbcc.a lib/shakespeare-mbcc.o
}
build-Q6-shared () {
    make clean
    make buildQ6Shared 
    microblazeel-xilinx-linux-gnu-g++ -mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall-shared -Wl,-soname,lib/libshakespeare.so.1 -o libshakespeare.so.1.0 *.o
    mv libshakespeare.so.1.0 lib/
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so.1
    ln -sf ./lib/libshakespeare.so.1.0 ./lib/libshakespeare.so
}

build-BB () { make buildBBStatic
    ar rcs lib/libshakespeare-BB.a lib/shakespeare-BB.o
}

for arg in "$@"; do
    case $arg in
        "Q6")
            build-Q6; quit;
        ;;
        "Q6-shared")
            build-Q6-shared; quit;
        ;;
        "PC")
            build-x86; quit;
        ;;
        "PC-shared")
            build-x86-shared; quit;
        ;;
        "BB")
            build-BB; quit;
    esac
done

build-x86
#build-Q6
#build-BB
