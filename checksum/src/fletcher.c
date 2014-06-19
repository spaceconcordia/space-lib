/*
 * =====================================================================================
 *
 *       Filename:  fletcher.c
 *
 *    Description:  Implementation of Fletcher's checksum
 *
 *        Version:  1.0
 *        Created:  04/05/2014 05:32:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdint.h>     /*  Standard integer types */

/**
 * struct to hold values of fletcher checksum
 */
typedef struct fletcher_checksum {
    uint8_t sum1;
    uint8_t sum2;
} fletcher_checksum;

/** 
 * 16-bit implementation of the Fletcher Checksum
 * returns two 8-bit sums
 * @param data - uint8_t const - data on which to perform checksum
 * @param bytes - size_t - number of bytes to process
 * inspired by http://en.wikipedia.org/wiki/Fletcher%27s_checksum#Optimizations
 */
struct fletcher_checksum
fletcher_checksum16 (unsigned char *data, size_t bytes)
{
    uint8_t sum1 = 0, sum2 = 0;

    while (bytes)
    {
        size_t tlen = bytes > 20 ? 20 : bytes; 
        bytes -= tlen;
        do
        {
            sum2 += sum1 += *data++;
        }
        while (--tlen);
    }
    
    // prepare and return checksum values 
    fletcher_checksum r;
   
    // final reduction to 8 bits
    r.sum1 = (sum1 & 0xff);
    r.sum2 = (sum2 & 0xff);
    
    return r;
}
