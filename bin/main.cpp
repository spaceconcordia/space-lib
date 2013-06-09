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
#include <iostream>
//#include "shakespeare.h"
#include "../inc/shakespeare.h"

int main() {
    using namespace std;
    FILE * log;
    log = fopen("/var/log/space/error.log", "a");      
    Priority logPriority = DEBUG; //enum
    string process = "TestProc";
    string result = "Some useful ERROR information";
    if(log!=NULL) {
        Log(log, logPriority, process, result);
    }
    fclose( log);
}
