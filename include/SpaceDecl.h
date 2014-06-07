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


#ifndef CS1_UTEST           /* add -DCS1_UTEST to the ENV flag in the makefile to activate the test environment */
/*
* Q6 and PC environment
*
*/
// Base directories
#define CS1_APPS            "/home/apps"
#define CS1_LOGS            "/home/logs"
#define CS1_TGZ             "/home/tgz"
#define CS1_PIPES           "/home/pipes"
#define CS1_PIDS            "/home/pids"
#define CS1_TMP             "/tmp"

// Files
#define CS1_WATCH_PUPPY_PID "/home/pids/watch-puppy.pid"


#define NDEBUG              /* disable assertion (assert.h) in production version */

#else // CS1_UTEST is defined!
/*
* Unit test environment
*
* For unit testing, we prefer not to use the real paths, instead create/populate directories on the fly.
* Define -DCS1_UTEST in makefile and create/remove test directories in setup()/teardown() 
*/
// Base directories
#define CS1_UTEST_DIR       "cs1_utest"             // Create this directory within the makefile and use
#define CS1_APPS            CS1_UTEST_DIR"/apps"    // Create all other within setup() of your tests
#define CS1_LOGS            CS1_UTEST_DIR"/logs"
#define CS1_TGZ             CS1_UTEST_DIR"/tgz"
#define CS1_PIPES           CS1_UTEST_DIR"/pipes"
#define CS1_PIDS            CS1_UTEST_DIR"/pids"
#define CS1_TMP             CS1_UTEST_DIR

// Files
#define CS1_WATCH_PUPPY_PID CS1_UTEST_DIR"/pids/watch-puppy.pid"


#endif


// Binaries
#define CS1_BABY_CRON_BIN   CS1_APPS"/current/baby-cron/baby-cron"
#define CS1_WATCH_PUPPY_BIN CS1_APPS"/current/watch-puppy/watch-puppy"
#define CS1_COMMANDER_BIN   CS1_APPS"/current/space-commander/space-commander"

// Updater folders
#define CS1_APPS_CURRENT    CS1_APPS"/current"
#define CS1_APPS_NEW        CS1_APPS"/new"


#define CS1_MAX_FRAME_SIZE 190
#define CS1_TGZ_MAX CS1_MAX_FRAME_SIZE

/* From limits.h */
#define CS1_NAME_MAX NAME_MAX           /* 255 chars in a file name */
#define CS1_PATH_MAX PATH_MAX           /* 4096 chars in a path name including nul */




#endif
