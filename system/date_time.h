#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

#include "typedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct CDateTime_t
{
	int32_t nYear;
	int32_t nMonth;
	int32_t nDay;
	int32_t nHour;
	int32_t nMinute;
	int32_t nSecond;
	int32_t nMileSeconds;
}CDateTime;

EXPORT_API int32_t get_curr_gm_datetime( CDateTime *pstDateTime );

EXPORT_API int32_t get_curr_local_datetime( CDateTime *pstDateTime );

EXPORT_API int64_t get_time( const int32_t iYear, const int32_t iMonth, const int32_t iDay, 
							const int32_t iHour, const int32_t iMinute, const int32_t iSecond );

EXPORT_API int32_t get_gm_datetime( int64_t iTotalTimeInSeconds, CDateTime *pOutDateTime );

EXPORT_API int32_t get_local_datetime( int64_t iTotalTimeInSeconds, CDateTime *pOutDateTime );

#ifdef __cplusplus
}
#endif


#endif/* __DATE_TIME_H__ */
