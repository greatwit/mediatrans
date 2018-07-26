#ifndef __LOG_H__
#define __LOG_H__

#include "typedefs.h"

#define LOG_SUPPORT  1



#ifdef __cplusplus
extern "C"
{
#endif

#if (LOG_SUPPORT)

#if (__OS_LINUX__)
#define ANDROID_SUPPORT  (1)
#include <android/log.h>
#endif


	/* C files should define LOG_TAG before including this header */
#define LOG_TAG "HN/JNI/main"
#ifndef LOG_TAG
# error You must define LOG_TAG
#endif

#ifdef ANDROID_SUPPORT
# define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
# define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARNING,LOG_TAG,__VA_ARGS__)
#else
# define LOGD(...)  (void)0
# define LOGV(...)  (void)0
#define  LOGI(...)  (void)0
#define  LOGE(...)  (void)0
#define  LOGW(...)  (void)0
#endif //end android support


typedef enum
{
	LOG_PRIORITY_EMERG, //紧急情况，需要立即通知技术人员。
	LOG_PRIORITY_ALERT, //应该被立即改正的问题，如系统数据库被破坏，ISP连接丢失。
	LOG_PRIORITY_CRIT, //重要情况，如硬盘错误，备用连接丢失。
	LOG_PRIORITY_ERR, //错误，不是非常紧急，在一定时间内修复即可。
	LOG_PRIORITY_WARNING, //警告信息，不是错误，比如系统磁盘使用了85%等。
	LOG_PRIORITY_NOTICE, //不是错误情况，也不需要立即处理。
	LOG_PRIORITY_INFO, //情报信息，正常的系统消息，比如骚扰报告，带宽数据等，不需要处理。
	LOG_PRIORITY_DEBUG, //包含详细的开发情报的信息，通常只在调试一个程序时使用。

	LOG_END
}C_LOG_PRIORITY;

typedef enum
{
	LOG_TYPE_FILE, //文件日志
	LOG_TYPE_NET,//网络日志(暂不用)
	LOG_TYPE_CONSOLE, //控制台打印
	LOG_TYPE_FILE_CONSOLE,//控制台and文件打印

	LOG_TYPE_END
}C_LOG_TYPE;

//启用， 关闭日志
EXPORT_API void enable_log( int32_t iIsEnabled, int32_t iPriority );

//设置日志类型
EXPORT_API int32_t set_log( int32_t iLogType, void *pParam );

EXPORT_API int32_t release_log( int32_t iLogType, void *pParam);

//日志接口
EXPORT_API int32_t sys_log( int32_t iPriority, const char *pMsg );

//控制台日志接口
EXPORT_API int32_t console_log( int32_t iPriority, const char *pMsg );

EXPORT_API int32_t get_log_priority( void );

//日志接口宏 
#define LOGD1(msg)                                                                   \
	do	                                                                    \
{	                                                                    \
	char rreeerrlogBuf[1024] = {0};	                                    \
	int32_t iMsgLen = strlen(msg);	                                    \
	if ((iMsgLen < 512) && strlen(__FILE__) < 256)	                    \
{	                                                                \
	sprintf( rreeerrlogBuf, "%s:%d %s", __FILE__, __LINE__, msg );	\
	sys_log( get_log_priority(), rreeerrlogBuf );	                \
}	                                                                \
}while (0)	

//控制台调试接口宏 
#define CONSOLED(msg)  \
    do	\
{	\
    char rreeerrlogBuf[1024] = {0};	\
    int32_t iMsgLen = strlen(msg);	\
    if ((iMsgLen < 512) && strlen(__FILE__) < 256)	\
{	\
    sprintf( rreeerrlogBuf, "%s:%d %s", __FILE__, __LINE__, msg );	\
    console_log( LOG_PRIORITY_DEBUG, rreeerrlogBuf );	\
}	\
}while (0)	


#else

#define enable_log(a,b) 
#define set_log(a,b) 
#define sys_log(a) 
#define LOGD1(msg) 

#endif

#ifdef __cplusplus
}
#endif


#endif/* __LOG_H__ */
