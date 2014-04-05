CPP=g++
CC=gcc
CFLAGS=-Wall -pedantic -Wextra -Werror
MICROCC=microblazeel-xilinx-linux-gnu-gcc
MICROPP=microblazeel-xilinx-linux-gnu-g++
BEAGLECC=arm-linux-gnueabi-g++
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian
SHAREDMICROFLAGS = $(MICROFLAGS) -fPIC -shared
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
INCPATH=-I./inc/
LIBPATH=-L./lib/

buildX86Static:
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/fletcher.c -o lib/fletcher.o
buildQ6Static:
	$(MICROPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/fletcher.c -o lib/fletcher-mbcc.o
buildX86Shared:
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) -shared -c src/fletcher.c -o lib/fletcher.o
buildQ6Shared:
	$(MICROPP) $(CFLAGS) $(SHAREDMICROFLAGS) $(INCPATH) $(LIBPATH) -c src/fletcher.c -o lib/fletcher-mbcc.o
buildBBStatic:
	$(BEAGLECC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/fletcher.c -o lib/fletcher-BB.o
buildTest:
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) src/test.c -lfletcher -o bin/test.x
