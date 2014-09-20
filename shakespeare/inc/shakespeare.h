#ifndef SHAKESPEARE_H
#define	SHAKESPEARE_H

#include <string>
#include <stdint.h>

#include "SpaceDecl.h"

// Wrapper to the Shakespeare::log function 
#define log_3(priority, process, msg) log_shorthand(string(CS1_LOGS), priority, process, msg)

using namespace std;
namespace Shakespeare
{
    extern const char* cs1_systems[];
    enum Priority {
        NOTICE,
        WARNING,
        DEBUG,
        ERROR,
        URGENT,
        CRITICAL
    };
    // struct to hold the parsed values of a binary log entry
    typedef struct  {
        time_t 	    date_time;
        uint8_t     subsystem;
        uint8_t	    priority;
        uint16_t	data;
    } BinaryLogEntry;

    /**
     *  check if a given file is at its size limit
     **/ 
    int file_size_limit_reached(char *filepath, size_t write_size);
    
    /**
     *  check if a given directory exists using stat
     **/ 
    bool directory_exists(const char* directory);

    /**
     *  validate a filepath and make any adjustments needed, if possible
     */
    string ensure_filepath(string folder);

    /**
     *  Generate the filename given a stem (main part of word), and 
     *  suffix (usually the extension). The ISO date will be prefixed
     *  to the name, and full filepath returned
     *  @param string folder - the destination path for the log file
     *  @param string stem - how the log file will be named
     *  @param string suffix - how the filename will end (e.g. .log)
     **/
    string get_filename(string folder, string stem, string suffix);

    /*
     * Function to provide shorthand to returning file pointer for
     * Shakespeare Log (SL) file
     */
    char *get_custom_time(string format);

    FILE * open_log(string folder, string process);

    int log(FILE* lf, Priority ePriority, string process, string msg);
    int log_shorthand(string log_folder, Priority logPriority, string process, string msg);
    int log(Priority logPriority, string process, string msg);

    int log_bin(FILE* lf, Priority ePriority, uint8_t process_id, short int data);    
    int log_bin_shorthand(string log_folder, Priority logPriority, string process, string msg);
    int log_bin(Priority logPriority, string process, string msg);

    int binary_file_size(ifstream bf);
    BinaryLogEntry read_bin_entry(string filename, streampos entryPosition);
    int print_binary_entry(FILE * output_file, BinaryLogEntry entry);
}
#endif	/* SHAKESPEARE_H */
