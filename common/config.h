#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef linux
#define __OS_WIN32__  (0)
#define __OS_LINUX__  (1)
#define __OS_IOS__    (0)
#elif defined WIN32
#define __OS_WIN32__  (1)
#define __OS_LINUX__  (0)
#define __OS_IOS__    (0)
#else
#define __OS_WIN32__  (0)
#define __OS_LINUX__  (0)
#define __OS_IOS__    (1)
#endif


#define DEBUG_SUPPORT (1)
#define CAP_SUPPORT   (0)
#define SDK_DEBUG     (0)

#if SDK_DEBUG
#include <android/log.h>
#endif

/*
//系统平台宏定义
#if defined(WIN32)
//WINDOWS平台
#define __OS_WIN32__  (1)
#elif defined(__GNUC__)
//Linux平台(Android, x86 Linux)
#define __OS_LINUX__  (1)
#else
//IOS平台?
#define __OS_IOS__  (1)

#endif
*/

#if (__OS_WIN32__)
#define MAX_SOCKET_SIZE  (64)
#elif (__OS_LINUX__)
#define MAX_SOCKET_SIZE  (64)
#elif (__OS_IOS__)
#define MAX_SOCKET_SIZE  (64)
#endif

#if (__OS_WIN32__)
#define EXPORT_API  __declspec( dllexport )
#define IMPORT_API  __declspec( dllimport )
#else
#define EXPORT_API  
#define IMPORT_API 
#endif

#ifdef __cplusplus
}
#endif

#endif/* __CONFIG_H__ */

