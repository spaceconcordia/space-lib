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

int main() {
    using namespace std;

/*  // uggh
    string some_process = "TestProc"; // should increment timestamp rather than index
    string some_directory = "./test_folder/"; // folder must exist
    string some_extension = ".log"; // need '.'
    //string some_filepath = get_filename(some_directory,some_process,some_extension);
    string some_filepath = get_filename("./test folder","TestProcess",".log");
    //char *some_filepath = get_filename("./test folder","TestProcess",".log");


    char *filep = new char[some_filepath.length() + 1];
    strcpy(filep,some_filepath.c_str());
    FILE *log;
    log = fopen(filep, "a");
*/
    FILE *test_log;
    test_log = fopen(get_filename("./test folder","TestProcess",".log").c_str(),"a");

    Priority logPriority = DEBUG; //enum
    string result = "Some useful ERROR information";
    if(test_log!=NULL) {
        Log(test_log, logPriority, PROCESS, result);
    }
    fclose(test_log);
}
