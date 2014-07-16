/*=============================================================================
*
*   FILE        : SpaceDecl.h
*
*   AUTHOR      : Space Concordia 2014 
*
*   PURPOSE     : This header contains Global Symbols. Always include BEFORE
*                 other includes.
*
*
*============================================================================*/
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



#ifdef CS1_UTEST 
/* add -DCS1_UTEST to the ENV flag in the makefile to activate the test environment */
/*
 * Unit test environment
 *
 * For unit testing, we prefer not to use the real paths for some directories, 
 * instead create/populate directories on the fly.
 * Define -DCS1_UTEST in makefile and create/remove test directories in setup()/teardown() 
 */
// Base directories
#define CS1_UTEST_DIR       "cs1_utest"             // Create this directory within the makefile
                                                    // Create all others within setup() of your tests
#undef CS1_LOGS
#define CS1_LOGS            CS1_UTEST_DIR"/logs"

#undef CS1_TGZ
#define CS1_TGZ             CS1_UTEST_DIR"/tgz"

#undef CS1_TMP
#define CS1_TMP             CS1_UTEST_DIR

#endif

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


// From limits.h
#define CS1_NAME_MAX NAME_MAX           /* 255 chars in a file name */
#define CS1_PATH_MAX PATH_MAX           /* 4096 chars in a path name including nul */

// Subsystem IDs
//#define ACS          0x00
//#define COMMS        0x01
//#define HARDWARE     0x02
//#define MECH         0x03
//#define PAYLOAD      0x04
//#define POWER        0x05
//#define SOFTWARE     0x06
//#define UPDATER      0x07
//#define WATCH_PUPPY  0x08
//#define UNDEF_SUB    0xFF
// Software Subsystem IDs for logging purposes
#define COMMANDER_LOG_ID 	0x10
#define BABYCRON_LOG_ID 	0x11
#define UPDATER_API_ID 		0x12
#define NETMAN_LOG_ID 		0x13
#define JOBRUNNER_LOG_ID 	0x14
#define TIMER_LIB_ID 		0x15
#define SHAKESPEARE_LIB_ID 	0x16
#ifndef CS1_UTEST 
#define NDEBUG              /* disable assertion (assert.h) in production version */
#endif

// Commander Config
#define COMMANER_SLEEP_TIME 1       // seconds

// General error codes
#define CS1_SUCCESS                 0
#define CS1_NULL_MALLOC             7
#define CS1_INVALID_BYTE_SEQUENCE   13
#define CS1_WRONG_LENGTH            14
#define CS1_NULL_FILE_POINTER       21

// Transceiver error codes
#define HE_FAILED_OPEN_PORT         8
#define HE_FAILED_CLOSE_PORT        9
#define HE_NOT_A_TTY                10
#define HE_INVALID_COMMAND          15
#define HE_NOT_READY                16
#define HE_POWER_OFF                17
#define HE_FAILED_TTY_CONFIG        18
#define HE_FAILED_SET_BAUD          19
#define HE_FAILED_FLUSH             20

#endif
