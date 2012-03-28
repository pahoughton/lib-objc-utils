#ifndef _DateTimeUtils_hh_
#define _DateTimeUtils_hh_
/**
   File:        DateTimeUtils.hh
   Project:	StlUtils ()
   Desc:        
  
    Declarations for various DateTime constants and functions.
  
   Quick Start: - short example of class usage
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     05/02/95 06:32
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
  
    $Id$ 
**/

#include <SMKConfig.h>
#include <time.h>
#include <string.h>


extern const time_t SMK_GVAR_T SecPerMin;
extern const time_t SMK_GVAR_T SecPerHour;
extern const time_t SMK_GVAR_T SecPerDay;
extern const time_t SMK_GVAR_T SecPerYear;

extern const time_t SMK_GVAR_T MinPerHour;
extern const time_t SMK_GVAR_T MinPerDay;

extern const time_t SMK_GVAR_T MinTimeT;
extern const time_t SMK_GVAR_T MaxTimeT;

extern const time_t SMK_GVAR_T MinYear;
extern const time_t SMK_GVAR_T MaxYear;

#if ! defined( COMMON_DATETIME_VALUES )
#define COMMON_DATETIME_VALUES 1

extern const int    SMK_GVAR_T DaysInMonth[];
extern const int    SMK_GVAR_T DaysInMonthLeap[];

extern const int    SMK_GVAR_T MonthDayOfYear[];
extern const int    SMK_GVAR_T MonthDayOfYearLeap[];

extern const char * SMK_GVAR_T Months[];
extern const char * SMK_GVAR_T AbbrMonths[];
extern const char * SMK_GVAR_T WeekDays[];
extern const char * SMK_GVAR_T AbbrWeekDays[];
#endif

#if !defined( DAYOFWEEK_ENUM )
#define DAYOFWEEK_ENUM 1

typedef enum {
  Sunday = 0,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
} DayOfWeek;

#endif

#if !defined( SMK_HAS_STRPTIME )
extern "C"
char *
SMK_FUNCT_T
strptime( char * b, const char * fmt, struct tm * t );
#endif

bool
IsTimetDst( time_t val );


#include "SMKDateTimeUtils.ii"

/**  
   Detail Documentation
  
   Types:
  
  	enum DayOfWeek
  	    The days of the week where Sunday is 0 and Saturday is 6
  
   Variables:
  
  	extern const time_t SMK_GVAR_T SecPerMin;
  	    The number of seconds in a minute (60)
  
  	extern const time_t SMK_GVAR_T SecPerHour;
  	    The number of seconds in a hour (60 * 60)
  
  	extern const time_t SMK_GVAR_T SecPerDay;
  	    The number of seconds in a day (60 * 60 * 24)
  
  	extern const time_t SMK_GVAR_T SecPerYear;
  	    The number of seconds in a year (60 * 60 * 24 * 365)
  	
  	extern const time_t SMK_GVAR_T MinPerHour;
  	    The number of minutes in a hour (60)
  
  	extern const time_t SMK_GVAR_T MinPerDay;
  	    The number of minutes in a day (60 * 24)
  	
  	extern const time_t SMK_GVAR_T MinTimeT;
  	    The minimum time_t value
  
  	extern const time_t SMK_GVAR_T MaxTimeT;
  	    The maximum time_t value
  	
  	extern const time_t SMK_GVAR_T MinYear;
  	    The minimum year possible for a time_t value
  
  	extern const time_t SMK_GVAR_T MaxYear;
  	    The maximum year possible for a time_t value
  
  	extern const int    SMK_GVAR_T DaysInMonth[];
  	    The number of days in each month where Jan is month 0 so,
  	    DaysInMonth[1] == 28.
  
  	extern const int    SMK_GVAR_T MonthDayOfYear[];
  	    The number of days since the beging of the year for the first day
  	    of the month where Jan is month 0 so
  	    MonthDayOfYear[1] == 31 && MonthDayOfYear[2] == 58
  
  	extern const char * SMK_GVAR_T Months[];
  	    The full names of the months where Jan is month 0 so,
  	    Months[2] == "March"
  
  	extern const char * SMK_GVAR_T AbbrMonths[];
  	    The first three letters of the month where Jan is month 0 so,
  	    AbbrMonths[9] == "Oct"
  
  	extern const char * SMK_GVAR_T WeekDays[];
  	    The full name of the days of the week where sunday is 0 so,
  	    WeekDays[ 2 ] = "Tuesday"
  
  	extern const char * SMK_GVAR_T AbbrWeekDays[];
  	    The 3 char abbeviated names of the days of the week where
  	    sunday is 0, so AbbrWeekDays[ 4 ] == "Thu"
  
  	
   Functions:
  
    	long
    	SecInTimeT( long sec );
    	    return the second of the minute.
  
    	long
    	MinInTimeT( long sec )
    	    return the minute of the hour.
  
    	long
    	HourInTimeT( long sec )
    	    return the hour of the day.
  
    	long
    	HoursInTimeT( long sec )
    	    return the number of hours.
  
    	long
    	DaysInTimeT( long sec )
    	    return the number of days.
  
    	long
    	DateInTimeT( long sec )
    	    return the date portion only.
  
  	void
  	YYMMDDtoYYYYMMDD( char * dest, const char * src )
  	    convert 970304 to 19970304. if the first digit is < 5
  	    the year is assumed to be 2000, so 050304 will be 20050304.
  
  	bool
  	IsTimetDst( time_t val );
  	    Returns true if the time of val is between the 2 am First
  	    Sunday of April and 2 am the last Sunday of October
   Example:
  
   See Also:
  
   Files:
  
  	DateTimeUtils.hh
  	DateTimeUtils.ii
  	libStlUtils.a
  
   Documented Ver: 4.3
  
   Tested Ver: 4.3
  
   Revision Log:
**/
  
#endif //   ! def _DateTimeUtils_hh_ 

