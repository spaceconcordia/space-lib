/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* AUTHORS : Space Concordia 2014, Joseph
*
* TITLE : SpaceString.h
*
* DESCRIPTION : Contains static functions related to the conversion from 
*               raw bytes to Type and to the char* manipulation. 
*
*----------------------------------------------------------------------------*/
#ifndef SPACE_STRING_H
#define SPACE_STRING_H
#include <string.h>
class SpaceString {
private :
    union Converter_ushort_2char {
        unsigned short ushort;
        char cstr[2];
    };

    union Converter_uint_4char {
        unsigned int uint;
        char cstr[4];
    };

    union Converter_timet_timetbytesizechar {
        time_t time;
        char cstr[sizeof(time_t)];
     };

public:
    static char* get2Char(char out[2], unsigned short ushort);
    static char* get4Char(char char_buf[4], unsigned int uint);
    static size_t getUInt(const char cstr[4]);
    static unsigned short getUShort(const char cstr[2]);
    static char* BuildPath(char *path_buf, const char *dir, const char *file);
    static char* getTimetInChar(char char_buf[sizeof(time_t)], time_t time);
    static time_t getTimet(const char cstr[sizeof(time_t)]);

};
#endif
