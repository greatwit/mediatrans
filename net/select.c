/**************************************************************************************************
* File Name: select.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/


#include "select.h"


#if (__OS_WIN32__)

#include <winsock.h>

#include "memory.h"

#include "net_api.h"

#include <time.h>

#include "os_api.h"

#include "log.h"

#pragma comment(lib, "ws2_32.lib")

static int32_t init( struct CNetEngine_t *pNetEngine );
static void release( struct CNetEngine_t *pNetEngine );
static int32_t add_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId );
static int32_t remove_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId );

static void *fNetWorkingThread( void *pParam );	

CNetEngine *create_engine( void *pUserData )
{
	CNetEngine *pNewNetEngine = NULL;

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
			FD_ZERO (&pNetEngine->active_fd_set);

			iRetCode = OP_SUCCESS;
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
	int32_t iRetCode = OP_FAILURE;

	if ( pNetEngine && iSocketId > 0 )
	{
		FD_SET (iSocketId, &pNetEngine->active_fd_set);

		iRetCode = OP_SUCCESS;
	}

	return iRetCode;
}

static int32_t remove_socket( struct CNetEngine_t *pNetEngine, int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pNetEngine && iSocketId > 0 )
	{
		FD_CLR(iSocketId, &pNetEngine->active_fd_set);

		//close_socket( iSocketId );

		iRetCode = OP_SUCCESS;
	}

	return iRetCode;

}

extern int32_t on_net_event_notify( int32_t iSocketId, int32_t iNetEvent, void *pUserData );
static void *fNetWorkingThread( void *pParam )
{
	void *pRetVal = NULL;
	CNetEngine *pNetEngine = (CNetEngine *)pParam;
	fd_set read_fd_set;	
	struct timeval tv;

	if ( !pNetEngine )
		return pRetVal;

	//printf( "fNetWorkingThread:-->\r\n" );

	FD_ZERO (&read_fd_set);

	memset( &tv, 0x00, sizeof(tv) );
	tv.tv_sec = 0;      //second
    tv.tv_usec = 500;      //ms 
      
	while ( pNetEngine->iIsRunning )
	{
		int32_t iNActivated = 0;

		//printf( "select engine is running...\r\n" );

		read_fd_set = pNetEngine->active_fd_set;
		if ( read_fd_set.fd_count <= 0 )
		{
			os_sleep( 10 );

			continue ;
		}

		iNActivated = select(FD_SETSIZE, &read_fd_set, NULL, NULL, &tv);
		if ( iNActivated < 0 )//等待500毫秒， 直到有套接字事件为此
		{
			LOGD( "select failed.\r\n" );

			
		}
		else
		{
			if ( iNActivated > 0 )
			{
				int i = 0;

				for ( i = 0; i < FD_SETSIZE; i++ )
				{
					if ( read_fd_set.fd_array[i] > 0 )
					{
						if ( FD_ISSET( read_fd_set.fd_array[i], &read_fd_set ) )
						{
							if ( on_net_event_notify( read_fd_set.fd_array[i], NET_EVENT_DATA_NOTIFY, pNetEngine->pUserData ) < 0 )
							{
				
							}
						}
					}
				}
			}
		}
	}

	pRetVal = (void *)pNetEngine->iWorkingTid;

	LOGD( "select engine quits...\r\n" );

	return pRetVal;	
}


#endif

