#include "log.h"

#if (LOG_SUPPORT)

#include "os_api.h"
#include "date_time.h"
#include <stdio.h>

#define ANDROID_SUPPORT (0)

#if (ANDROID_SUPPORT)
#include <android/log.h>
#endif

#if (__OS_IOS__)

#endif

static int32_t fg_IsLogEnabled = 0;

static int32_t fg_LogPriority = LOG_PRIORITY_INFO;

static int32_t fg_LogType = LOG_TYPE_FILE;

static FILE *fg_LogFileHandle = NULL;

static CMutex pfg_LogMutex = NULL;

void enable_log( int32_t iIsEnabled, int32_t iPriority )
{
	fg_IsLogEnabled = iIsEnabled;
	fg_LogPriority = iPriority;
}

int32_t get_log_priority( void )
{
	return fg_LogPriority;
}

//设置日志类型
int32_t set_log( int32_t iLogType, void *pParam )
{
	int32_t iRetCode = -1;

	if ( !(iLogType >= LOG_TYPE_FILE && iLogType < LOG_TYPE_END) )
		return iRetCode;

	fg_LogType = iLogType;
	switch ( fg_LogType )
	{
	case LOG_TYPE_FILE:
		{
			CDateTime stDateTime;

			memset( &stDateTime, 0x00, sizeof(stDateTime) );
			if ( get_curr_local_datetime( &stDateTime ) >= 0 )
			{
				int8_t oldLogName[128] = { 0x00, };
				int8_t currLogName[128] = { 0x00, };
#if 1
				sprintf( oldLogName, "%s_%04d-%02d-%02d %02d %02d:%02d.log", (const char *)pParam, 
										stDateTime.nYear, stDateTime.nMonth, stDateTime.nDay, 
										stDateTime.nHour, stDateTime.nMinute, stDateTime.nSecond
										 );
#else
				sprintf( oldLogName, "%s_test.log" );
#endif

				sprintf( currLogName, "%s.log", (const char *)pParam );

				//file_rename( currLogName, oldLogName );
				
				fg_LogFileHandle = fopen( currLogName, "a+" );
				if ( fg_LogFileHandle )
				{
				}
			}
		}
		break ;

	default:
		{

		}break ;
	}

	return iRetCode;
}

int32_t release_log( int32_t iLogType, void *pParam)
{
    int32_t iRetCode = -1;

    if ( !(iLogType >= LOG_TYPE_FILE && iLogType < LOG_TYPE_END) )
        return iRetCode;

    fg_LogType = iLogType;
    switch ( fg_LogType )
    {
    case LOG_TYPE_FILE:
        if ( fg_LogFileHandle )
        {
            fclose(fg_LogFileHandle);
            fg_LogFileHandle = NULL;
        }
        break;

    case LOG_TYPE_NET:
        break;
    case LOG_TYPE_CONSOLE:
        break;
    default:
        break;
    }
    return iRetCode;
}

int32_t render_log(int32_t iPriority, const char *pMsg)
{
    switch(iPriority)
    {
    case LOG_TYPE_FILE:
        break;

    case LOG_TYPE_NET:
        {
        }
        break ;

    case LOG_TYPE_CONSOLE:
        {
        }
        break;
    case LOG_TYPE_FILE_CONSOLE:
        break;
    default:
        break;
    }
    return 0;
}

int32_t gie_printf(int32_t iPriority, const char *pMsg)
{
    int8_t bDateTimeBuf[128] = {0};
    int8_t bLogBuf[1024] = {0};
    int8_t bPriorityBuf[32]={0};
    CDateTime stDateTime;
    memset( &stDateTime, 0x00, sizeof(stDateTime) );
    if ( get_curr_local_datetime( &stDateTime ) >= 0 )
        sprintf( bDateTimeBuf, "%04d-%02d-%02d %02d:%02d:%02d", 
        stDateTime.nYear, stDateTime.nMonth, stDateTime.nDay, 
        stDateTime.nHour, stDateTime.nMinute, stDateTime.nSecond );

        switch(iPriority)
        {
            case LOG_PRIORITY_EMERG:
                strcpy(bPriorityBuf, "EMERG:");
                break ;
            case LOG_PRIORITY_ALERT:
                strcpy(bPriorityBuf, "ALERT:");
                break ;
            case LOG_PRIORITY_CRIT:
                strcpy(bPriorityBuf, "CRIT:");
                break ;
            case LOG_PRIORITY_ERR:
                strcpy(bPriorityBuf, "ERR:");
                break ;
            case LOG_PRIORITY_WARNING:
                strcpy(bPriorityBuf, "WARNING:");
                break ;
            case LOG_PRIORITY_NOTICE:
                strcpy(bPriorityBuf, "NOTICE:");
                break ;
            case LOG_PRIORITY_INFO:
                strcpy(bPriorityBuf, "INFO:");
                break ;
            case LOG_PRIORITY_DEBUG:
                strcpy(bPriorityBuf, "DEBUG:");
                break ;
            default:
                break;
        }

#if (__OS_LINUX__)
#if (ANDROID_SUPPORT)
    sprintf( bLogBuf, "%s %s %s\r\n", bDateTimeBuf, bPriorityBuf, pMsg );
    __android_log_print(ANDROID_LOG_DEBUG,"GIE_NET_SDK",bLogBuf);
#endif
#elif (__OS_IOS__)
    sprintf( bLogBuf, "%s %s %s\r\n", bDateTimeBuf, bPriorityBuf, pMsg );
    printf(bLogBuf);
#else
    sprintf( bLogBuf, "%s %s %s\r\n", bDateTimeBuf, bPriorityBuf, pMsg );
    printf(bLogBuf);
#endif
return 0;
}

int32_t sys_log( int32_t iPriority, const char *pMsg )
{
	int32_t iRetCode = -1;
	int8_t bLogBuf[1024] = {0};
	int32_t iMsgLen = 0;
	int8_t bDateTimeBuf[128] = {0};
	CDateTime stDateTime;
	

	if ( !pMsg || !fg_IsLogEnabled )
		return iRetCode;

	iMsgLen = strlen(pMsg);
	if ( iMsgLen >= sizeof(bLogBuf) - 128 )
		return iRetCode;

	memset( &stDateTime, 0x00, sizeof(stDateTime) );
	if ( get_curr_local_datetime( &stDateTime ) >= 0 )
		sprintf( bDateTimeBuf, "%04d-%02d-%02d %02d:%02d:%02d", 
								stDateTime.nYear, stDateTime.nMonth, stDateTime.nDay, 
								stDateTime.nHour, stDateTime.nMinute, stDateTime.nSecond );

	switch ( fg_LogType )
	{
	case LOG_TYPE_FILE:
		{
			switch ( iPriority )
			{
			case LOG_PRIORITY_EMERG:
				{
					sprintf( bLogBuf, "%s EMERG: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );
				}break ;
			case LOG_PRIORITY_ALERT:
				{

					sprintf( bLogBuf, "%s ALERT: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );
				}break ;
			case LOG_PRIORITY_CRIT:
				{

					sprintf( bLogBuf, "%s CRIT: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );
				}break ;
			case LOG_PRIORITY_ERR:
				{

					sprintf( bLogBuf, "%s ERR: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );
				}break ;
			case LOG_PRIORITY_WARNING:
				{

					sprintf( bLogBuf, "%s WARNING: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );

				}break ;
			case LOG_PRIORITY_NOTICE:
				{

					sprintf( bLogBuf, "%s NOTICE: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );

				}break ;
			case LOG_PRIORITY_INFO:
				{

					sprintf( bLogBuf, "%s INFO: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );
				}break ;
			case LOG_PRIORITY_DEBUG:
				{
					sprintf( bLogBuf, "%s DEBUG: %s\r\n", bDateTimeBuf, pMsg );
					fwrite( bLogBuf, 1, strlen(bLogBuf), fg_LogFileHandle );

				}break ;
			default:
				{
                    printf( "Unknown log priority?????????????" );
				}break ;
			}

			fflush( fg_LogFileHandle );
	
			iRetCode = 0;

		}break ;

	case LOG_TYPE_CONSOLE:
		{
			switch ( iPriority )
			{
			    case LOG_PRIORITY_EMERG:
				    {
    #if (__OS_LINUX__)
    #if (ANDROID_SUPPORT)
					    sprintf( bLogBuf, "%s EMERG: %s\r\n", bDateTimeBuf, pMsg );
					    __android_log_print(ANDROID_LOG_DEBUG,"GIE_NET_SDK",bLogBuf);
    #endif
    #elif (__OS_IOS__)
                        sprintf( bLogBuf, "%s DEBUG: %s\r\n", bDateTimeBuf, pMsg );
                       printf(bLogBuf);
    #endif

				    }break ;

			    default:
			    {
                    printf( "Unknown log priority???????????????" );
			    }break ;
			}

		}break ;
	default:
		{
		}break ;
	}

	return iRetCode;
}

//控制台日志接口
int32_t console_log( int32_t iPriority, const char *pMsg )
{
    int32_t iRetCode = -1;
    int8_t bLogBuf[1024] = {0};
    int32_t iMsgLen = 0;
    int8_t bDateTimeBuf[128] = {0};
    CDateTime stDateTime;


    if ( !pMsg || !fg_IsLogEnabled )
        return iRetCode;

    iMsgLen = strlen(pMsg);
    if ( iMsgLen >= sizeof(bLogBuf) - 128 )
        return iRetCode;


    memset( &stDateTime, 0x00, sizeof(stDateTime) );
    if ( get_curr_local_datetime( &stDateTime ) >= 0 )
        sprintf( bDateTimeBuf, "%04d-%02d-%02d %02d:%02d:%02d", 
        stDateTime.nYear, stDateTime.nMonth, stDateTime.nDay, 
        stDateTime.nHour, stDateTime.nMinute, stDateTime.nSecond );


            switch ( iPriority )
            {
            case LOG_PRIORITY_EMERG:
                {
#if (__OS_LINUX__)
#if (ANDROID_SUPPORT)
                    sprintf( bLogBuf, "%s EMERG: %s\r\n", bDateTimeBuf, pMsg );
                    __android_log_print(ANDROID_LOG_DEBUG,"GIE_NET_SDK",bLogBuf);
#endif
#elif (__OS_IOS__)
                    sprintf( bLogBuf, "%s DEBUG: %s\r\n", bDateTimeBuf, pMsg );
                    printf(bLogBuf);
#endif

                }break ;

            default:
                {
                    printf( "Unknown log priority???????????????" );
                }break ;
            }

    return iRetCode;
}

#endif

