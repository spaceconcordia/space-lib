#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <SpaceDecl.h>
#include "i2c-device.h"

namespace I2CDevice
{
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CRead
* 
* PURPOSE : Read the i2c-devices register values into a buffer
*
*-----------------------------------------------------------------------------*/
char error_msg[MAX_ERROR_MSG_SIZE];
int error_num;
int I2CRead(const char* filename, char* i2c_buffer)
{
    error_num = 0;
    FILE* file;
    if ( (file = fopen(filename,"r")) == NULL )
    {  
        snprintf(error_msg,MAX_ERROR_MSG_SIZE,"Fopen failed to open I2C device at path %s and returned error message %s \n",filename, strerror(errno));
        error_num = errno;
        return CS1_FAILURE;
    }
    if ((fgets(i2c_buffer,I2C_MAX_BUF_SIZE,file))== NULL)
    {
        snprintf(error_msg,MAX_ERROR_MSG_SIZE,"Fgets failed to read I2C device at path %s and returned error message %s \n",filename, strerror(errno));
        error_num = errno;
        return CS1_FAILURE;
    }
    fclose(file);  
    return CS1_SUCCESS;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CWriteToRTC
* 
* PURPOSE : Write to the RTC to set the time
*
*-----------------------------------------------------------------------------*/
int I2CWriteToRTC(struct rtc_time rt,int bus_number)
{   
    error_num = 0;
    char file_handler[15];
    snprintf(file_handler,15,"/dev/rtc%d",bus_number);
    int file = open(file_handler,O_RDWR);
    if (file < 0 )
    {
        snprintf(error_msg,MAX_ERROR_MSG_SIZE,"Open failed to open RTC at %s and returned errno %s \n", file_handler,strerror(errno));
        return CS1_FAILURE;
    }
    else
    {
        file = ioctl(file,RTC_SET_TIME,&rt);
        if ( file < 0 )
        {
            snprintf(error_msg,MAX_ERROR_MSG_SIZE,"IOCTL failed to set RTC at %s and returned errno %s \n", file_handler,strerror(errno));
            return CS1_FAILURE;
        }
        
    }
    close(file);
    return CS1_SUCCESS;            
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : I2CWrite
* 
* PURPOSE : Write to the i2c-device register
*
*-----------------------------------------------------------------------------*/
int I2CWrite()
{
    return 1;


    

}
}
