#ifndef __TIMER_H__
#define __TIMER_H__


#include "typedefs.h"
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif


typedef int32_t (*timer_callback_t)( int32_t iTimerId, void *pUserData );

EXPORT_API int32_t init_timer( void );

EXPORT_API int32_t create_timer( timer_callback_t callback, int32_t iTimeInSeconds, void *pUserData );

EXPORT_API int32_t destory_timer( int32_t iTimerId );

EXPORT_API void release_timer( void );


EXPORT_API time_t GetTime_t(int year, int month, int day, int hour, int min, int sec);

EXPORT_API struct tm AddTime(time_t nSourTime, time_t tm);


#ifdef __cplusplus
}
#endif


#endif/* __TIMER_H__ */

