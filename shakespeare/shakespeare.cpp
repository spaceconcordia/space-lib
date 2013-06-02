

#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

void Log(FILE* lf, string msg) {
    fprintf(lf, "%u: %s\n",  time(0), msg.c_str());
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

