#include "gtest/gtest.h"
#include "../inc/shakespeare.h"
#define PROCESS "GTEST"
#define BE 1
#define LE 0
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
    Shakespeare::Priority logPriority = Shakespeare::DEBUG; //enum
    int bin_val = 5;
    int result = Shakespeare::logBin(test_log, 3, logPriority, bin_val);
    fclose(test_log);
  
    // test that logBin is successful
    ASSERT_EQ(1,result);
    
    // read the entry from the log file
    char * logEntry = malloc (BINARYLOGENTRYSIZE);
    if (logEntry==NULL) ASSERT_EQ(1,0);
    int read_val = readBin(logEntry, test_log, PROCESS);
    struct Shakespeare::BinaryLogEntry binary_log_entry = parseEntry(logEntry);    free (logEntry);
    
    ASSERT_EQ(binary_log_entry.date_time,bin_val); // TODO how to freeze time for testing? 
    ASSERT_EQ(binary_log_entry.subsystem,3); 
    ASSERT_EQ(binary_log_entry.priority,logPriority); 
    ASSERT_EQ(binary_log_entry.data,bin_val); 
}

TEST_F(Shakespeare_Test, NullFilePointer)
{
    FILE * nfp;
    int result = Shakespeare::log(nfp,Shakespeare::URGENT,"NullFilePointerTest","Testing NULL File Pointer");

    ASSERT_EQ(1,result);
}
