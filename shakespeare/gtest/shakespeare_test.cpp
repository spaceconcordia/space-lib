#include "gtest/gtest.h"
#include "../inc/shakespeare.h"
#include "../../include/SpaceDecl.h"
#include <stdint.h>
#define PROCESS "GTEST"
#define TIMEBUFFERSIZE  80
#define COMPILER_CALCULATED_LOG_ENTRY_SIZE (sizeof(time_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)) // timestamp, subsystem_id, priority_id, reading
#define TEST_LOG_PATH "/tmp/shakespeare_testing"

class Shakespeare_Test : public ::testing::Test
{
    protected:
    virtual void SetUp() { }
    
    // Globals
    //FILE *test_log;
};

char endian(void)
{
  short x=0x0100;
  return(*(char *)&x);
}


TEST_F(Shakespeare_Test, LittleEndian)
{
  ASSERT_EQ(LE,endian());
}

// Make sure space is replaced with underscore, and slash is added
TEST_F(Shakespeare_Test, CharacterReplacement)
{    
    string actual_filepath = Shakespeare::ensure_filepath("/tmp/test folder");
    string expected_filepath = "/tmp/test_folder/";
    ASSERT_STREQ( 
        expected_filepath.c_str(), // expected
        actual_filepath.c_str()  // actual
    ); 
}

// Test filename and path construction
TEST_F(Shakespeare_Test, GetFilename)
{
    string process = "TestProc";
    string extension = ".log";
    stringstream ss; 
    string folder = "/tmp/test_folder/";
    char *buffer = Shakespeare::get_custom_time("%Y%m%d"); 
    ss << buffer;
    string expected_file = folder + process + ss.str() + extension;

    string actual_file = Shakespeare::get_filename("/tmp/test folder", process, extension);

    ASSERT_STREQ(
        expected_file.c_str(), // expected
        actual_file.c_str()  // actual
    ); 

    ASSERT_EQ(
        true,
        Shakespeare::directory_exists(folder.c_str())
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

TEST_F(Shakespeare_Test, LogShorthand) {
    Shakespeare::Priority test_priority = Shakespeare::NOTICE;
    int log_result = Shakespeare::log_shorthand(TEST_LOG_PATH, test_priority, PROCESS, "Test Log Message");
    string filename = Shakespeare::get_filename(TEST_LOG_PATH,PROCESS,".log");
    remove (filename.c_str());
    ASSERT_EQ(0,log_result);
}

/**
 * In this test, we use the overloaded log_bin function to log
 * to 3 different subsystem logs in binary, incrementing by the 
 * binary value recorded
 * We then read these log files, parse the log entries into the 
 * binary log structure, and make sure the entries are consistent
 * with our input data.
 */
TEST_F(Shakespeare_Test, Binary)
{
    Shakespeare::Priority logPriority = Shakespeare::DEBUG;
    short int bin_val = 5; // hardcoded value mocking as a sensor reading
    uint8_t test_subsystem_id=0; 
    string test_subsystem; 
    int result,i; 
    int iterations=3;
    string filename; // open only to keep track of it and to clean up the files after the test
    
    for (i=0;i<iterations;i++) 
    {
        test_subsystem = cs1_systems[test_subsystem_id];
        filename = Shakespeare::get_filename("/home/logs/",test_subsystem,".log");

        // write log entry
        result = Shakespeare::log_bin(logPriority, test_subsystem_id, bin_val);    
        ASSERT_EQ(CS1_SUCCESS,result);

        // read log entry
        Shakespeare::BinaryLogEntry logEntry;
        logEntry = Shakespeare::read_bin_entry(filename,i);
      
        #ifdef CS1_DEBUG 
            printf (
                "MAX_LOG_ENTRY_SIZE:%d\nfilename:%s\ntime_t:%ld\nsubsystem:%d\npriority:%d\ndata:%d\n",
                sizeof(logEntry),filename.c_str(),logEntry.date_time,logEntry.subsystem,logEntry.priority,logEntry.data
            );
            print_binary_entry(stdout, logEntry);
        #endif

        //ASSERT_EQ(logEntry.date_time,bin_val); // TODO how to freeze time for testing? 
        ASSERT_EQ(test_subsystem_id,logEntry.subsystem); 
        ASSERT_EQ(logPriority,logEntry.priority); 
        ASSERT_EQ(bin_val,logEntry.data);
        bin_val++;
    }        
    remove(filename.c_str());
} 


// try to fetch an entry when not enough bytes are available at the end of the file
/* 
TEST_F(Shakespeare_Test, BinaryFileOutOfBounds) 
{
   FAIL(); 
}
*/

// catch an incomplete entry, log/report the event, and read next available 
/*

TEST_F(Shakespeare_Test, IncompleteBinaryEntry) 
{
   FAIL(); 
}
*/

// Prevent writing binary to ascii file and visa-versa

TEST_F(Shakespeare_Test, CatchBinaryAscii) 
{
   bool binary;
   char * test_entry = "1438446858:WARNING:test_process:test_message\0";
   binary = Shakespeare::binary_ascii_check(test_entry);
   ASSERT_EQ(binary, true);
}

TEST_F(Shakespeare_Test, DISABLED_AsciiCheck)
{
   string date, process, priority, message;
   string test_entry = "1438447049:WARNING:test_process:test_message\0";

   int returned_int = Shakespeare::ascii_log_check(string(test_entry), date, priority, process, message); 
   ASSERT_EQ(date,"20150801 16:37:29");
   ASSERT_EQ(priority,"WARNING");
   ASSERT_EQ(process, "test_process");
   ASSERT_EQ(message, "test_message");
   ASSERT_EQ(CS1_SUCCESS, returned_int);
}

/*
TEST_F(Shakespeare_Test, BinaryCheck) {
   string date, priority, process, message;



   int returned_int = Shakespeare::binary_log_check(test_entry, date, priority, process, message);

   ASSERT_EQ(date, "20150801 16:37:05");
   ASSERT_EQ(priority, "DEBUG");
   ASSERT_EQ(process, "SHAKESPEARE");
   ASSERT_EQ(message, "12002");
   ASSERT_EQ(CS1_SUCCESS, returned_int);
}
*/

/* FAILING TEST
TEST_F(Shakespeare_Test, DISABLED_ASCIILogCSV){
	using namespace Shakespeare;
	FILE * write_log = fopen("ascii_log.log", "a+");
	for (uint16_t i = 0; i != 10; ++i) {
		log(write_log, Shakespeare::URGENT, "TEST", "TEST TEST");
	}
	fclose(write_log);
	FILE * csv = fopen("ascii.csv", "a+");
	FILE * log = fopen("ascii_log.log", "a+");
	int i = log_file_csv(log, csv);
	fclose(csv);
	fclose(log);
	ASSERT_EQ(CS1_SUCCESS, i);
	remove("ascii_log.log");
	remove("ascii.csv");
}
*/

/* FAILING TEST
TEST_F(Shakespeare_Test, DISABLED_BinaryLogCSV){
	using namespace Shakespeare;
	FILE * write_log = fopen("bin_log.log", "ab+");
	for (uint8_t i = 0; i != 10; ++i){
		log_bin(write_log, DEBUG, 1, i);
		log_bin(write_log, ERROR, 2, i);
		log_bin(write_log, URGENT, 3, i);
		log_bin(write_log, CRITICAL, 4, i);
		log_bin(write_log, NOTICE, 5, i);
	}
	fclose(write_log);
	FILE* csv = fopen("bin.csv", "a+");
	FILE* log = fopen("bin_log.log", "r");
	log_file_csv(log, csv);
	fclose(csv);
	fclose(log);
	remove("bin.csv");
	remove("bin_log.log");
}
*/

/* FAILING TEST
TEST_F(Shakespeare_Test, DISABLED_IntegratedLogCSV)
{
   using namespace Shakespeare;

   FILE * write_log = fopen("log.log", "a+");
   for (uint16_t i = 0; i != 10; ++i) {
   	log_bin(write_log, DEBUG, 1, i);
   	log_bin(write_log, ERROR, 2, i);
   	log_bin(write_log, URGENT, 3, i);
   	log_bin(write_log, CRITICAL, 4, i);
   	log(write_log, Shakespeare::URGENT, "TEST PROCESS", "TESTING, TESTING");
   	log_bin(write_log, DEBUG, 4, i);
   	log_bin(write_log, NOTICE, 1, i);
   }
   fclose(write_log);

   FILE * csv = fopen("csv.csv", "a+");
   FILE * log = fopen("log.log", "r");
   log_file_csv(log, csv);

   fclose(csv);
   fclose(log);
   remove("log.log");
   remove("csv.csv");
}
*/

TEST_F(Shakespeare_Test, NullFilePointer)
{
    FILE * nfp = NULL;
    int result = Shakespeare::log(nfp,Shakespeare::URGENT,"NullFilePointerTest","Testing NULL File Pointer");
    ASSERT_EQ(CS1_NULL_FILE_POINTER,result);

}




