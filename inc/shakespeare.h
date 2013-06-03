#ifndef SHAKESPEARE_H
#define	SHAKESPEARE_H

#include <string>
using namespace std;

void Log(FILE* lf, int priority, string msg);
string get_filename(string folder, string prefix, string suffix);


#endif	/* SHAKESPEARE_H */
