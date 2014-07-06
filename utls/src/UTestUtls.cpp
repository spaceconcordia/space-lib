/******************************************************************************
*
* AUTHOR :
*
* FILE : UTestUtls.cpp
*
* PURPOSE :
*
* CREATION DATE : 05-07-2014
*
* LAST MODIFIED : Sat 05 Jul 2014 08:43:23 PM EDT
*
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <stdio.h>

#include "UTestUtls.h"



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : create_file
 *
 * PURPOSE : Conviently create test files.
 * 
 *-----------------------------------------------------------------------------*/
bool UTestUtls::CreateFile(const char* path, const char* msg)
{
    FILE* file = fopen(path, "w+");

    if (!file) {
        fprintf(stderr, "fopen failed");
        return false;
    }

    fprintf(file, "%s", msg);
    fclose(file);

    return true;
}


bool UTestUtls::CreateFileOfSize(const char* path, size_t size)
{
    int status_size = 0;
    FILE *file = fopen(path, "w+");

    if (!file) {
        fprintf(stderr, "fopen failed");
        return false;
    }

    fclose(file);


    while (status_size < (int)size) {
        // 1st fork
        int pid = fork();

        if (pid == 0) {
            FILE* file = 0;

            file = fopen(path, "a");

            if (!file) {
                fprintf(stderr, "fopen failed");
                return false;
            }

            fprintf(file, "%c", 'a');

            fclose(file);

            exit(0);
        } else {
            int sts = 0;
            waitpid(pid, &sts, 0);

            // 2nd fork
            pid = fork();
        }


        if (pid == 0) {
            struct stat attr;
            stat(path, &attr);
            exit((int)attr.st_size);    // Returing the size via the exit status... OK this is for Unit Testing ONLY!
        } else { 
           
            waitpid(pid, &status_size, 0); 

            if (WIFEXITED(status_size)) {
                status_size = WEXITSTATUS(status_size);
            }
        }
    }

    return true;
}
