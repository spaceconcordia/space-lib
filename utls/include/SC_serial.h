#ifndef SC_SERIAL_H_
#define SC_SERIAL_H_

#include <SC_serial_config.h>
#include <termios.h>
#include <unistd.h>

/**
 * Function to configure serial interface
 * @param fdin - the file descriptor representing the serial device
 * @return int - exit status 
 * REF: http://man7.org/linux/man-pages/man3/termios.3.html
 * REF: http://www.unixguide.net/unix/programming/3.6.2.shtml
 */
int SC_configureInterface (int, char);

/* Function to open HE100 device on configured seial port address */
int SC_openPort (unsigned char * port_address);

/* Function to close serial device connection at given file descriptor */
int SC_closePort (int);

// Read a certain number of bytes from the serial port
int SC_readPort(int fdin, unsigned char * buffer, int num_bytes);

// Write a number of bytes from the serial port
int SC_writePort(int fdin, unsigned char * bytes, int num_bytes);

#endif
