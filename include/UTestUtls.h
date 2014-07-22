/******************************************************************************
*
* AUTHOR :
*
* FILE : UTestUtls.h
*
* PURPOSE : Some static functions that are usefull when doing Unit Testing
*
* CREATION DATE : 05-07-2014
*
* LAST MODIFIED : Sat 05 Jul 2014 08:47:47 PM EDT
*
******************************************************************************/


class UTestUtls
{
    public :
        static bool CreateFile(const char* path, const char* msg);
        static bool CreateFileOfSize(const char* path, size_t size);
};
