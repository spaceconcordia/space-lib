CC=g++
CFLAGS=-Wall
MICROCC=microblazeel-xilinx-linux-gnu-gcc
MICROPP=microblazeel-xilinx-linux-gnu-g++
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian
SHAREDMICROFLAGS = $(MICROFLAGS) -fPIC -shared 
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
INCPATH=-I./inc/
LIBPATH=-L./lib/

buildX86Static:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/shakespeare.cpp -o lib/shakespeare.o
buildQ6Static:
	$(MICROPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildX86Shared:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) -shared -c src/shakespeare.cpp -o lib/shakespeare.o
buildQ6Shared:
	$(MICROPP) $(CFLAGS) $(SHAREDMICROFLAGS) $(INCPATH) $(LIBPATH) -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o

buildTest: 
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) src/test.cpp -lshakespeare -o bin/test.x
