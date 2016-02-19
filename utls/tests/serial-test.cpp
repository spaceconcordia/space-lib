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
#include <termios.h>
#include <fcntl.h>

#include <SpaceDecl.h>
#include "CppUTest/TestHarness.h"
#include "UTestUtls.h"
#include "fileIO.h"
#include <SC_serial.h>


TEST_GROUP(SerialTestGroup)
{
    void setup() {
        
    }

    void teardown() {
        
    }
};

TEST(SerialTestGroup, UTestSerial_ReadTest)
{
    // prepare mock bytes to test with
    unsigned char mock_bytes[36] = {0x48,0x65,0x20,0x04,0x00,0x1a,0x3e,0xa6,0x86,0xa2,0x40,0x40,0x40,0x40,0x60,0xac,0x8a,0x64,0x86,0xaa,0x82,0xe1,0x03,0xf0,0x6b,0x65,0x6e,0x77,0x6f,0x6f,0x64,0x0d,0x8d,0x08,0x63,0x9f};

    // set up our mock serial device
    int pdm; // the master pseudo tty to write to
    int pds; // the slave pseudo tty to read from

    // set up master
    pdm = open("/dev/ptmx", O_RDWR | O_NOCTTY);
    if (pdm < 0) CHECK_EQUAL(0,pdm);

    // assign slave
    grantpt(pdm);
    unlockpt(pdm);
    pds = open(ptsname(pdm), O_RDWR | O_NOCTTY);

    if (pds < 0) CHECK_EQUAL(0,pds);
    // write series of bytes to mock serial device, intended to be our incoming transmission
    int w;
    w = SC_writePort (pds, mock_bytes, 36);
    CHECK_EQUAL(36,w);

    // invoke HE100_read
    int r;
    unsigned char payload[36] = {0};
    r = SC_readPort(pdm, payload, 36); // TODO ptr-ptr

    // analyse the payload, ASSERT (all_expected_bytes, all_actual_bytes)
    for (int z=0; z<36; z++) {
        CHECK_EQUAL(
            mock_bytes[z],
            payload[z]
        );
    }

    // flush and close the pseudo serial devices
    fsync(pdm);fsync(pds);
    close(pdm);close(pds);

    // final check to make sure read returns successfully
    CHECK_EQUAL(26, r);
}

