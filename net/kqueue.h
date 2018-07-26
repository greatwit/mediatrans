/**************************************************************************************************
* File Name: kqueue.h
* Writer: xx
* Create Date: 2013-3-25 12:36
* Update Table:
*----------------------------------------------------------------
* 
*
*
*资源：https://developer.apple.com/library/mac/#documentation/Darwin/Conceptual/FSEvents_ProgGuide/KernelQueues/KernelQueues.html
***************************************************************************************************/
#ifndef __KQUEUE_H__
#define __KQUEUE_H__

#include "typedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if (__OS_IOS__)

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct CNetEngine_t
{
	int32_t iReactorId;
	
	int32_t (*init)( struct CNetEngine_t *pNetEngine );

	int32_t (*add_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	int32_t (*remove_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	void (*release)( struct CNetEngine_t *pNetEngine );

	int32u_t iWorkingTid;//网络线程ID

	int32_t iKQueueId;//网络引擎ID

	int32_t iIsRunning;

	void *pUserData;
}CNetEngine;

CNetEngine *create_engine( void *pUserData );

int32_t destory_engine( CNetEngine **ppNetEngine );


#endif

#ifdef __cplusplus
}
#endif


#endif/* __KQUEUE_H__ */

