/**************************************************************************************************
* File Name: epoll.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#include "epoll.h"

#include "net_api.h"

#include "memory.h"

#include <errno.h>

#include "log.h"


#if (__OS_LINUX__)

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
#if (LOG_SUPPORT)
		//LOGD( "init:-->\r\n" );
#endif

	if ( pNetEngine )
	{
		pNetEngine->iWorkingTid = os_thread_create( fNetWorkingThread, pNetEngine, OS_THREAD_PRIORITY_NORMAL );
		if ( pNetEngine->iWorkingTid > 0 )
		{
			pNetEngine->iEPollId = epoll_create( EPOLL_SIZE );
			if ( pNetEngine->iEPollId > 0 )
				iRetCode = OP_SUCCESS;

			//printf( "pNetEngine->iEPollId-->%d.\r\n", pNetEngine->iEPollId );
		}

		//printf( "pNetEngine->iWorkingTid-->%u.\r\n", pNetEngine->iWorkingTid );
	}

	return iRetCode;
}

static void release( struct CNetEngine_t *pNetEngine )
{
#if (LOG_SUPPORT)
	//LOGD( "release:-->\r\n" );
#endif
	if ( pNetEngine )
	{
		pNetEngine->iIsRunning = 0;
		os_thread_destory( pNetEngine->iWorkingTid );
	}
}

static int32_t add_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;
#if (LOG_SUPPORT)
		//	LOGD( "add_socket:-->\r\n" );
#endif

	if ( pNetEngine && iSocketId > 0 )
	{
		struct epoll_event ev;
		int32_t iOpRet = -1;

		memset( &ev, 0x00, sizeof(ev) );
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = iSocketId;

		iOpRet = epoll_ctl( pNetEngine->iEPollId, EPOLL_CTL_ADD, iSocketId, &ev );
		if ( iOpRet >= 0 )
			iRetCode = OP_SUCCESS;
		#if (LOG_SUPPORT)
		else
		{

			LOGD("iSocketId-->%d, iOpRet-->%d, %s", iSocketId, iOpRet, strerror(errno));
			LOGD("!iOpRet = epoll_ctl( pNetEngine->iEPollId, EPOLL_CTL_ADD failed?????");
		}
		#endif
	}

	return iRetCode;
}

static int32_t remove_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;


	if ( pNetEngine && iSocketId > 0 )
	{	
		struct epoll_event ev;
		int32_t iOpRet = -1;

		memset( &ev, 0x00, sizeof(ev) );
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = iSocketId;

		//close_socket( iSocketId );
		iOpRet = epoll_ctl( pNetEngine->iEPollId, EPOLL_CTL_DEL, iSocketId, &ev );
		iRetCode = OP_SUCCESS;
		#if 0
		if ( iOpRet >= 0 )
			iRetCode = OP_SUCCESS;
		#if (LOG_SUPPORT)
		else
		{
			char logBuf[128];
			sprintf(logBuf, "iSocketId-->%d, iOpRet-->%d, %s.", iSocketId, iRetCode, strerror(errno) );
			LOGD(logBuf);
			LOGD("!if ( epoll_ctl( pNetEngine->iEPollId, EPOLL_CTL_DEL, iSocket failed??????????");
		}
		#endif
		#endif
	}
	#if (LOG_SUPPORT)
	else
	{
		LOGD("pNetEngine-->%u, iSocketId-->%d.", pNetEngine, iSocketId);
		LOGD("!if ( pNetEngine && iSocketId > 0 ) failed????????????????");
	}
	#endif

	return iRetCode;

}

extern int32_t on_net_event_notify( int32_t iSocketId, int32_t iNetEvent, void *pUserData );

#if 0
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

#endif

static void *fNetWorkingThread( void *pParam )
{
#define MAX_EPOLL_WAIT_TIME_IN_MILESECONDS  (500)//500ms
	void *pRetVal = NULL;

	CNetEngine *pNetEngine = (CNetEngine *)pParam;

	if ( !pNetEngine )
		return pRetVal;

	//LOGD( "fNetWorkingThread:-->\r\n" );
	
	while ( pNetEngine->iIsRunning )
	{
		int32_t iActiveCount = epoll_wait( pNetEngine->iEPollId, pNetEngine->Events, EPOLL_SIZE, MAX_EPOLL_WAIT_TIME_IN_MILESECONDS );

#if 0
		printf( "pNetEngine->iReactorId-->%d.\r\n", pNetEngine->iReactorId );
		printf( "pNetEngine->iWorkingTid-->%d.\r\n", pNetEngine->iWorkingTid );
		printf( "pNetEngine->iEPollId-->%d.\r\n", pNetEngine->iEPollId );

		printf( "pNetEngine->iIsRunning-->%d.\r\n", pNetEngine->iIsRunning );
		
		printf( "iActiveCount-->%d.\r\n", iActiveCount );
		#endif

		if ( iActiveCount <= 0 )
			continue ;
		else
		{
			int32_t i = 0;

			for ( i = 0; i < iActiveCount; i++ )
			{
				//printf( "pNetEngine->Events[i].data.fd-->%d.\r\n", pNetEngine->Events[i].data.fd );
				#if (LOG_SUPPORT)
				LOGD("iActiveCount-->%d, socket fd -->%d.\r\n", 
					 iActiveCount, pNetEngine->Events[i].data.fd);
				#endif

				if ( on_net_event_notify( pNetEngine->Events[i].data.fd, NET_EVENT_DATA_NOTIFY, pNetEngine->pUserData ) < 0 )
				{
				}
			}
		}
	}

	pRetVal = (void *)pNetEngine->iWorkingTid;

	on_net_event_notify( 0xff, NET_EVENT_DATA_NOTIFY, pNetEngine->pUserData );

	LOGD( "epoll engine quits...\r\n" );

	return pRetVal;	
}


#endif

