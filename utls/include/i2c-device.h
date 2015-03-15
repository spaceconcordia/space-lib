#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#define MAX_ERROR_MSG_SIZE 200

#include <linux/rtc.h>

#define I2C_MAX_BUF_SIZE 50
namespace I2CDevice {
    int I2CRead(const char* filename, char* i2c_buffer);
    int I2CWrite();
    int I2CWriteToRTC(struct rtc_time rt,int i2c_bus);
    int readDevice (char* pPath, const char* deviceName) 

    extern char error_msg[MAX_ERROR_MSG_SIZE];
    extern int error_num;
};
#endif
