#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h> // stat to check filesize

#include <sys/time.h>

#define TIMEBUFFERSIZE 80
#define READINGSIZE 4 // bytes
#define PRIORITYSIZE 1 // byte
#define BINARYLOGENTRYSIZE (sizeof(time_t)+sizeof(int)+sizeof(int)+sizeof(int)+sizeof(char))
// timestamp, subsystem_id, priority_id, reading, terminator

#define MAXFILESIZE 1024 // bytes
#define EXTENSION   ".log"

#define NULL_FILE_POINTER 7
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
        if ( lf == NULL ) return NULL_FILE_POINTER;
        fflush(lf);
        fprintf(lf, "%u:%s:%s:%s\r\n", (unsigned)time(NULL), priorities[ePriority].c_str(), process.c_str(), msg.c_str());
<<<<<<< HEAD
	return 0;
    }

    /** Method to log a single integer to file as binary, which will 
     *  support most logging needs
     *  @param process_id - the id of the process, which will be referenced in SpaceDecl.h
    */
    int logBin(FILE* lf, Priority ePriority, int process_id, int data) {
        if (lf==NULL) return NULL_FILE_POINTER;
        fflush(lf);
	time_t itime;
	time(&itime);
	size_t actual_size = 0;
        actual_size = actual_size + fwrite(&itime,sizeof(time_t),1,lf);
        actual_size = actual_size + fwrite(&process_id,sizeof(int),1,lf); 
        actual_size = actual_size + fwrite(&ePriority,sizeof(int),1,lf);
        actual_size = actual_size + fwrite(&data, sizeof(int), sizeof(data),lf);
        actual_size = actual_size + fwrite("\n", sizeof(char), 1,lf);
	return (actual_size == BINARYLOGENTRYSIZE) ? 0 : 1;
=======
        return 0;
>>>>>>> master
    }

    // struct to hold the parsed values of a binary log entry
    struct BinaryLogEntry {
	time_t 	date_time;
	int 	subsystem;
	int	priority;
	int	data;
    };
/*
    // Method to parse and validate log data
    struct Shakespeare::BinaryLogEntry parseEntry(char * data) {
	Shakespeare::BinaryLogEntry log_entry;
	time_t 	date_time; int dt_pos=0;
	int 	subsystem; int ss_pos=sizeof(time_t);
	int 	priority;  int py_pos=ss_pos+sizeof(int);
	int	reading;   int rg_pos=py_pos+sizeof(int);
	memcpy (date_time, data[dt_pos], sizeof(time_t));
	log_entry.date_time=date_time;
	memcpy (subsystem, data[ss_pos], sizeof(int));
	log_entry.subsystem=subsystem;
	memcpy (priority,  data[py_pos], sizeof(int));
	log_entry.priority=priority;
	memcpy (reading,   data[rg_pos], sizeof(int));
	log_entry.data=reading;
	return log_entry;
    }
*/
    // Method to open a binary file
    // @param buffer
    int readBinFile(char * buffer, FILE * lf) {
	// check incoming file pointer
    	if (lf==NULL) return NULL_FILE_POINTER;
    
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
    
    // Our binary log entry size is always the same. Some error checking
    // should be performed to ensure bytes received are expected and
    // and in correct order
/*    int readBinEntry(FILE * lf, char * buffer, int entry_position) {
	if (lf==NULL) return NULL_FILE_POINTER;
	if (buffer==NULL) return NULL_CHAR_POINTER;
        long lSize;
	fseek(lf,0,SEEK_END);
	lSize(lf);
	int i; int count=0;
	for (i=0;i<(int)lSize,i++) {
	    
	}	
	return 0;
    }
*/
 
    // TODO document
    int file_size_limit_reached(char *filepath) {
        struct stat st;
        stat(filepath, &st);
        size_t log_file_size = st.st_size;
        if (MAXFILESIZE < log_file_size) {
            return 1;
        }
        return 0;
    }

    // TODO document
    bool directory_exists(const char* directory) {
        struct stat st;
        if (stat(directory,&st) == 0) {
            if ( S_ISDIR(st.st_mode) ) {
                return true;
            }
        }
        return false;
    }

    // TODO document
    /* if filepath has spaces they must be escaped! */
    string ensure_filepath(string folder) 
    {
        //check if filepath exists, else create it
        if ( !directory_exists(folder.c_str()) ) {
	    // TODO create_directory! For now, replace space with underscore 
            printf ("%s Directory does not exist! Exiting... %s:%d \r\n", 
                    folder.c_str(), __FILE__,__LINE__); 
            //exit (EXIT_FAILURE);
        }

        //printf("\nIncoming folder: %s\r\n",folder);
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
            //if (folder[i] == 0x20 || folder[i] == 0x09 || folder[i] == 0x0a || folder[i] == 0x0b || folder[i] == 0x0d) 
            if ( isspace(folder[i]) )
            {
               folder[i] = '_'; // for now, replace with underscore. bad user.
            }
        }
        //printf("\nOutgoing folder: %s\r\n",folder);
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
     */
    FILE * open_log(string folder,string process) {
        FILE *LogFile = fopen(get_filename(folder, process, EXTENSION).c_str(),"a");
        return LogFile;
    }
}
