/*
 * =====================================================================================
 *
 *       Filename:  SC_serial.c
 *
 *    Description:  Object file to implement serial interaction.
 *                  This file was separated from the SC_he100.c file to separate
 *                  the serial layer to allow reusablility in other progroms that 
 *                  require serial access.
 *
 *                  TODO: 
 *                  - there are redundant includes here, they should be removed
 *                  - Shakespeare logging should be handled by the parent, not in this 
 *                    low level code. Remove the code and includes.
 *                  - more testing focusing on this layer
 *                  - move this library to another appropriate repository
 *
 *        Version:  1.0
 *        Created:  13-09-20 08:23:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shawn Bulger (),
 *   Organization:  Space Concordia
 *
 * =====================================================================================
 */
 
#include <stdlib.h>     /*  C Standard General Utilities Library */
#include <stdio.h>      /*  Standard input/output definitions */
#include <stdint.h>     /*  Standard integer types */
#include <string.h>     /*  String function definitions, used for strerror(errno) */
#include <unistd.h>     /*  UNIX standard function definitions, used for isatty and close */
#include <fcntl.h>      /*  File control definitions */
#include <errno.h>      /*  Error number definitions */
#include <fcntl.h>      /*  File control definitions */

// TODO these dependencies should be removed, their functionality should be higher level
#include "SpaceDecl.h"  /*  Space Concordia Global Includes */

#include <SC_serial.h>

/*  Function prototypes */
#include <SC_serial_config.h>  /*  Function prototypes */

#define SERIAL_FAILED_OPEN_PORT         1
#define SERIAL_FAILED_CLOSE_PORT        2
#define SERIAL_NOT_A_TTY                3 
#define SERIAL_FAILED_SET_BAUD          8

/**
 * Function to configure interface
 * @param fdin - the file descriptor representing the serial device
 * REF: http://man7.org/linux/man-pages/man3/termios.3.html
 * REF: http://www.unixguide.net/unix/programming/3.6.2.shtml
 */
int
SC_configureInterface (int fdin)
{
    struct termios settings;

    // get current settings
    int get_settings = -1;
    if ( ( get_settings = tcgetattr(fdin, &settings) ) < 0 )
    {
        printf (
            "get config failed: %d, %s, %s, %d", 
            fdin, strerror(errno), __func__, __LINE__
        );
        return -1; 
    }
    // attempt to set input and output baud rate to 9600
    if (cfsetispeed(&settings, B9600) < 0 || cfsetospeed(&settings, SERIAL_BAUDRATE) < 0)
    {
        printf (
            "failed set BAUD rate: %d, %s, %s, %d", 
            fdin, strerror(errno), __func__, __LINE__
        );
        return -1;
    }

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

    // ONLY for non-canonical read control behaviour
    settings.c_cc[VMIN]  = 1;     // min bytes to return read
    settings.c_cc[VTIME] = 30;    // read timeout in 1/10 seconds

    fcntl(
        fdin,
        F_SETFL,
        FNDELAY // return 0 if no chars available on port (non-blocking)
    ); // immediate reads

    tcflush(fdin, TCIFLUSH); // flush port before persisting changes

    int apply_settings = -1;
    if ( (apply_settings = tcsetattr(fdin, TCSANOW, &settings)) < 0 ) { // apply attributes
        printf (
            "failed set config: %d, %s, %s, %d", 
            fdin, strerror(errno), __func__, __LINE__
        );
        return -1;
    }
    int flush_device = -1;
    if ( (flush_device = tcsetattr(fdin, TCSAFLUSH, &settings)) < 0 ) { // apply attributes
        printf (
            "failed flush device: %d, %s, %s, %d", 
            fdin, strerror(errno), __func__, __LINE__
        );
        return -1;
    }
    return 0;
}

int
SC_openPort(const char * port_address)
{
    int fdin; // File descriptor for the port

    fdin = open(
        port_address,
          O_RDWR // O_RDWR read and write (CREAD, )
        | O_NOCTTY // port never becomes the controlling terminal
        | O_NDELAY // use non-blocking I/O
        | O_NONBLOCK
        // CLOCAL don't allow control of the port to be changed
    );

    if (fdin == -1) {
        printf (
            "Unable to open port: %s, %s, %s, %d", 
            port_address, strerror(errno), __func__, __LINE__
        );
        return SERIAL_FAILED_OPEN_PORT;
    }

    if ( !isatty(fdin) ) {
        printf (
            "Not a serial device: %s, %s, %s, %d", 
            port_address, strerror(errno), __func__, __LINE__
        );
        return SERIAL_NOT_A_TTY;
    }

    // TODO issue NOOP and check device is on
    if ( SC_configureInterface(fdin) != 0 ) fdin = -1;
      return(fdin);
}

/* Function to close serial device connection at given file descriptor */
int
SC_closePort(int fdin)
{
    // TODO: Setting the speed to B0 instructs the modem to "hang up".
    if (close(fdin) == -1)
    {
        printf (
            "Unable to close serial connection: %d, %s, %s, %d", 
            fdin, strerror(errno), __func__, __LINE__
        );
        return -1;
    }
    return 0;
}

int SC_readPort(int fdin, unsigned char * buffer, int num_bytes)
{
    return read(fdin, &buffer, num_bytes);
} 

int SC_writePort(int fdin, unsigned char * bytes, int num_bytes)
{
    return write(fdin, bytes, num_bytes);
}
