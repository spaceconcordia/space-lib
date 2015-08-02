CC=g++
MICROCC=microblazeel-xilinx-linux-gnu-g++
BEAGLECC=arm-linux-gnueabi-g++

#
# Paths
#
SPACE_LIB = ../../space-lib
SPACE_UPTDATER = ../../space-updater
CPPUTEST_HOME = ../../CppUTest
SPACE_SCRIPT = ../../space-script

#
# Flags
#
CFLAGS += -Wall
CPPFLAGS += -Wall -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
MEM_LEAK_MACRO = -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
MICROCFLAGS=-mcpu=v8.40.b -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -mlittle-endian -Wall
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb

#
# includes
#
INCLUDES = -I./include/ -I$(SPACE_LIB)/shakespeare/inc -I$(SPACE_LIB)/include -I$(SPACE_UPTDATER)/include -I$(SPACE_SCRIPT)/tgz-wizard/include
INCTESTPATH = -I./tests/stubs/ -I./tests/helpers/include/

#
# Libraries
#
LIBPATH=-L./lib/  -L$(SPACE_LIB)/shakespeare/lib -L$(CPPUTEST_HOME)/lib
CPPUTEST_LIBS=-lCppUTest -lCppUTestExt 

#
#++++++++++++++++++++
# 	CppUTest / PC
#--------------------
#
# All Object files, do not use wildcard, add the ones you need explicitly!
#
Q6_TAG=Q6
OBJECTS = bin/i2c-device.o bin/Date.o bin/SpaceString.o bin/SystemProcess.o bin/UTestUtls.o bin/fileIO.o bin/dirUtl.o bin/cs1_systems.o
OBJECTS_Q6 = bin/i2c-device$(Q6_TAG).o bin/Date$(Q6_TAG).o bin/SpaceString$(Q6_TAG).o bin/SystemProcess$(Q6_TAG).o bin/UTestUtls$(Q6_TAG).o bin/fileIO$(Q6_TAG).o bin/dirUtl$(Q6_TAG).o bin/cs1_systems$(Q6_TAG).o

#
# CppUTest files, no wildcard, add files explicitly!
#
UNIT_TEST = tests/utl-test.cpp tests/i2c-device-test.cpp
CS1_UTEST_DIR="cs1_utest" # as defined in SpaceDecl.h

#
# ENV : either CS1_UTEST for test environment or empty for PROD, perform a 'make clean' when changing this parameter
#
ENV = -DDEBUG -DCS1_UTEST  #-DPRESERVE

#
#++++++++++++++++++++
# PC 
#--------------------
buildBin: mk_local_dir lib/libcs1_utls.a 

lib/libcs1_utls.a: $(OBJECTS)
	ar rcs $@ $^

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(MEM_LEAK_MACRO) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@ $(ENV) 

bin/fileIO.o: $(SPACE_UPTDATER)/src/fileIO.cpp $(SPACE_UPTDATER)/include/fileIO.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@ $(ENV)

bin/dirUtl.o: $(SPACE_SCRIPT)/tgz-wizard/src/dirUtl.cpp $(SPACE_SCRIPT)/tgz-wizard/include/dirUtl.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@ $(ENV)

#
#++++++++++++++++++++
# microblaze 
#--------------------
buildQ6: mk_local_dir lib/libcs1_utlsQ6.a

lib/libcs1_utls$(Q6_TAG).a: $(OBJECTS_Q6)
	ar rcs $@ $^

bin/%Q6.o: src/%.cpp
	$(MICROCC) $(MICROCFLAGS) $(INCLUDES) -c $^ -o $@

bin/fileIOQ6.o: $(SPACE_UPTDATER)/src/fileIO.cpp $(SPACE_UPTDATER)/include/fileIO.h
	$(MICROCC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@

bin/dirUtlQ6.o: $(SPACE_SCRIPT)/tgz-wizard/src/dirUtl.cpp $(SPACE_SCRIPT)/tgz-wizard/include/dirUtl.h
	$(MICROCC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@

#
#++++++++++++++++++++
# unit testing
#--------------------
test: mk_local_dir bin/AllTests 
	mkdir -p $(CS1_UTEST_DIR)

bin/AllTests: tests/AllTests.cpp  $(UNIT_TEST) $(OBJECTS) 
	$(CC) $(CFLAGS) $(MEM_LEAK_MACRO) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBPATH) -o $@ $^ $(CPPUTEST_LIBS) $(ENV)

mk_local_dir:
	mkdir -p lib bin

#
#
#++++++++++++++++++++
# Cleanup
#--------------------
clean:
	rm -f *.o *~ ./bin/* AllTests ./lib/* && rm -fr ./cs1_utest
