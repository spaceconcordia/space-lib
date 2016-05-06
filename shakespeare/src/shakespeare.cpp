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
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h> // stat to check filesize
#include <SpaceDecl.h>
#include <Date.h>

#include <sys/time.h>

#define TIMEBUFFERSIZE  80
#define DEFAULT_LOG_FOLDER "/home/logs"
#define CS1_MAX_LOG_FILE_SIZE 1024 // bytes
#define LOG_FILE_EXTENSION ".log"
#define LOG_ENTRY_DATE_POSITION 0
#define LOG_ENTRY_SUBSYSTEM_POSITION sizeof(time_t)
#define LOG_ENTRY_PRIORITY_POSITION (LOG_ENTRY_SUBSYSTEM_POSITION+sizeof(int))
#define LOG_ENTRY_READING_POSITION (LOG_ENTRY_PRIORITY_POSITION+sizeof(int))
#define SIZEOF_BIN_LOG_ENTRY sizeof(BinaryLogEntry)

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

    char *get_custom_time(string format) {
        char *buffer = (char *) malloc(TIMEBUFFERSIZE);
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer,80,format.c_str(),timeinfo);
        return buffer;
    }

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

    string ensure_filepath(string folder) 
    {
        // check for trailing slash
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
               folder[i] = '_'; // for now, replace with underscore
            }
        }

        if ( !directory_exists(folder.c_str()) ) 
        {
           printf ("%s Directory does not exist! Attempting to create it... %s:%d \r\n", 
                    folder.c_str(), __FILE__,__LINE__);  
          
           int mkdir_result = mkdir(folder.c_str(),S_IRWXU);

           if ( !directory_exists(folder.c_str()) || (mkdir_result != 0) ) {
                   printf ("Failed creating path: %s %s:%d\n",folder.c_str(), __FILE__,__LINE__);
           }
        }

        return folder;
    }

    string get_filename(string folder, string stem, string suffix) 
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
        char *iso_date = Shakespeare::get_custom_time("%Y%m%d"); // new file every day

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
        return folder + stem + iso_date + suffix;
    }

    // TODO enforce NULL input pointer 
    FILE * open_log(string folder,string process) 
    {
        FILE *LogFile = fopen(get_filename(folder, process, LOG_FILE_EXTENSION).c_str(),"a");
        return LogFile;
    }

    // TODO open and close file, requires passing log file path
    int log(FILE* lf, Priority ePriority, string process, string msg) 
    {
        if ( lf == NULL ) 
        {
           return CS1_NULL_FILE_POINTER;
        }
        fflush(lf);
        fprintf(lf, "%u:%s:%s:%s\r\n", (unsigned)time(NULL), priorities[ePriority].c_str(), process.c_str(), msg.c_str());
        return 0;
    }

    // logs into csv
    int log_csv(FILE* lf, string date, string ePriority, string process, string msg)
    {
        if (lf == NULL)
        {
            return CS1_NULL_FILE_POINTER;
        }
        fflush(lf);
        fprintf(lf, "%s,%s,%s,%s,\r\n", date.c_str(), ePriority.c_str(), process.c_str(), msg.c_str());
        return 0;
    }

   //returns true if binary, false for ascii
   bool binary_ascii_check(char * line){
      bool all_ascii = true;
      bool colon_pos = false;
      size_t i;
      for (i = 0; i < strlen(line) && line[i] != '\0'; ++i) {
        if (line[i] == ':' && i == 10) {
          colon_pos = true;
        }
        if ((int)line[i] < 0){
          all_ascii = false;
        }
      } 
      if (all_ascii && colon_pos){
        return true;
      }
        return false;
      }

      inline string timet_to_date_string(time_t time) {
      tm * ptm = localtime(&time);
      char * c_date = new  char[32];
      strftime(c_date, 32, "%Y%m%d %H:%M:%S", ptm);
      string date_string = string(c_date);
      delete[] c_date;
      return date_string;
  }
/* //TODO FAILING TEST 
  int binary_log_check(char * line, string &date, string &priority, string &process, string &message) {
      size_t read = 0;
      time_t * time;
      time = (time_t *)(line + read);
      date = timet_to_date_string(*time);
      read += sizeof(time_t);

      uint8_t * process_id = (uint8_t *)(line + read);
      process = cs1_systems[*process_id];
      read += sizeof(uint8_t);

      uint8_t * priority_id = (uint8_t *)(line + read);
      priority = priorities[* priority_id];
      read += sizeof(uint8_t);

      uint16_t * data_msg = (uint16_t *)(line + read);
      char data_msg_arr[64];
      snprintf(data_msg_arr, 64, "%d", *data_msg);
      message = std::string(data_msg_arr);

      return CS1_SUCCESS;
  }
  */

    int ascii_log_check(string entry, string &date, string &priority, string &process, string &message)  {
        unsigned int index;
	unsigned int length = entry.length();

        for (index = 0; index < length && entry[index] != ':'; ++index) {
        }
        string date_raw = entry.substr(0, index);
        time_t time = (time_t)atol(date_raw.c_str());

	date = timet_to_date_string(time);
	//priority
        unsigned int base = ++index;
        for (index = 0; (base + index) < length && entry[base + index] != ':'; ++index)
	{}
        priority = entry.substr(base, index);

	//process
        base = ++index + base;
        for (index = 0; (base + index) < length && entry[base + index] != ':'; ++index)
	{}
	process = entry.substr(base, index);

        ++index;
	message = entry.substr(base + index, length);

        return CS1_SUCCESS;
    }

//read from file, write to csv
/* // TODO FAILING TEST
int log_file_csv(FILE* lf, FILE* csv)
{
  if (lf == NULL || csv == NULL)
  {
      return CS1_NULL_FILE_POINTER;
  };

  string priority;
  string process;
	string message;
	string date;

  char line[256];
  size_t bin_s = sizeof(time_t) + 2*sizeof(uint8_t) + sizeof(uint16_t);
	size_t read;
  while ((read = fread(line, sizeof(char), 2 * bin_s , lf))){
	  if (binary_ascii_check(line)) {
      memset(line, '0', 256);
      fseek(lf, -1 * read, SEEK_CUR);
      fgets(line, sizeof(line), lf);
      ascii_log_check(string(line), date, priority,process,message);
	  }
    else {
      fseek(lf, -1 * read, SEEK_CUR);
      memset(line, '0', 256); 
      if (fread(line, sizeof(char), bin_s, lf)){
        binary_log_check(line, date, priority, process, message);
      }
      else {
        return CS1_FAILURE;
      }
    }
	  memset(line, '0', 256);
    log_csv(csv, date, priority, process, message);
	 }
   return CS1_SUCCESS;
}
*/

    // faster method to make log entries
    int log_shorthand(string log_folder, Priority logPriority, string process, string msg)
    {
        FILE *test_log;
        test_log = open_log(log_folder,process);
        int log_result=-1;

        if(test_log!=NULL)
        {
            log_result = Shakespeare::log(test_log, logPriority, process, msg);
            fclose(test_log);
        }
        return log_result;
    }

    int log(Priority logPriority, string process, string msg) {
        return log_shorthand (DEFAULT_LOG_FOLDER, logPriority, process, msg);
    }

    // struct to hold the parsed values of a binary log entry
    typedef struct {
        time_t 	date_time;
        uint8_t subsystem;
        uint8_t	priority;
        uint16_t	data;
    } BinaryLogEntry;

    /** Method to log a single integer to file as binary, which will
     *  support most logging needs
     *  @param process_id - the id of the process, which will be referenced in SpaceDecl.h
    */
    int log_bin(FILE* lf, Priority ePriority, uint8_t process_id, short int data)
    {
        size_t expected_num_elements = 4;
        if (lf==NULL)
        {
            return CS1_NULL_FILE_POINTER;
        }

        fflush(lf);
        time_t itime;
        time(&itime);
        size_t elements_written = 0;

        size_t log_entry_padding = sizeof(BinaryLogEntry) - ( sizeof(time_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint16_t) );

        elements_written = elements_written + fwrite(&itime,        sizeof(time_t), 1,lf);
        elements_written = elements_written + fwrite(&process_id,   sizeof(uint8_t),1,lf);
        elements_written = elements_written + fwrite(&ePriority,    sizeof(uint8_t),1,lf);
        elements_written = elements_written + fwrite(&data,         sizeof(uint16_t),1,lf);

        if (log_entry_padding > 0)
        {
            expected_num_elements=5;
            elements_written = elements_written + fwrite("\0", log_entry_padding, 1, lf);
        }

        fflush(lf);
        return (elements_written == expected_num_elements) ? 0 : 1;
    }

    // faster method to make log entries
    int log_bin_shorthand(string log_folder, Priority logPriority, uint8_t process_id, short int data) {
        FILE *test_log;
        const char * process = cs1_systems[process_id];
        test_log = open_log(log_folder,process);
        int log_result=-1;
        if(test_log!=NULL) {
            log_result = Shakespeare::log_bin(test_log, logPriority, process_id, data);
        }
        fclose(test_log);
        return log_result;
    }

    int log_bin(Priority logPriority, uint8_t process_id, short int data) {
       return Shakespeare::log_bin_shorthand(DEFAULT_LOG_FOLDER, logPriority, process_id, data);
    }

    // Method to read an entry from a binary file
    // @param string filename - the name of the file which stores binary log entries
    // @param streampos entry_position - the position of the log entry to be read
    // @return BinaryLogEntry - the BinaryLogEntry struct containing all pertinent data
    //
    // Our binary log entry size is always the same. Some error checking
    // should be performed to ensure bytes received are expected and
    // and in correct order
    // TODO current operation is dangerous and unreliable.
    // A single missing byte will break all future log entry reading - use a delimination phrase between log entries, and scan accordingly
    BinaryLogEntry read_bin_entry(string filename, streampos entry_position) {
        Shakespeare::BinaryLogEntry log_entry;
        static ifstream inputBinary;
        inputBinary.open(filename.c_str(),ios_base::binary);
        streampos abs_position = entry_position*sizeof(log_entry);

        // store EOF conditions
        inputBinary.seekg(0,ios::end);
        size_t file_size;
        file_size = inputBinary.tellg();

        #ifdef CS1_DEBUG
            printf ("End: filesize:%d,entries:%ld\n", file_size, file_size / sizeof(log_entry) );
        #endif

        // seek back to beginning of file
        inputBinary.seekg(0,ios::beg);
        if (entry_position > 0) {// seek as required
            inputBinary.seekg(abs_position);
        }

        // take a reading if boundary conditions are met
        int cur_pos = inputBinary.tellg();
        if ( (unsigned)(file_size - cur_pos) >= sizeof(log_entry) ) {
            if (inputBinary) { // read and return log entry
                inputBinary.read( (char*)&log_entry, sizeof(log_entry) );
            }
        }

        // close and return
        inputBinary.close();
        return log_entry;
    }

    // print a binary log entry in a human-readable form
    void print_binary_entry(FILE * output_file, BinaryLogEntry entry) {
        Date time(entry.date_time,1);
        fprintf ( output_file,
            "Time:%s Subsystem:%d Priority:%s Value:%d\n",
            time.GetDateTimeString(), entry.subsystem, priorities[entry.priority].c_str(), entry.data
        );
    }
}
