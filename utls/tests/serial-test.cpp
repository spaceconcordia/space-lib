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

TEST(SerialTestGroup, UTestSerial_OpenWriteReadTest)
{
    // prepare mock bytes to test with
    unsigned char mock_bytes[36] = {0x48,0x65,0x20,0x04,0x00,0x1a,0x3e,0xa6,0x86,0xa2,0x40,0x40,0x40,0x40,0x60,0xac,0x8a,0x64,0x86,0xaa,0x82,0xe1,0x03,0xf0,0x6b,0x65,0x6e,0x77,0x6f,0x6f,0x64,0x0d,0x8d,0x08,0x63,0x9f};

    // set up our mock serial device
    int pdm; // the master pseudo tty to write to
    int pds; // the slave pseudo tty to read from

    // set up master
    pdm = SC_openPort("/dev/ptmx"/*, O_RDWR | O_NOCTTY*/);
    CHECK(pdm != -1);

    // assign slave
    grantpt(pdm);
    unlockpt(pdm);
    pds = SC_openPort(ptsname(pdm)/*, O_RDWR | O_NOCTTY*/);

    CHECK(pds != -1);

    // write series of bytes to mock serial device, intended to be our incoming transmission
    int w;
    w = SC_writePort (pds, mock_bytes, 36);
    CHECK_EQUAL(36,w);

    // read the bytes, the same ones written should come back
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
    
    // final check to make sure read returns the right number of bytes
    CHECK_EQUAL(36, r);

    // flush and close the pseudo serial devices
    fsync(pdm);
    fsync(pds);

    // close both pseudo terminal connections
    int pdmc = SC_closePort(pdm);
    int pdsc = SC_closePort(pds);

    // check that the return status was successful when closing
    CHECK_EQUAL(0,pdmc);
    CHECK_EQUAL(0,pdsc);
}

TEST(SerialTestGroup, UTestSerial_ConfigureInterface)
{
    struct termios settings;

    settings.c_iflag &= ~(
          IGNBRK // disable: ignore BREAK condition on input
        | BRKINT // convert break to null byte
        | ICRNL  // no CR to NL translation
        | INLCR  // no NL to CR translation
        | PARMRK // don't mark parity errors or breaks
        | INPCK  // no input parity check
        | ISTRIP // don't strip high bit off
    //    | IXON   // no XON/XOFF software flow control
    );
    settings.c_iflag |= (
          IXON
        | IXOFF
        | IGNPAR // ignore bytes with parity errors
        | ICRNL  // map CR to NL (otherwise CR input on other computer will not terminate input)
    //    | INLCR  // map NL to CR (otherwise CR input on other computer will not terminate input)
    );

    // Output flags
    settings.c_oflag = 0; // disable output processing, raw output

    // Line processing flags
    settings.c_lflag = 0; // disable line processing

    // settings.c_lflag = ICANON; // enable canonical input
    //cfmakeraw(&settings); // raw mode Input is not assembled into lines and special characters are not processed.

    settings.c_lflag = ECHONL;

    // Control flags
    settings.c_cflag &= ~( // disable stuff
          PARENB  // no parity bit
        | CSIZE   // mask the character size bits
        | CSTOPB  // stop bits: 1 stop bit
        | CRTSCTS // disable hardware flow control
        //| ~PARODD; // even parity
    );
    settings.c_cflag |= ( // enable stuff
          B9600    // set BAUD to 9600
        | CS8      // byte size: 8 data bits
        | CREAD   // enable receiver
        //| PARENB  // enable parity bit
        //| PARODD  // odd parity
        //| CLOCAL  // set local mode
    );

    settings.c_ispeed = B9600;
    settings.c_ospeed = B9600;

    // ONLY for non-canonical read control behaviour
    settings.c_cc[VMIN]  = 1;     // min bytes to return read
    settings.c_cc[VTIME] = 30;    // read timeout in 1/10 seconds

    // set up our mock serial device
    int pdm; // the master pseudo tty to write to
    int pds; // the slave pseudo tty to read from

    // set up master
    pdm = SC_openPort("/dev/ptmx"/*, O_RDWR | O_NOCTTY*/);
    CHECK(pdm != -1);

    // assign slave
    grantpt(pdm);
    unlockpt(pdm);
    pds = SC_openPort(ptsname(pdm), settings); // TESTING OVERLOADED CALL HERE

    CHECK(pds != -1);

    CHECK( SC_configureInterface(pdm,settings) == 0 ); // TESTING OVERLOADED CALL HERE
    
    // flush and close the pseudo serial devices
    fsync(pdm);
    fsync(pds);

    // close both pseudo terminal connections
    int pdmc = SC_closePort(pdm);
    int pdsc = SC_closePort(pds);

    // check that the return status was successful when closing
    CHECK_EQUAL(0,pdmc);
    CHECK_EQUAL(0,pdsc);
}
