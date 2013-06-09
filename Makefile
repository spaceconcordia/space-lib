CC=g++
MICROCC=microblaze-unknown-linux-gnu-g++
CFLAGS=-Wall
MICROCFLAGS=-mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root -Wall
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
INCPATH=-I./inc/
# INCTESTPATH=-I./tests/unit/stubs/ -I./tests/helpers/include/
LIBPATH=-L./lib/
LIBS=-lshakespeare
# The test builds have their own main provided by CppUTest so we need to exclude commander.cpp
# DEBUG_SRC_FILES =`find src/ ! -name 'space-commander-main.cpp' -name '*.cpp'`

buildBin:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) src/*.cpp -o bin/shakespeare
buildQ6:
	$(MICROCC) $(MICROCFLAGS) $(INCPATH) $(LIBPATH) bin/main.cpp -l shakespeare-mbcc
buildQ6Shared:
	$(MICROCC) $(MICROCFLAGS) $(INCPATH) $(LIBPATH) bin/main.cpp libshakespeare.so
buildx86:
	$(CC) $(CFLAGS) $(INCPATH) $(LIBPATH) bin/main.cpp -l shakespeare
#buildAllTests: buildUnitTests
#buildUnitTests:
#	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCPATH) $(INCTESTPATH) $(LIBPATH) src/*.cpp tests/unit/*.cpp -o bin/AllUnitTests $(LIBS)
