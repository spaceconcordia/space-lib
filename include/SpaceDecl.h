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

#define CS1_APPS            "/home/apps"
#define CS1_LOGS            "/home/logs"
#define CS1_TGZ             "/home/tgz"
#define CS1_PIPES           "/home/pipes"
#define CS1_WATCH_PUPPY_PID "/home/pids/watch-puppy.pid"
#define CS1_TMP             "/tmp"
#define NDEBUG              /* disable assertion (assert.h) in production version */

#else
/*
* For unit testing, we prefer not to use the real paths, instead create/populate directories on the fly.
* Define -DCS1_UTEST in makefile and create/remove test directories in setup()/teardown() 
*/
#define CS1_APPS            "./apps"
#define CS1_LOGS            "./logs"
#define CS1_TGZ             "./tgz"
#define CS1_PIPES           "./pipes"
#define CS1_WATCH_PUPPY_PID "./pids/watch-puppy.pid"
#define CS1_TMP             "."

#endif



#define CS1_MAX_FRAME_SIZE 190
#define CS1_TGZ_MAX CS1_MAX_FRAME_SIZE

/* From limits.h */
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

#endif
