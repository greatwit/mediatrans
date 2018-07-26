/**************************************************************************************************
* File Name: epoll.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __EPOLL_H__
#define __EPOLL_H__



#include "os_api.h"
#include "typedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif


#if (__OS_LINUX__)

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

#define EPOLL_SIZE  (100)


typedef struct CNetEngine_t
{
	int32_t iReactorId;
	
	int32_t (*init)( struct CNetEngine_t *pNetEngine );

	int32_t (*add_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	int32_t (*remove_socket)( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

	void (*release)( struct CNetEngine_t *pNetEngine );

	int32u_t iWorkingTid;//ÍøÂçÏß³ÌID

	int32_t iEPollId;//ÍøÂçÒýÇæID

	struct epoll_event Events[EPOLL_SIZE];          

	int32_t iIsRunning;

	void *pUserData;
}CNetEngine;

CNetEngine *create_engine( void *pUserData );

int32_t destory_engine( CNetEngine **ppNetEngine );


#endif

#ifdef __cplusplus
}
#endif

#endif/* __EPOLL_H__ */
