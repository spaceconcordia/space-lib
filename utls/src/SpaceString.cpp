/******************************************************************************
 *
 * CREATOR : Space Concordia 2014, Joseph 
 *
 * TITLE : SpaceString.cpp
 *
 * REVISION HISTORY :
 *
 *      - 2014-08-29 Joseph : Uniformize style... Short lines to avoid 
 *                            wrap around, opening brack of functions on
 *                            its own line, function headers
 *          
 *
 *****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "SpaceDecl.h"
#include "SpaceString.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : getUShort
 * 
 * PURPOSE : Converts a 2 bytes char sequence to an unsigned short
 *
 *-----------------------------------------------------------------------------*/
unsigned short SpaceString::getUShort(const char cstr[2])
{
    Converter_ushort_2char converter = {0};    

    if (cstr) {
        memcpy(converter.cstr, cstr, 2);
    }

    return converter.ushort;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : get2Char
 * 
 * PURPOSE : Converts an unsigned short to a 2 bytes char array
 *
 *-----------------------------------------------------------------------------*/
char* SpaceString::get2Char(char out_buf[2], unsigned short ushort) {
    Converter_ushort_2char converter = {0};    
    
    if (out_buf) {
        converter.ushort = ushort;
        memcpy(out_buf, converter.cstr, 4);
    }

    return out_buf;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : getUInt
 * 
 * PURPOSE : Converts a 4 byte char sequence to an unsigned integer
 *
 *-----------------------------------------------------------------------------*/
size_t SpaceString::getUInt(const char cstr[4])
{
    Converter_uint_4char converter = {0};

    if (cstr) {
        memcpy(converter.cstr, cstr, 4);
    }

    return converter.uint;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : get4Char
 * 
 * PURPOSE : Converts an unsigned integer to a 4 byte char sequence
 *
 *-----------------------------------------------------------------------------*/
char* SpaceString::get4Char(char char_buf[4], unsigned int uint)
{
    Converter_uint_4char converter = {0};    
    
    if (char_buf) {
        converter.uint = uint;
    }

    memcpy(char_buf, converter.cstr, 4);

    return char_buf;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : getTimet
 * 
 * PURPOSE : Converts an 8 byte char sequence to time_t
 *
 *-----------------------------------------------------------------------------*/
time_t SpaceString::getTimet(const char cstr[sizeof(time_t)])
{
    Converter_timet_timetbytesizechar converter = {0};

    if (cstr){
        memcpy(converter.cstr,cstr,sizeof(time_t));
    }

    return converter.time;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : get8Char 
 * 
 * PURPOSE : Converts time_t to an 8 byte char sequence 
 *
 *-----------------------------------------------------------------------------*/
char* SpaceString::getTimetInChar(char char_buf[sizeof(time_t)], time_t time)
{
    Converter_timet_timetbytesizechar converter = {0};
 
    if (char_buf){
        converter.time = time;
    }

    memcpy(char_buf, converter.cstr, sizeof(time_t));

    return char_buf;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : BuildPath 
 * 
 * PURPOSE : Builds a path 'dir/file' and saves it into 'path_buf', the caller
 *           has to make sure path_buf is large enough.
 *
 *-----------------------------------------------------------------------------*/
char* SpaceString::BuildPath(char *path_buf, const char *dir, const char *file)
{
    assert(strlen(dir) + strlen(file) + 1 < CS1_PATH_MAX);

    strcpy(path_buf, dir);
    strcat(path_buf, "/");
    strcat(path_buf, file);

    return path_buf;
}
