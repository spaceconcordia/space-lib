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

#include "SpaceDecl.h"
#include "CppUTest/TestHarness.h"
#include "Date.h"
#include "SpaceString.h"
#include "UTestUtls.h"
#include "fileIO.h"

TEST_GROUP(SpaceStringTestGroup)
{
    void setup() {
    }

    void teardown() {
    }
};

TEST_GROUP(UtlsTestGroup)
{
    void setup() {
        mkdir(CS1_UTEST_DIR, S_IRWXU);
    }
    void teardown() {
        DeleteDirectoryContent(CS1_UTEST_DIR);
        rmdir(CS1_UTEST_DIR);
    }
};


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * GROUP : UtlsTestGroup 
 *
 * NAME : UTestUtls_CreateFileOfSize_success 
 *
 *-----------------------------------------------------------------------------*/
TEST(UtlsTestGroup, UTestUtls_CreateFileOfSize_success)
{
    const int FILE_SIZE = 10;
    const char* file_path = CS1_UTEST_DIR"/helper.txt";
    UTestUtls::CreateFileOfSize(file_path, FILE_SIZE);

    struct stat attr;
    stat(file_path, &attr);

    CHECK_EQUAL(FILE_SIZE, attr.st_size);

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* GROUP : SpaceStringTestGroup 
*
* NAME  : get4Char_returnCorrectCStr
* 
*-----------------------------------------------------------------------------*/
TEST(SpaceStringTestGroup, get4Char_returnCorrectCStr)
{
    char expected_cstr[4] = { 0x00, 0xEF, 0xCD, 0xAB };
    char cstr[4] = {0};
    size_t uint = 2882400000LL;

    SpaceString::get4Char(cstr, uint);

    CHECK_EQUAL(memcmp(expected_cstr, cstr, 4), 0);
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : SpaceStringTestGroup :: getUInt_returnCorrectIntegerValue
* 
* PURPOSE :
*
*-----------------------------------------------------------------------------*/
TEST(SpaceStringTestGroup, getUInt_returnCorrectIntegerValue)
{
    char cstr[4] = { 0x00, 0xEF, 0xCD, 0xAB };
    size_t expected = 2882400000LL;

    size_t actual = SpaceString::getUInt(cstr);

    CHECK_EQUAL(expected, actual);
}

TEST_GROUP(DateTestGroup)
{
    void setup() {
    }
    void teardown() {
    }
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : GetTimeT_returns_time_t
* 
* PURPOSE : Converts YYYYMMDD to time_t back and forth.
*
*-----------------------------------------------------------------------------*/
TEST(DateTestGroup, GetTimeT_returns_time_t){
    Date date(2014, 1, 1);

    time_t rawtime = date.GetTimeT();

    Date date_raw(rawtime);

    STRCMP_EQUAL(date.GetString(), date_raw.GetString()); 

}
