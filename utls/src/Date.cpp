#include <time.h>
#include <stdio.h>
#include "Date.h"


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : Date 
*
*------------------------------------------------------------------------------*/
Date::Date(){
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
    this->milisecond = 0;
    this->microsecond = 0;
    this->nanosecond = 0;
    this->time_t_format = 0;
}

Date::Date(int year, int month, int day){
    this->year = year;
    this->month = month;
    this->day = day;

    this->BuildString();
    this->MakeTimeT();
}

Date::Date(int year, int month, int day, int hour, int minute, int second){
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;

    this->BuildDateTimeString();
    this->MakeTimeT();
}

Date::Date(int year, int month, int day, int hour, int minute, int second, int milisecond, int microsecond, int nanosecond){
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    this->milisecond = milisecond;
    this->microsecond = microsecond;
    this->nanosecond = nanosecond;

    this->BuildDateTimePreciseString();
    this->MakeTimeT();
}

Date::Date(time_t raw_time){
    struct tm* timeinfo = localtime(&raw_time);
    this->time_t_format = raw_time;

    this->year = timeinfo->tm_year + 1900;
    this->month = timeinfo->tm_mon + 1;
    this->day = timeinfo->tm_mday;

    this->BuildString();
}

// 0 days
// 1 seconds
// 2 nanoseconds
Date::Date(time_t raw_time, int precision){
    struct tm* timeinfo = localtime(&raw_time);
    this->time_t_format = raw_time;

    this->year = timeinfo->tm_year + 1900;
    this->month = timeinfo->tm_mon + 1;
    this->day = timeinfo->tm_mday;

    if (precision>0) {
        this->hour = timeinfo->tm_hour;
        this->minute = timeinfo->tm_min;
        this->second = timeinfo->tm_sec;
        this->BuildDateTimeString();
    } else {
        this->BuildString();
    }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : GetTimeT
*
* PURPOSE : returns the time_t corresponding to the Date
*
*------------------------------------------------------------------------------*/
time_t Date::GetTimeT(){
    return this->time_t_format;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : MakeTimeT
*
* PURPOSE : Builds the time_t corresponding to the Date
*
*------------------------------------------------------------------------------*/
void Date::MakeTimeT(void){
    struct tm timeinfo = {0};

    timeinfo.tm_year = this->year - 1900;
    timeinfo.tm_mon  = this->month - 1;
    timeinfo.tm_mday = this->day;

    this->time_t_format =  mktime(&timeinfo);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : GetString
*
* PURPOSE : returns a pointer to date_str. Do NOT use this pointer after
*           destruction of the object. Make a copy!
*
*------------------------------------------------------------------------------*/
const char* Date::GetString(void){
    return date_str;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : GetDateTimeString
*
* PURPOSE : returns a pointer to date_str. Do NOT use this pointer after
*           destruction of the object. Make a copy!
*
*------------------------------------------------------------------------------*/
const char* Date::GetDateTimeString(void){
    return date_time_str;
}

//-----------------
// Pivate functions
//-----------------



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : BuildString
*
* PURPOSE : Builds the date_str
*
*------------------------------------------------------------------------------*/
void Date::BuildString(void){
    snprintf(date_str, 9, "%04d%02d%02d", this->year, this->month, this->day);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : BuildDateTimeString
*
* PURPOSE : Builds the date_time_str
*
*------------------------------------------------------------------------------*/
void Date::BuildDateTimeString(void){
    snprintf(date_time_str, 21, "%04d/%02d/%02d@%02d:%02d:%02d", this->year, this->month, this->day, this->hour, this->minute, this->second);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* NAME : BuildDateTimeString
*
* PURPOSE : Builds the date_time_str
*
*------------------------------------------------------------------------------*/
void Date::BuildDateTimePreciseString(void){
    snprintf(date_time_str, 27, "%04d/%02d/%02d@%02d:%02d:%02d:%02d:%02d:%02d", this->year, this->month, this->day, this->hour, this->minute, this->second, this->milisecond, this->microsecond, this->nanosecond);
}
