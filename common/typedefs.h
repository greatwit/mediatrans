/**************************************************************************************************
* File Name: typedefs.h
* Writer: xx
* Create Date: 2013-3-25 12:36
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

#if defined(WIN32)
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//操作返回值
#define OP_SUCCESS  (0)
#define OP_FAILURE  (-1)


#define CONTAINER_OF(member, ptr, type)	\
						((type *)(((unsigned char *)ptr) - (int)&( ((type *)0)->member )))

//基本类型定义
#if defined(WIN32)
typedef char int8_t;
#else
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
#endif


typedef unsigned char int8u_t;
typedef short int16_t;
typedef unsigned short int16u_t;
typedef int int32_t;
typedef unsigned int int32u_t;
typedef long long int64_t;
typedef unsigned long long int64u_t;
typedef float float_t;
typedef double float64_t;


#define uint8_t unsigned char
#define int16_t short
#define uint16_t unsigned short
#define int32_t int
#define uint32_t unsigned int 


#if defined(_WIN32) && !defined(__MINGW32__) && (!defined(_MSC_VER) || _MSC_VER<1600)
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

#if !defined(WIN32)
#ifdef _UNICODE
typedef char * LPCTSTR;
#else
typedef char * LPCTSTR;
#endif
//typedef int32_t LONG;
#define LONG int32_t
#endif

#define DEV_SDK_API
/*
#ifdef WIN32

#ifdef  DEV_SDK_EXPORTS
#define DEV_SDK_API __declspec(dllexport)
#else
#define DEV_SDK_API __declspec(dllimport)
#endif

#else

#define DEV_SDK_API
#define WINAPI

#endif  //WIN32
*/

#ifdef __cplusplus
}
#endif

#endif/* __TYPEDEFS_H__ */

