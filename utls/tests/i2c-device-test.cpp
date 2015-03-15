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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * GROUP : "readDevice" Testing
 *
 * NAME : Tests brought over from jobs Gtest
 *
 *-----------------------------------------------------------------------------*/



// Test that the readDevice function returns success when passed the correct pPath and "in_voltage0_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage0)
{
    /*********************AD7998 Temperature Sensor 0********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage0_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage1_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage1)
{
    /*********************AD7998 Temperature Sensor 1********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage1_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage2_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage2)
{
    /*********************AD7998 Battery Temperature Sensor 1********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage2_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage3_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage3)
{
    /*********************AD7998 Battery Temperature Sensor 0********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage3_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage4_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage4)
{
    /*********************AD7998 Battery Temperature Sensor 2********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage4_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage5_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage5)
{
    /*********************AD7998 Temperature Sensor 3********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage5_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage6_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage6)
{
    /*********************AD7998 Payload Temperature Sensor********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage6_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns success when passed the correct pPath and "/in_voltage7_raw" device
TEST_F(Read_Temp_EBPL_Test, readFromInVoltage7)
{
    /*********************AD7998 Elec Bay Temperature Sensor********************/
    int readDeviceReturn = readDevice(pPath, "/in_voltage7_raw");

    ASSERT_EQ(
        CS1_SUCCESS, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns a null path error when passed a null path
TEST_F(Read_Temp_EBPL_Test, readFromNullPath)
{
    int readDeviceReturn = readDevice(NULL, "/in_voltage1_raw");

    ASSERT_EQ(
        NULL_PATH_ERROR, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns a null device error when passed a null device
TEST_F(Read_Temp_EBPL_Test, readFromNullDevice)
{
    int readDeviceReturn = readDevice(pPath, NULL);

    ASSERT_EQ(
        NULL_DEVICENAME_ERROR, // expected
        readDeviceReturn // actual
    );
}


// Test that the readDevice function returns a null path error when passed a null path and null device
TEST_F(Read_Temp_EBPL_Test, readFromNullPathNullDevice)
{
    int readDeviceReturn = readDevice(NULL, NULL);

    ASSERT_EQ(
        NULL_PATH_ERROR, // expected
        readDeviceReturn // actual
    );
}
