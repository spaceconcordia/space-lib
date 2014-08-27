/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* AUTHORS : Space Concordia 2014, Joseph
*
* TITLE : Utl-test.cpp
*
* DESCRIPTION : Contains Unit tests for the utility classes.
*
*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/stat.h>
#include <string>
#include <unistd.h>

#include "SpaceDecl.h"
#include "CppUTest/TestHarness.h"
#include <SpaceString.h>

TEST_GROUP(SpaceStringTestGroup)
{
    void setup() 
    {

    }

    void teardown() 
    {

    }
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * GROUP : UtlsTestGroup 
 *
 * NAME : UTestUtls_CreateFileOfSize_success 
 *
 *-----------------------------------------------------------------------------*/
TEST(SpaceStringTestGroup, SimpleEcho)
{
    SystemProcess * process = new SystemProcess("echo \"Hello Space\"");
    string output = process->Execute();
    delete process;
    STRCMP_EQUAL("Hello Space", output);
}
