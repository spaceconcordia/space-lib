#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;

enum Priority {
    NOTICE,
    WARNING,
    DEBUG,
    ERROR,
    URGENT,
    CRITICAL
};
string apriori[6] = {"NOTICE","WARNING","DEBUG","ERROR","URGENT", "CRITICAL"};

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

string get_filename(string prefix, string suffix){
    char buffer[100];
    
    time_t now = time(NULL);
    struct tm tm = *localtime(&now);
    sprintf(buffer, "%d%d%d%d%d%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return prefix + string(buffer) + suffix; 
}

string get_filename(string folder, string prefix, string suffix) {
    
    DIR *pDIR;
    struct dirent *entry;
    vector<string> directoryListing;
    
    if( pDIR = opendir(folder.c_str()) )
	{
        while(entry = readdir(pDIR))
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
    
    if (directoryListing.size() > 0) {
        sort(directoryListing.begin(), directoryListing.end());

        string last = directoryListing.back();
        string result;
        int index = 0;
        bool copy = false;

        while(index != last.length()) {
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
    ss << number;//add number to the stream
    
    return prefix + ss.str() + suffix;
}

