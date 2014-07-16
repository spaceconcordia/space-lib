#include "gtest/gtest.h"
#include "../inc/shakespeare.h"
#include "../../include/SpaceDecl.h"
#include <stdint.h>
#define PROCESS "GTEST"
#define BE 1
#define LE 0
#define TIMEBUFFERSIZE  80
#define READINGSIZE     4 // bytes
#define PRIORITYSIZE    1 // byte
#define SIZEOF_TIMET    8
#define SIZEOF_UINT8T   1
#define SIZEOF_INT      4
//#define BINARY_LOG_ENTRY_SIZE (SIZEOF_TIMET+SIZEOF_UINT8T+SIZEOF_UINT8T+SIZEOF_UINT8T) // timestamp, subsystem_id, priority_id, reading
#define COMPILER_CALCULATED_LOG_ENTRY_SIZE (sizeof(time_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)) // timestamp, subsystem_id, priority_id, reading
#define BINARY_LOG_ENTRY_SIZE 11
class Shakespeare_Test : public ::testing::Test
{
    protected:
    virtual void SetUp() { }
    
    // Globals
    //FILE *test_log;
};

/* 
// Some test 
TEST_F(Shakespeare_Test, SomeTest)
{
    ASSERT_EQ(
        'a', // expected
        'b'  // actual
    ); 
}
*/

char endian(void)
{
  short x=0x0100;
  return(*(char *)&x);
}

#define isBigEndian (endian()==BE)
#define isLittleEndian (endian()==LE)

TEST_F(Shakespeare_Test, LittleEndian)
{
  ASSERT_EQ(LE,endian());
}

TEST_F(Shakespeare_Test, TypeTest)
{
  ASSERT_EQ(SIZEOF_TIMET,sizeof(time_t));
  ASSERT_EQ(SIZEOF_UINT8T,sizeof(uint8_t));
  ASSERT_EQ(SIZEOF_INT,sizeof(int));
  ASSERT_EQ(BINARY_LOG_ENTRY_SIZE,COMPILER_CALCULATED_LOG_ENTRY_SIZE);
}

// EnsureFilePath 
// Make sure space is replaced with underscore, and slash is added
TEST_F(Shakespeare_Test, EnsureFilepath)
{    
    string actual_filepath = Shakespeare::ensure_filepath("/media/Data/Development/CONSAT1/space-lib/shakespeare/test folder");
    string expected_filepath = "/media/Data/Development/CONSAT1/space-lib/shakespeare/test_folder/";
    ASSERT_STREQ( 
        expected_filepath.c_str(), // expected
        actual_filepath.c_str()  // actual
    ); 
}

// GetFilename
// Test filename and path construction
// TODO WHAT ELSE?
TEST_F(Shakespeare_Test, GetFilename)
{
    string process = "TestProc";
    string extension = ".log";
    stringstream ss; 
    string folder = "/media/Data/Development/CONSAT1/space-lib/shakespeare/test_folder/";
    char *buffer = Shakespeare::get_custom_time("%Y%m%d"); 
    ss << buffer;
    string expected_file = folder + process + ss.str() + extension;

    string actual_file = Shakespeare::get_filename("/media/Data/Development/CONSAT1/space-lib/shakespeare/test folder", process, extension);

    ASSERT_STREQ(
        expected_file.c_str(), // expected
        actual_file.c_str()  // actual
    ); 
}

/*
// How to test without just replicating the code? Especially as dates change, I don't want to tamper with the clock...
// Easy to pass custom time on testing side, but harder to pass custom time through to logging function.
TEST_F(Shakespeare_Test, GetCustomDate)
{
    ASSERT_EQ(
        'a', // expected
        'b'  // actual
    ); 
}
*/

// Directory exists
// Make sure there are no false positives or false negative
// TODO test a REALLY long filepath
TEST_F(Shakespeare_Test, DirectoryExists)
{
    const int num_valid_dir = 3;
    const int num_invalid_dir = 3;
    const char *valid_directories[num_valid_dir] = {"/tmp","/var","/usr/lib/"};
    const char *invalid_directories[num_invalid_dir] = {"/foo","/foo/bar/","/etc/fstab"};
    
    int i;
    for (i=0;i<num_valid_dir;i++){
        ASSERT_EQ(
            1, // expected
            Shakespeare::directory_exists(valid_directories[i])  // actual
        ); 
    }

    for (i=0;i<num_invalid_dir;i++){
        ASSERT_EQ(
            0, // expected
            Shakespeare::directory_exists(invalid_directories[i])  // actual
        ); 
    }   
}

/* This test does not make sense at all yet */
TEST_F(Shakespeare_Test, Binary)
{
    // make a binary log entry
    FILE *test_log;
    test_log = Shakespeare::open_log("/tmp/",PROCESS);
    if (test_log != NULL) 
    {
        Shakespeare::Priority logPriority = Shakespeare::DEBUG;
        int bin_val = 5; // hardcoded value mocking as a sensor reading
        int test_subsystem = 3; 
        int result = Shakespeare::logBin(test_log, logPriority, test_subsystem, bin_val);    
        
        // test that logBin is successful
        ASSERT_EQ(0,result);
        fclose(test_log);

        // read an entry from the log file 
        string filename = Shakespeare::get_filename("/tmp/",PROCESS,".log"); // fetch filename to pass for fstream
        Shakespeare::BinaryLogEntry logEntry;
        logEntry = Shakespeare::readBinEntry(filename);
 
        // parse the entry from the log file into the struct
        printf (
            "MAX_LOG_ENTRY_SIZE:%d\ntime_t:%ld\nsubsystem:%d\npriority:%d\ndata:%d",
            BINARY_LOG_ENTRY_SIZE,logEntry.date_time,logEntry.subsystem,logEntry.priority,logEntry.data
        );
        //ASSERT_EQ(logEntry.date_time,bin_val); // TODO how to freeze time for testing? 
        ASSERT_EQ(logEntry.subsystem,test_subsystem); 
        //ASSERT_EQ(2,test_subsystem); 
        ASSERT_EQ(logEntry.priority,logPriority); 
        //ASSERT_EQ(2,logPriority); 
        ASSERT_EQ(logEntry.data,bin_val);
        //ASSERT_EQ(2,bin_val);
    } else FAIL();
}

TEST_F(Shakespeare_Test, NullFilePointer)
{
    FILE * nfp = NULL;
    int result = Shakespeare::log(nfp,Shakespeare::URGENT,"NullFilePointerTest","Testing NULL File Pointer");

    ASSERT_EQ(CS1_NULL_FILE_POINTER,result);
}
