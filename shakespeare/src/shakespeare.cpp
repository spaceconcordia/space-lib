#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <string>
#include <sys/stat.h> // stat to check filesize

#include <sys/time.h>

#define MAXFILESIZE 1024 // bytes
#define EXTENSION   ".log"

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
        char *buffer = (char *) malloc(sizeof(char) * 80);
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer,80,format.c_str(),timeinfo);
        return buffer;
    }

    void log(FILE* lf, Priority ePriority, string process, string msg) {
        fflush(lf);
        fprintf(lf, "%u:%s:%s:%s\r\n", (unsigned)time(NULL), priorities[ePriority].c_str(), process.c_str(), msg.c_str());
    }

    int file_size_limit_reached(char *filepath) {
        struct stat st;
        stat(filepath, &st);
        size_t log_file_size = st.st_size;
        if (MAXFILESIZE < log_file_size) {
            return 1;
        }
        return 0;
    }

    bool directory_exists(const char* directory) {
        struct stat st;
        if (stat(directory,&st) == 0) {
            if ( S_ISDIR(st.st_mode) ) {
                return true;
            }
        }
        return false;
    }

    /* if filepath has spaces they must be escaped! */
    string ensure_filepath(string folder)
    {
        //check if filepath exists, else create it
        if ( !directory_exists(folder.c_str()) ) {
            printf ("%s Directory does not exist! Exiting... TODO create_directory! For now, replace space with underscore %s:%d \r\n",
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

    //char *get_filename(string folder, string prefix, string suffix) {
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
        //ss << number;//add number to the stream
        ss << buffer;//add stime to the stream

        //char* filepath;
        //filepath = malloc(folder.length()+prefix.length()+suffix.length()+1+4);
        //return filepath;
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
