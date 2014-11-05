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

#include "i2c-device.h"
#include "SpaceDecl.h"
#include "CppUTest/TestHarness.h"
#include "Date.h"
#include "SpaceString.h"
#include "UTestUtls.h"
#include "fileIO.h"

static void create_file(const char* path, const char* msg);
char i2c_buffer[I2C_MAX_BUF_SIZE];

TEST_GROUP(I2CDeviceTestGroup)
{
    void setup() {
        mkdir(CS1_UTEST_DIR, S_IRWXU);
    }
    void teardown() {
        DeleteDirectoryContent(CS1_UTEST_DIR);
        rmdir(CS1_UTEST_DIR);
    }
};

void create_file(const char* path, const char* msg)
{
    FILE* file = fopen(path, "w+");
    fprintf(file, "%s", msg);
    fclose(file);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * GROUP : I2CDeviceTestGroup 
 *
 * NAME : I2CDevice_Open_Failure 
 *
 *-----------------------------------------------------------------------------*/
TEST(I2CDeviceTestGroup, I2CDevice_Open_Failure)
{
    const char* filename = "test/test";

    int result = I2CDevice::I2CRead(filename,i2c_buffer);
    CHECK(result==CS1_FAILURE);
    CHECK(I2CDevice::error_num==2);    
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * GROUP : I2CDeviceTestGroup 
 *
 * NAME : I2CDevice_Open_Success 
 *
 *-----------------------------------------------------------------------------*/
TEST(I2CDeviceTestGroup, I2CDevice_Open_Success)
{
    
    const char* filepath = CS1_UTEST_DIR"/i2c-test-file";
    const char* data_6_bytes = "123456";
  
    create_file(filepath,data_6_bytes);
    
    int result = I2CDevice::I2CRead(filepath,i2c_buffer);
    CHECK(result==CS1_SUCCESS);
    CHECK(I2CDevice::error_num==0);    
}

