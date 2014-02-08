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

using namespace std;

int main() {

    FILE *test_log;
    test_log = s_open_log("/media/Data/Development/CONSAT1/space-lib/shakespeare/test_folder",PROCESS);

    Priority logPriority = DEBUG; //enum
    string result = "Some useful ERROR information";
    if(test_log!=NULL) {
        s_log(test_log, logPriority, PROCESS, result);
    }
    fclose(test_log);
}
