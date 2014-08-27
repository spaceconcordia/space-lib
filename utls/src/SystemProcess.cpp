/*
 * =====================================================================================
 *
 *       Filename:  SystemProcess.cpp
 *
 *    Description:  Contains functions for executing and monitoring processes  
 *
 *        Version:  1.0
 *        Created:  08/26/2014 10:12:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <SystemProcess.h>
#define MAX_COMMAND_LENGTH 255
#define MAX_OUTPUT_LENGTH 255

/**
 * Function to execute a command and get output
 */
std::string SystemProcess::Execute(char * orig_cmd) {
  char command[MAX_COMMAND_LENGTH] = {0};
  sprintf(command, orig_cmd, "2>&1"); // redirect stderr to stdout
  
  FILE * exec_pipe = popen(command, "r");
  if (!exec_pipe) return "[ERROR] failed to open pipe";
  char buffer[MAX_OUTPUT_LENGTH];
  std::string result = "";
  while( !feof(exec_pipe) ) {
    if ( fgets(buffer, MAX_OUTPUT_LENGTH, exec_pipe) != NULL ) {
      result+=buffer;
    }
  }
  pclose(exec_pipe);
  return result;
}
