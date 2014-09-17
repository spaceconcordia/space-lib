/******************************************************************************
 *
 *   FILE        : SpaceDecl.h
 *
 *   AUTHOR      : Space Concordia 2014 
 *
 *   PURPOSE     : This header contains Global Symbols. 
 *
 *****************************************************************************/
#ifndef SPACE_CONCORDIA_DECL_H
#define SPACE_CONCORDIA_DECL_H

#include <limits.h>

/*
 * Q6 and PC environment
 */

// Base directories
#define CS1_APPS            "/home/apps"
#define CS1_LOGS            "/home/logs"
#define CS1_TGZ             "/home/tgz"
#define CS1_PIPES           "/home/pipes"
#define CS1_PIDS            "/home/pids"
#define CS1_TMP             "/tmp"

#define NDEBUG              /* disable assertion (assert.h) in production version */

#ifdef CS1_UTEST 
/* add -DCS1_UTEST to the ENV flag in the makefile to activate the test environment */
/*
 * Unit test environment
 *
 * For unit testing, we prefer not to use the real paths for some directories, 
 * instead create/populate directories on the fly.
 * Define -DCS1_UTEST in makefile and create/remove test directories in setup()/teardown() 
 */

#define CS1_UTEST_DIR       "cs1_utest"             // Create this directory within the makefile
                                                    // Create all others within setup() of your tests
#undef CS1_LOGS
#define CS1_LOGS            CS1_UTEST_DIR"/logs"

#undef CS1_TGZ
#define CS1_TGZ             CS1_UTEST_DIR"/tgz"

#undef CS1_TMP
#define CS1_TMP             CS1_UTEST_DIR

#undef NDEBUG                                       // enable assertions
#endif // CS1_UTEST


// Files
#define CS1_WATCH_PUPPY_PID CS1_PIDS"/watch-puppy.pid"

// Binaries
#define CS1_BABY_CRON_BIN   CS1_APPS"/current/baby-cron/baby-cron"
#define CS1_WATCH_PUPPY_BIN CS1_APPS"/current/watch-puppy/watch-puppy"
#define CS1_COMMANDER_BIN   CS1_APPS"/current/space-commander/space-commander"

// Updater folders
#define CS1_APPS_CURRENT    CS1_APPS"/current"
#define CS1_APPS_NEW        CS1_APPS"/new"

// Buffer sizes
#define CS1_MAX_FRAME_SIZE 190
#define CS1_MAX_LOG_FILE_SIZE 1024 // bytes

#define BE 1
#define LE 0
#define isBigEndian (endian()==BE)
#define isLittleEndian (endian()==LE)

// From limits.h
#define CS1_NAME_MAX NAME_MAX           /* 255 chars in a file name */
#define CS1_PATH_MAX PATH_MAX           /* 4096 chars in a path name including nul */

// Subsystem IDs
#define CS1_ACS          0x00
#define CS1_AT_RUNNER    0x01
#define CS1_BABY_CRON    0x02
#define CS1_COMMANDER    0x03
#define CS1_COMMS        0x05
#define CS1_CHECKSUM     0x06
#define CS1_HARDWARE     0x07
#define CS1_HELIUM       0x08
#define CS1_MECH         0x09
#define CS1_NETMAN       0x0a
#define CS1_PAYLOAD      0x0b
#define CS1_POWER        0x0c
#define CS1_SOFTWARE     0x0d
#define CS1_SHAKESPEARE  0x0e
#define CS1_PROCESS_MON  0x0d
#define CS1_TGZ_WIZARD   0x10 
#define CS1_TIMER        0x11 
#define CS1_UPDATER      0x12
#define CS1_UPDATER_API  0x13
#define CS1_UNDEF_SUB    0xFF

// Software Subsystem IDs for logging purposes
#define COMMANDER_LOG_ID 	0x10
#define BABYCRON_LOG_ID 	0x11
#define UPDATER_API_ID 		0x12
#define NETMAN_LOG_ID 		0x13
#define JOBRUNNER_LOG_ID 	0x14
#define TIMER_LIB_ID 		0x15
#define SHAKESPEARE_LIB_ID 	0x16

// Commander Config
#define COMMANER_SLEEP_TIME 1       // seconds

// General error codes
#define CS1_SUCCESS                     0
#define CS1_FAILURE                     1
#define CS1_NULL_MALLOC                 7
#define CS1_INVALID_BYTE_SEQUENCE       13
#define CS1_WRONG_LENGTH                14
#define CS1_NULL_FILE_POINTER           21
#define CS1_NULL_POINTER                77
#define CS1_DIRECTORY_DOES_NOT_EXIST    78
#define CS1_FILE_DOES_NOT_EXIST         79

#endif
