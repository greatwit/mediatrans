/**************************************************************************************************
* File Name: select.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __SELECT_H__
#define __SELECT_H__

#include "typedefs.h"
#include "os_api.h"

#if (__OS_WIN32__)
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif


#if (__OS_WIN32__)

typedef struct CNetEngine_t
{
	int32_t iReactorId;
	
	int32_t (*init)( struct CNetEngine_t *pNetEngine );

	int32_t (*add_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	int32_t (*remove_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	void (*release)( struct CNetEngine_t *pNetEngine );

	int32u_t iWorkingTid;//网络线程ID

	int32_t iIsRunning;

	fd_set active_fd_set;//WINDOWS平台最多64个

	void *pUserData;
}CNetEngine;

EXPORT_API CNetEngine *create_engine( void *pUserData );

EXPORT_API int32_t destory_engine( CNetEngine **ppNetEngine );

#endif

#ifdef __cplusplus
}
#endif

#endif/* __SELECT_H__ */
