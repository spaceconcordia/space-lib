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

int main() {
    using namespace std;

    string some_process = "TestProc"; // should increment timestamp rather than index
    string some_directory = "./test log"; // need trailing slash
    string some_extension = ".log"; // need '.'
    string some_filename = get_filename(some_directory,some_process,some_extension);
    //string some_filepath = validate_filepath(some_directory) + some_filename;
    string some_filepath = some_directory + some_filename;

    char *filep = new char[some_filename.length() + some_directory.length() + 1]; 
    strcpy(filep,some_filepath.c_str());

    FILE * log;
    log = fopen(filep, "a");
    Priority logPriority = DEBUG; //enum
    string result = "Some useful ERROR information";
    if(log!=NULL) {
        Log(log, logPriority, some_process, result);
    }
    fclose( log);
}
