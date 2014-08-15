/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Test Shakespeare
 *
 *        Version:  1.0
 *        Created:  13-05-26 07:48:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shawn Bulger,
 *   Organization:  Space Concordia
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "shakespeare.h"

#define PROCESS "TestProc"
#define LOG_PATH "/home/logs/shakespeare_testing"

using namespace std;

int main() {

    FILE *test_log;
    test_log = Shakespeare::open_log(LOG_PATH,PROCESS);

    Shakespeare::Priority logPriority = Shakespeare::DEBUG; //enum
    string result = "Some useful debug information";
    if(test_log!=NULL) {
        Shakespeare::log(test_log, logPriority, PROCESS, result);
        Shakespeare::log(test_log, Shakespeare::WARNING, PROCESS, "This is a warning message");
        Shakespeare::log(test_log, Shakespeare::NOTICE, PROCESS, "This is a notice message");
        Shakespeare::log(test_log, Shakespeare::ERROR, PROCESS, "This is an error message");
        Shakespeare::log(test_log, Shakespeare::URGENT, PROCESS, "This is an urgent message");
        Shakespeare::log(test_log, Shakespeare::CRITICAL, PROCESS, "This is a critical message");
    }
    fclose(test_log);
    Shakespeare::log_shorthand(LOG_PATH, logPriority, PROCESS, "LOG SHORTHAND");
}
