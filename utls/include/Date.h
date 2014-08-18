/*=============================================================================
*
*   AUTHOR      : Space Concordia 2014 
*
*   PURPOSE     : The Date is used to convert YYYYMMDD to time_t and
*                 time_t to YYYYMMDD
* DESCRIPTION   : This class offers Date storage, manipulation, and display methods
*
*============================================================================*/
#ifndef _DATE_H_
#define _DATE_H_

class Date {
    private :
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        int milisecond;
        int microsecond;
        int nanosecond;
        char date_str[9];
        char date_time_str[21];
        time_t time_t_format;

    public :
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int minute, int second);
        Date(int year, int month, int day, int hour, int minute, int second, int milisecond, int microsecond, int nanosecond);
        Date(time_t raw_time);
        Date(time_t raw_time, int precision);

        int GetCustomFormatTime(std::string format, char * output_date, int output_length, time_t rawtime);

        time_t GetTimeT(void);
        const char* GetString(void); // When the object is destroyed, the memory location is deallocated, make a copy!
        const char* GetDateTimeString(void); // When the object is destroyed, the memory location is deallocated, make a copy!

    private :
        void MakeTimeT(void);
        void BuildString(void);
        void BuildDateTimeString(void);
        void BuildDateTimePreciseString(void);
};

#endif
