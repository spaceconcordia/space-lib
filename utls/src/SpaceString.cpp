
#include <assert.h>
#include <stdio.h>
#include "SpaceDecl.h"
#include "SpaceString.h"

size_t SpaceString::getUInt(const char cstr[4])
{

    Converter_uint_4char converter = {0};

    if (cstr) {
        memcpy(converter.cstr, cstr, 4);
    }

    return converter.uint;
}

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


