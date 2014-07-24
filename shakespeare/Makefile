CC=g++
CFLAGS=-Wall -pedantic -Wextra -Werror
MICROCC=microblazeel-xilinx-linux-gnu-gcc
MICROPP=microblazeel-xilinx-linux-gnu-g++
BEAGLECC=arm-linux-gnueabi-g++
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian
SHAREDMICROFLAGS = $(MICROFLAGS) -fPIC -shared
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
GLOBAL_INC_PATH=../../include/
INCPATH=-I./inc/ -I$(GLOBAL_INC_PATH)
LIBPATH=-L./lib/ -I../../lib/

HEADERS=$(USER_DIR)/inc/timer.h $(UTLS_DIR)/include/Date.h $(GLOBAL_INC_DIR)/SpaceDecl.h $(USER_DIR)/inc/SC_he100.h

buildX86Static:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c -lcs1_utls src/shakespeare.cpp -o lib/shakespeare.o
buildQ6Static:
	$(MICROPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildX86Shared:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) -shared -c src/shakespeare.cpp -lcs1_utls -o lib/shakespeare.o
buildQ6Shared:
	$(MICROPP) $(CFLAGS) $(SHAREDMICROFLAGS) $(INCPATH) $(LIBPATH) -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildBBStatic:
	$(BEAGLECC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-BB.o
buildTest:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) src/test.cpp -lshakespeare -lcs1_utls -o bin/test.x
clean:
	rm -f lib/* *.o *.a
