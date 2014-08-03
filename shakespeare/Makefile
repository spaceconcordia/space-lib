CC=g++
CFLAGS=-Wall -pedantic -Wextra -Werror
MICROCC=microblazeel-xilinx-linux-gnu-gcc
MICROPP=microblazeel-xilinx-linux-gnu-g++
BEAGLECC=arm-linux-gnueabi-g++
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian
SHAREDMICROFLAGS = $(MICROFLAGS) -fPIC -shared
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
GLOBAL_INC_PATH=../include/
INCPATH=-I./inc/ -I$(GLOBAL_INC_PATH)
LIBPATH=-L./lib/ -L../lib/

#HEADERS=$(GLOBAL_INC_PATH)/SpaceDecl.h $(GLOBAL_INC_PATH)/Date.h

buildX86Static:
	$(CC) $(CFLAGS) $(INCPATH) $(HEADERS) $(LIBPATH) $(DEBUGFLAGS) -static -c -lcs1_utls src/shakespeare.cpp -o lib/shakespeare.o
buildQ6Static:
	$(MICROPP) $(CFLAGS) $(INCPATH) $(HEADERS) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildX86Shared:
	$(CC) $(CFLAGS) $(INCPATH) $(HEADERS) $(LIBPATH) -shared -c src/shakespeare.cpp -lcs1_utls -o lib/shakespeare.o
buildQ6Shared:
	$(MICROPP) $(CFLAGS) $(HEADERS) $(SHAREDMICROFLAGS) $(INCPATH) $(LIBPATH) -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildBBStatic:
	$(BEAGLECC) $(CFLAGS) $(HEADERS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-BB.o
clean:
	rm -f lib/* *.o *.a
