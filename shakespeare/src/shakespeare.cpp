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

using namespace std;

enum Priority {
    NOTICE,
    WARNING,
    DEBUG,
    ERROR,
    URGENT,
    CRITICAL
};
string apriori[6] = {"NOTICE","WARNING","DEBUG","ERROR","URGENT","CRITICAL"};

void Log(FILE* lf, Priority ePriority, string process, string msg) {
       
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%Y-%m-%d %H.%M.%S",timeinfo);

    fflush(lf);
    fprintf(lf, "%s :: %s :: %s :: %s\n", apriori[ePriority].c_str(), buffer, process.c_str(), msg.c_str());
}

int file_space_remaining(char *filepath)
{
    struct stat st;
    stat(filepath, &st);
    size_t size = st.st_size;
    return (MAXFILESIZE - size);
}

string validate_filepath(string folder) {
    //printf("\nIncoming folder: %s\r\n",folder);
    // check for spaces and slashes
    if ( folder[folder.length()-1] != '/')
    {
        folder += '/';
    }
    size_t i;
    string temp_folder; // in case we need to add backslash
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

/* if filepath has spaces they must be escaped! */
string get_filename(string folder, string prefix, string suffix) {
   
    //folder = validate_filepath(folder);    
    
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

    // use timestamp rather than number
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    //strftime(buffer,80,"%Y-%m-%d_%H:%M:%S",timeinfo);
    strftime(buffer,80,"%Y-%m-%d",timeinfo); // will open a new log file every day

    struct timeval tv;
    gettimeofday(&tv,NULL);

    if (directoryListing.size() > 0) { 
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
    //ss << buffer;//add stime to the stream
    ss << time(NULL);//add stime to the stream
    
    return prefix + ss.str() + suffix;
}
