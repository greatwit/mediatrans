#include "kqueue.h"

#include "os_api.h"

#include "net_api.h"

#include "memory.h"

#if (__OS_IOS__)

#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int32_t init( struct CNetEngine_t *pNetEngine );
static void release( struct CNetEngine_t *pNetEngine );
static int32_t add_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId );
static int32_t remove_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId );
static void *fNetWorkingThread( void *pParam );

CNetEngine *create_engine( void *pUserData )
{
	CNetEngine *pNewNetEngine = NULL;

#if (LOG_SUPPORT)
	//LOGD( "create_engine:-->\r\n" );
#endif

	pNewNetEngine = mem_malloc( sizeof(*pNewNetEngine) );
	if ( pNewNetEngine )
	{
		memset( pNewNetEngine, 0x00, sizeof(*pNewNetEngine) );

		pNewNetEngine->init = init;
		pNewNetEngine->release = release;
		pNewNetEngine->add_socket = add_socket;
		pNewNetEngine->remove_socket = remove_socket;
		pNewNetEngine->pUserData = pUserData;
		pNewNetEngine->iIsRunning = 1;
	}

	return pNewNetEngine;
}

int32_t destory_engine( CNetEngine **ppNetEngine )
{
	int32_t iRetCode = OP_FAILURE;

#if (LOG_SUPPORT)
	//LOGD( "destory_engine:-->\r\n" );
#endif

	if ( ppNetEngine && *ppNetEngine )
	{
		mem_free( *ppNetEngine );
		*ppNetEngine = NULL;

		iRetCode = OP_SUCCESS;
	}

	return iRetCode;
}

static int32_t init( struct CNetEngine_t *pNetEngine )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pNetEngine )
	{
		pNetEngine->iWorkingTid = os_thread_create( fNetWorkingThread, pNetEngine, OS_THREAD_PRIORITY_NORMAL );
		if ( pNetEngine->iWorkingTid > 0 )
		{
			pNetEngine->iKQueueId = kqueue();			
			if ( pNetEngine->iKQueueId > 0 )
				iRetCode = OP_SUCCESS;

			if ( iRetCode < 0 )
			{
				if ( pNetEngine->iWorkingTid > 0 )
				{
					pNetEngine->iIsRunning = 0;
					os_thread_destory( pNetEngine->iWorkingTid );
					pNetEngine->iWorkingTid = -1;
				}
			}
		}
	}

	return iRetCode;
}

static void release( struct CNetEngine_t *pNetEngine )
{
	if ( pNetEngine )
	{
		pNetEngine->iIsRunning = 0;
		os_thread_destory( pNetEngine->iWorkingTid );
	}
}

static int32_t add_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId )
{
	struct kevent changes[1];
	int ret = -1;

	if ( pNetEngine && iSocketId >= 0 )
	{
		EV_SET( &changes[0], iSocketId, EVFILT_READ, EV_ADD, 0, 0, NULL );
		
		ret = kevent( pNetEngine->iKQueueId, changes, 1, NULL, 0, NULL );
	}
	
	return 0;
}

static int32_t remove_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId )
{
	int32_t iRetCode = -1, ret = -1;
    struct kevent changes[1];

	if ( pNetEngine && iSocketId > 0 )
	{
		EV_SET( &changes[0], iSocketId, EVFILT_READ, EV_DELETE, 0, 0, NULL );
		
		ret = kevent( pNetEngine->iKQueueId, changes, 1, NULL, 0, NULL );

		iRetCode = 0;
	}

	return iRetCode;
}

extern int32_t on_net_event_notify( int32_t iSocketId, int32_t iNetEvent, void *pUserData );
static void *fNetWorkingThread( void *pParam )
{
#define MAX_EVENT_COUNT  (1000)
	void *pRetVal = NULL;
	struct kevent events[MAX_EVENT_COUNT];
	struct timespec timeout;
	int ret = -1;
	
	CNetEngine *pNetEngine = (CNetEngine *)pParam;

	if ( !pNetEngine )
		return pRetVal;

	memset( &timeout, 0x00, sizeof(timeout) );
	timeout.tv_nsec = 500 * 1000;//500MS³¬Ê±
	while ( pNetEngine->iIsRunning )
	{
		ret = kevent( pNetEngine->iKQueueId, NULL, 0, events, MAX_EVENT_COUNT, &timeout ); 
		
		if ( ret > 0 )
		{
			int32_t i = 0;
			
			for ( i = 0; i < ret; i++ )
			{
				if ( on_net_event_notify(
						events[i].ident, 
						NET_EVENT_DATA_NOTIFY, 
						pNetEngine->pUserData ) < 0 )
				{
			
				}
			}
		}
	}

	pRetVal = (void *)pNetEngine->iWorkingTid;
	
	return pRetVal;
}

#endif

