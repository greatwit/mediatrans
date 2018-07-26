#include "date_time.h"
#include <time.h>

int32_t get_curr_gm_datetime( CDateTime *pstDateTime )
{
	int iRetCode = -1;
	struct tm *p;
	time_t tm = 0;
	
	int year, month, day, week, hour, minute, second;	

	tm = time(NULL);
	p = gmtime(&tm);
	if ( p )
	{
		year = 1900 + p->tm_year;
		month = p->tm_mon + 1;
		day = p->tm_mday;	
		week = p->tm_wday;
		hour = p->tm_hour;
		minute = p->tm_min;
		second = p->tm_sec; 
		
		pstDateTime->nYear = year;
		pstDateTime->nMonth = month;
		pstDateTime->nDay = day;
		pstDateTime->nHour = hour;
		pstDateTime->nMinute = minute;
		pstDateTime->nSecond = second;

		
		iRetCode = 0;
	}

	return iRetCode;
}

EXPORT_API int64_t get_time( const int32_t iYear, const int32_t iMonth, const int32_t iDay, 
							const int32_t iHour, const int32_t iMinute, const int32_t iSecond )
{
	int64_t iRetCode = -1;

	struct tm stDateTime;

	memset( &stDateTime, 0x00, sizeof(stDateTime) );

	stDateTime.tm_year = iYear - 1900;
	stDateTime.tm_mon = iMonth - 1;
	stDateTime.tm_mday = iDay;
	stDateTime.tm_hour = iHour;
	stDateTime.tm_min = iMinute;
	stDateTime.tm_sec = iSecond;

	iRetCode = mktime( &stDateTime );//转换为utc时间,即会比本地(东八区)时间少8小时
//#if (__OS_LINUX__)
	iRetCode += (8 * 60 * 60);//加上8小时的时区差
//#endif
	return iRetCode;
}

int32_t get_gm_datetime( int64_t iTotalTimeInSeconds, CDateTime *pstDateTime )
{
	int iRetCode = -1;
	struct tm *p;
	
	int year, month, day, week, hour, minute, second;	

	p = gmtime(&iTotalTimeInSeconds);
	if ( p && pstDateTime )
	{
		year = 1900 + p->tm_year;
		month = p->tm_mon + 1;
		day = p->tm_mday;	
		week = p->tm_wday;
		hour = p->tm_hour;
		minute = p->tm_min;
		second = p->tm_sec; 
		
		pstDateTime->nYear = year;
		pstDateTime->nMonth = month;
		pstDateTime->nDay = day;
		pstDateTime->nHour = hour;
		pstDateTime->nMinute = minute;
		pstDateTime->nSecond = second;

		
		iRetCode = 0;
	}

	return iRetCode;
}

int32_t get_curr_local_datetime( CDateTime *pstDateTime )
{
	int iRetCode = -1;
	struct tm *p;
	time_t tm = 0;
	
	int year, month, day, week, hour, minute, second;	

	tm = time(NULL);
	p = localtime(&tm);
	if ( p )
	{
		year = 1900 + p->tm_year;
		month = p->tm_mon + 1;
		day = p->tm_mday;	
		week = p->tm_wday;
		hour = p->tm_hour;
		minute = p->tm_min;
		second = p->tm_sec; 
		
		pstDateTime->nYear = year;
		pstDateTime->nMonth = month;
		pstDateTime->nDay = day;
		pstDateTime->nHour = hour;
		pstDateTime->nMinute = minute;
		pstDateTime->nSecond = second;

		
		iRetCode = 0;
	}

	return iRetCode;

}

int32_t get_local_datetime( int64_t iTotalTimeInSeconds, CDateTime *pstDateTime )
{
	int iRetCode = -1;
	struct tm *p;

	int year, month, day, week, hour, minute, second;	

	p = localtime(&iTotalTimeInSeconds);
	if ( p && pstDateTime )
	{
		year = 1900 + p->tm_year;
		month = p->tm_mon + 1;
		day = p->tm_mday;	
		week = p->tm_wday;
		hour = p->tm_hour;
		minute = p->tm_min;
		second = p->tm_sec; 
		
		pstDateTime->nYear = year;
		pstDateTime->nMonth = month;
		pstDateTime->nDay = day;
		pstDateTime->nHour = hour;
		pstDateTime->nMinute = minute;
		pstDateTime->nSecond = second;

		
		iRetCode = 0;
	}

	return iRetCode;
}
