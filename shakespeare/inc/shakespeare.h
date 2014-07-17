#ifndef SHAKESPEARE_H
#define	SHAKESPEARE_H

#include <string>
#include <stdint.h>
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
    typedef struct  {
        time_t 	date_time;
        uint8_t subsystem;
        uint8_t	priority;
        uint8_t	data;
    } BinaryLogEntry;
    char *get_custom_time(string format);
    int log(FILE* lf, Priority ePriority, string process, string msg);
    int log_bin(FILE* lf, Priority ePriority, int process_id, int data); 
    // struct to hold the parsed values of a binary log entry
    int binary_file_size(ifstream bf);
    BinaryLogEntry read_bin_entry(string filename, streampos entryPosition);
    int print_binary_entry(BinaryLogEntry entry);
    int file_size_limit_reached(char *filepath, size_t write_size);
    bool directory_exists(const char* directory);
    string ensure_filepath(string folder);
    string get_filename(string folder, string prefix, string suffix);
    FILE * open_log(string folder, string process);
}
#endif	/* SHAKESPEARE_H */
