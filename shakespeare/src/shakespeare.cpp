#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // TODO use only string functions!!
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h> // stat to check filesize
#include "../../include/SpaceDecl.h"

#include <sys/time.h>

#define TIMEBUFFERSIZE  80
#define READINGSIZE     4 // bytes
#define PRIORITYSIZE    1 // byte
#define SIZEOF_TIMET    8
#define SIZEOF_UINT8T   1
#define SIZEOF_INT      4
#define BINARY_LOG_ENTRY_SIZE (SIZEOF_TIMET+SIZEOF_UINT8T+SIZEOF_UINT8T+SIZEOF_UINT8T) // timestamp, subsystem_id, priority_id, reading
#define COMPILER_CALCULATED_LOG_ENTRY_SIZE (sizeof(time_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)) // timestamp, subsystem_id, priority_id, reading

#define CS1_MAX_LOG_FILE_SIZE 1024 // bytes
#define LOG_FILE_EXTENSION   ".log"
#define LOG_ENTRY_DATE_POSITION 0
#define LOG_ENTRY_SUBSYSTEM_POSITION sizeof(time_t)
#define LOG_ENTRY_PRIORITY_POSITION (LOG_ENTRY_SUBSYSTEM_POSITION+sizeof(int))
#define LOG_ENTRY_READING_POSITION (LOG_ENTRY_PRIORITY_POSITION+sizeof(int))
        
#define NULL_CHAR_POINTER 8

using namespace std;
namespace Shakespeare
{
    enum Priority {
        NOTICE,
        WARNING,
        DEBUG,
        ERROR,
        URGENT,
        CRITICAL
    };
    string priorities[6] = {"NOTICE","WARNING","DEBUG","ERROR","URGENT","CRITICAL"};

    // TODO document
    char *get_custom_time(string format) {
        char *buffer = (char *) malloc(TIMEBUFFERSIZE);
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer,80,format.c_str(),timeinfo);
        return buffer;
    }

    // TODO document
    // TODO open and close file, requires passing log file path
    int log(FILE* lf, Priority ePriority, string process, string msg) {
        if ( lf == NULL ) return CS1_NULL_FILE_POINTER;
        fflush(lf);
        fprintf(lf, "%u:%s:%s:%s\r\n", (unsigned)time(NULL), priorities[ePriority].c_str(), process.c_str(), msg.c_str());
        return 0;
    }

    /** Method to log a single integer to file as binary, which will 
     *  support most logging needs
     *  @param process_id - the id of the process, which will be referenced in SpaceDecl.h
    */
    int logBin(FILE* lf, Priority ePriority, int process_id, int data) {
        if (lf==NULL) return CS1_NULL_FILE_POINTER;
        fflush(lf);
        time_t itime;
        time(&itime);
        size_t elements_written = 0;
        printf ("%d",ePriority);
        // TODO add deliminator for future validation
        elements_written = elements_written + fwrite(&itime,        SIZEOF_TIMET, 1,lf);
        elements_written = elements_written + fwrite(&process_id,   SIZEOF_UINT8T,1,lf); 
        elements_written = elements_written + fwrite(&ePriority,    SIZEOF_UINT8T,1,lf);
        elements_written = elements_written + fwrite(&data,         SIZEOF_UINT8T,1,lf);
        fflush(lf);
        //elements_written = elements_written + fwrite("\0", sizeof(char), 1,lf); // we know the length of a log entry
        return (elements_written == 4) ? 0 : 1;
    }

    // struct to hold the parsed values of a binary log entry
    typedef struct {
        time_t 	date_time;
        uint8_t subsystem;
        uint8_t	priority;
        uint8_t	data;
    } BinaryLogEntry;

    // Method to open a binary file
    // @param buffer
    // @return int - exit status
    int readBinFileC(char * buffer, FILE * lf) {
        // check incoming file pointer
        if (lf==NULL) return CS1_NULL_FILE_POINTER;

        // read an entry from the log file
        // obtain file size
        long lSize;
        size_t result;
        fseek(lf, 0, SEEK_END);
        lSize = ftell (lf);
        rewind (lf);

        // allocate memory to contain the whole file
        buffer = (char*) malloc (sizeof(char)*lSize);
        if (buffer==NULL) {fputs ("Memory error",stderr); return 2;}

        // copy the file into the buffer
        result = fread (buffer,1,lSize,lf);
        if ((long)result != lSize) {fputs ("Reading error",stderr); return 3;}

        fclose(lf);
        return 0;
    }   

    // Method to open a binary file
    // @param buffer
    // @return int - exit status
    // Our binary log entry size is always the same. Some error checking
    // should be performed to ensure bytes received are expected and
    // and in correct order    
    BinaryLogEntry readBinEntry(string filename) {
        Shakespeare::BinaryLogEntry log_entry;
        static ifstream inputBinary;
        inputBinary.open(filename.c_str(),ios_base::binary);
        if (inputBinary) inputBinary.read( (char*)&log_entry, sizeof(log_entry) );
        return log_entry;
    }   
  
    void printBinaryEntry(BinaryLogEntry entry) {
        printf (
            "Time:%ld Subsystem:%d Priority%d Value:%d",
            entry.date_time, entry.subsystem, entry.priority, entry.data
        );
    }

    // check if a given file is at its size limit
    // TODO deprecated since tgzWizard 
    int file_size_limit_reached(char *filepath) {
        struct stat st;
        stat(filepath, &st);
        size_t log_file_size = st.st_size;
        if (CS1_MAX_LOG_FILE_SIZE < log_file_size) {
            return 1;
        }
        return 0;
    }

    // check if a given directory exists using stat and return bool
    bool directory_exists(const char* directory) {
        struct stat st;
        if (stat(directory,&st) == 0) {
            if ( S_ISDIR(st.st_mode) ) {
                return true;
            }
        }
        return false;
    }

    // if filepath has spaces they must be escaped!
    // function to validate filepath and create directory structure if missing
    string ensure_filepath(string folder) 
    {
        //check if filepath exists, else create it
        if ( !directory_exists(folder.c_str()) ) {
            // TODO create_directory! For now, replace space with underscore 
            printf ("%s Directory does not exist! Exiting... %s:%d \r\n", 
                    folder.c_str(), __FILE__,__LINE__); 
        }

        // check for spaces and slashes
        if ( folder[folder.length()-1] != '/')
        {
            folder += '/';
        }
        size_t i;
        string temp_folder; // in case we need to add backslash
        // check for spaces in the given filepath, replace with underscore
        for (i=0;i<(folder.length()-1);i++)
        {
            if ( isspace(folder[i]) )
            {
               folder[i] = '_'; // for now, replace with underscore. bad user.
            }
        }
        return folder;
    }

    // TODO document
    string get_filename(string folder, string prefix, string suffix) 
    {
        folder = ensure_filepath(folder);    
        
        DIR *pDIR;
        struct dirent *entry;
        vector<string> directoryListing;
        
        if( ( pDIR = opendir(folder.c_str()) ) )
        {
            while( ( entry = readdir(pDIR) ) )
            {
                string currentFileName = entry->d_name;
                if( currentFileName.find(suffix) != string::npos)
                {
                    directoryListing.push_back(entry->d_name);
                }
            }
            closedir(pDIR);
        }
        
        int number = 0;
        char *buffer = Shakespeare::get_custom_time("%Y%m%d"); // new file every day

        if (directoryListing.size() > 0) 
        { 
            sort(directoryListing.begin(), directoryListing.end());
            string last = directoryListing.back();
            string result;
            size_t index = 0;
            bool copy = false;

            while( index != last.length() ) { 
                if (last[index] == '.') {
                    copy = !copy;
                }
                else {        
                    if (copy) {
                        result += last[index];
                    }
                }
                index += 1;
            }
            number = atoi(result.c_str());
            number += 1; 
        }
        stringstream ss;//create a stringstream
        ss << buffer;//add stime to the stream

        return folder + prefix + ss.str() + suffix;
    }

    /*
     * Function to provide shorthand to returning file pointer for 
     * Shakespeare Log (SL) file
     * TODO enforce NULL input pointer 
     */
    FILE * open_log(string folder,string process) {
        FILE *LogFile = fopen(get_filename(folder, process, LOG_FILE_EXTENSION).c_str(),"a");
        return LogFile;
    }
}
