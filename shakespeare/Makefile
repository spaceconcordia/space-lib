CPP=g++
CFLAGS=-Wall -pedantic -Wextra -Werror
MICROCPP=microblazeel-xilinx-linux-gnu-gcc
MICROPP=microblazeel-xilinx-linux-gnu-g++
BEAGLECPP=arm-linux-gnueabi-g++
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian
SHAREDMICROFLAGS = $(MICROFLAGS) -fPIC -shared
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb

GLOBAL_INC_PATH=../include
SPACE_LIB_PATH=../
INCPATH=-I./inc -I$(GLOBAL_INC_PATH) -I$(SPACE_LIB_PATH)/utls/include
LIBPATH=-L./lib -L../lib

HEADERS=$(GLOBAL_INC_PATH)/SpaceDecl.h $(SPACE_LIB_PATH)/utls/include/Date.h

buildX86Static: $(HEADERS) src/shakespeare.cpp
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c -lcs1_utls src/shakespeare.cpp -o lib/shakespeare.o
buildQ6Static: $(HEADERS) src/shakespeare.cpp
	$(MICROPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildX86Shared: $(HEADERS) src/shakespeare.cpp
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) -shared -c src/shakespeare.cpp -lcs1_utls -o lib/shakespeare.o
buildQ6Shared: $(HEADERS) src/shakespeare.cpp
	$(MICROPP) $(CFLAGS) $(SHAREDMICROFLAGS) $(INCPATH) $(LIBPATH) -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-mbcc.o
buildBBStatic: $(HEADERS) src/shakespeare.cpp
	$(BEAGLECPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -lcs1_utls -c src/shakespeare.cpp -o lib/shakespeare-BB.o

cs1_systems.o: $(GLOBAL_INC_PATH)/SpaceDecl.h
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c $(GLOBAL_INC_PATH)/src/cs1_systems.cpp -o $(GLOBAL_INC_PATH)/lib/cs1_systems.o

cs1_systems-mbcc.o: $(GLOBAL_INC_PATH)/SpaceDecl.h
	$(MICROPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c $(GLOBAL_INC_PATH)/src/cs1_systems.cpp -o $(GLOBAL_INC_PATH)/lib/cs1_systems.o
	
example: src/example.cpp 
	$(CPP) $(CFLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) $< -o $@  -lshakespeare -lcs1_utls

clean:
	rm -f lib/* *.o *.a example
