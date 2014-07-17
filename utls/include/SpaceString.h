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
class SpaceString
{
    private :
        union Converter_uint_4char 
        {
            unsigned int uint;
            char cstr[4];
        };

    public:
        static char* get4Char(char char_buf[4], unsigned int uint);
        static size_t getUInt(const char cstr[4]);
        static char* BuildPath(char *path_buf, const char *dir, const char *file);
};
#endif
