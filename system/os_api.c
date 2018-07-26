/**************************************************************************************************
* File Name: os_api.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/
#include "os_api.h"
#include "hash.h"
#include "memory.h"

#include "log.h"


#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#if (__OS_LINUX__||__OS_IOS__)
#include <arpa/inet.h>
#endif

/***************************************************************************************************
* mutex begin...
****************************************************************************************************/


CMutex create_mutex( void )
{

#if (__OS_WIN32__)

	CRITICAL_SECTION *pstNewMutex = (CRITICAL_SECTION *)mem_malloc( sizeof(CRITICAL_SECTION) );
	if ( pstNewMutex )
	{
		memset( pstNewMutex, 0x00, sizeof(*pstNewMutex) );
		
		InitializeCriticalSection( pstNewMutex );

		return (void *)pstNewMutex;
	}
#elif (__OS_LINUX__)
	CMutex newMutex = NULL;

	newMutex = mem_malloc( sizeof(*newMutex) );
	if ( newMutex )
	{
		memset( newMutex, 0x00, sizeof(*newMutex) );

		if ( pthread_mutex_init( newMutex, NULL ) >= 0 )
			return newMutex;
	}
	
#elif (__OS_IOS__)
    CMutex newMutex = NULL;
    
	newMutex = mem_malloc( sizeof(*newMutex) );
	if ( newMutex )
	{
		memset( newMutex, 0x00, sizeof(*newMutex) );
        
		if ( pthread_mutex_init( newMutex, NULL ) >= 0 )
			return newMutex;
	}
#endif

	return NULL;
}

int32_t init_mutex( CMutex pMutex )
{
	int32_t iRetCode = -1;

	//LOGD("init_mutex:----------------->");

	if ( pMutex )
	{
		memset( pMutex, 0x00, sizeof(*pMutex) );
		
#if (__OS_WIN32__)
		InitializeCriticalSection( pMutex );

		iRetCode = 0;
#elif (__OS_LINUX__)
		//LOGD("if ( pthread_mutex_init( pMutex, NULL ) >= 0 )");
		if ( pthread_mutex_init( pMutex, NULL ) >= 0 )
		{
			//LOGD("init mutex ok..........");
			iRetCode = 0;
		}
#elif (__OS_IOS__)
        if ( pthread_mutex_init( pMutex, NULL ) >= 0 )
		{
			//LOGD("init mutex ok..........");
			iRetCode = 0;
		}
#endif
	}

	//LOGD("init_mutex end<-----------------");

	return iRetCode;
}

int32_t lock( CMutex mutex )
{
#if (__OS_WIN32__)
	int32_t iRetCode = -1;

	if ( mutex )
		EnterCriticalSection( mutex );

	iRetCode = 0;

	return iRetCode;
#elif (__OS_LINUX__)
	int32_t iRetCode = -1;

	if ( mutex )
	{
		pthread_mutex_lock( mutex );
		iRetCode = 0;
	}
	
	return iRetCode;
#elif (__OS_IOS__)
    int32_t iRetCode = -1;
    
	if ( mutex )
	{
		pthread_mutex_lock( mutex );
		iRetCode = 0;
	}
	
	return iRetCode;
#endif
}

int32_t unlock( CMutex mutex )
{
#if (__OS_WIN32__)
	int32_t iRetCode = -1;

	if ( mutex )
		LeaveCriticalSection(mutex);

	iRetCode = 0;

	return iRetCode;
#elif (__OS_LINUX__)
	int32_t iRetCode = -1;

	if ( mutex )
	{
		pthread_mutex_unlock( mutex );
		iRetCode = 0;
	}

	return iRetCode;
#elif (__OS_IOS__)
    int32_t iRetCode = -1;
    
	if ( mutex )
	{
		pthread_mutex_unlock( mutex );
		iRetCode = 0;
	}
    
	return iRetCode;
#endif
}

int32_t destory_mutex( CMutex *pMutex )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)

	if ( pMutex )
	{
		mem_free( *pMutex );
		*pMutex = NULL;

		iRetCode = OP_SUCCESS;
	}
	
#elif (__OS_LINUX__)

	if ( pMutex && *pMutex )
	{
		pthread_mutex_destroy( *pMutex );

		mem_free( *pMutex );
		*pMutex = NULL;

		iRetCode = OP_SUCCESS;
	}
#elif (__OS_IOS__)
    if ( pMutex && *pMutex )
	{
		pthread_mutex_destroy( *pMutex );

		mem_free( *pMutex );
		*pMutex = NULL;
        
		iRetCode = OP_SUCCESS;
	}
#endif

	return iRetCode;
}
/***************************************************************************************************
* mutex end...
****************************************************************************************************/


/***************************************************************************************************
* thread begin...
****************************************************************************************************/


typedef struct CThread_t
{
	int32_t iIsRunning;

	os_thread_t thread;

	void *pParam;

	int32_t iQuitFlag;

	CHashItem HItem;
}CThread;

typedef struct CThreadManager_t
{
	CHashTbl *pHashTbl;

	CMutex Mutex;

	int32_t iInitFlag;
}CThreadManager;

static CThreadManager fg_ThreadManager = {
	NULL, 
	NULL, 
	0
};

static void *comm_thread_proc( void * );
static int32_t thread_init( void );

int32u_t os_thread_create( os_thread_t fthread, void *pParam, int32_t iPriority )
{
	int32u_t iRetCode = 0;
	CThread *pThread = NULL;

	if ( !fg_ThreadManager.iInitFlag )
	{
		if ( thread_init() < 0 )
			return iRetCode;
	}

#if (__OS_WIN32__)

	lock( fg_ThreadManager.Mutex );

	pThread = (CThread *)mem_malloc(sizeof(*pThread));

	if ( pThread )
	{
		memset( pThread, 0x00, sizeof(*pThread) );

		pThread->iIsRunning = 1;
		pThread->thread = fthread;
		pThread->pParam = pParam;
		pThread->iQuitFlag = 0;
		if ( CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)comm_thread_proc, (void *)pThread, 0, &pThread->HItem.iHashId ) < 0 )
		{
			mem_free( pThread );
			pThread = NULL;
		}
		else
		{
			if ( OP_SUCCESS == insert_hash_tbl( fg_ThreadManager.pHashTbl, &pThread->HItem ) )
				iRetCode = pThread->HItem.iHashId;
		}
	}

	unlock( fg_ThreadManager.Mutex );
	
#elif (__OS_LINUX__)

	lock( fg_ThreadManager.Mutex );

	pThread = (CThread *)mem_malloc(sizeof(*pThread));

	if ( pThread )
	{
		memset( pThread, 0x00, sizeof(*pThread) );

		pThread->iIsRunning = 1;
		pThread->thread = fthread;
		pThread->pParam = pParam;
		pThread->iQuitFlag = 0;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

		if ( pthread_create( (pthread_t *)&pThread->HItem.iHashId, &attr, comm_thread_proc, (void *)pThread ) < 0 )
		{
			mem_free( pThread );
			pThread = NULL;
		}
		else
		{
			if ( OP_SUCCESS == insert_hash_tbl( fg_ThreadManager.pHashTbl, &pThread->HItem ) )
			{
				iRetCode = pThread->HItem.iHashId;

				//printf( "os_thread_create: iRetCode-->%u.\r\n", iRetCode );
			}
			#if 0//(LOG_SUPPORT)
			else
				printf( "if ( OP_SUCCESS == insert_hash_tbl( fg_ThreadManager.pHashTbl, &pThread->HItem ) )\r\n" );
			#endif			
		}
		pthread_attr_destroy(&attr);
		
		
	}

	unlock( fg_ThreadManager.Mutex );


#elif (__OS_IOS__)
    lock( fg_ThreadManager.Mutex );
    
	pThread = (CThread *)mem_malloc(sizeof(*pThread));
    
	if ( pThread )
	{
		memset( pThread, 0x00, sizeof(*pThread) );
        
		pThread->iIsRunning = 1;
		pThread->thread = fthread;
		pThread->pParam = pParam;
		pThread->iQuitFlag = 0;
        
		if ( pthread_create( (pthread_t *)&pThread->HItem.iHashId, NULL, comm_thread_proc, (void *)pThread ) < 0 )
		{
			mem_free( pThread );
			pThread = NULL;
		}
		else
		{
			if ( OP_SUCCESS == insert_hash_tbl( fg_ThreadManager.pHashTbl, &pThread->HItem ) )
			{
				iRetCode = pThread->HItem.iHashId;
                
				printf( "os_thread_create: iRetCode-->%u.\r\n", iRetCode );
			}
#if (LOG_SUPPORT)
			else
				printf( "if ( OP_SUCCESS == insert_hash_tbl( fg_ThreadManager.pHashTbl, &pThread->HItem ) )\r\n" );
#endif
		}
        
		
		
	}
    
	unlock( fg_ThreadManager.Mutex );
#endif

	return iRetCode;
}

int32_t os_thread_destory( int32u_t iThreadId )
{
	int32_t iRetCode = OP_FAILURE;
	const CHashItem *pSearchHashItem = NULL;

	if ( !fg_ThreadManager.iInitFlag )
		return iRetCode;

	lock( fg_ThreadManager.Mutex );
		
	pSearchHashItem = search_hash_tbl( fg_ThreadManager.pHashTbl, iThreadId );

	unlock( fg_ThreadManager.Mutex );
	
	if ( pSearchHashItem )
	{
		CThread *pThread = CONTAINER_OF(HItem,pSearchHashItem,CThread);
		const CHashItem *pRemoveHashItem = NULL;
		
		while ( !pThread->iQuitFlag )
		{
			//LOGD("waiting for thread quit..............");
			os_sleep( 10 );
		}

		lock( fg_ThreadManager.Mutex );
		
		pRemoveHashItem = remove_hash_tbl( fg_ThreadManager.pHashTbl, iThreadId );

		if ( pRemoveHashItem )
		{
			if ( pThread )
			{
				mem_free( pThread );
				pThread = NULL;

				iRetCode = OP_SUCCESS;
			}
		}

		unlock( fg_ThreadManager.Mutex );
	}
	
	return iRetCode;
}

static void *comm_thread_proc( void *pParam )
{
	void *pRetVal = NULL;
	CThread *pThread = (CThread *)pParam;

	if ( pThread )
	{
		if ( pThread->thread )
		{
			pThread->thread( pThread->pParam );
			
			pThread->iIsRunning = 0;
			pThread->iQuitFlag = 1;

			os_thread_destory( pThread->HItem.iHashId );
		}

		pRetVal = (void *)pThread->HItem.iHashId;
	}

	return pRetVal;
}

static int32_t thread_init( void )
{
	int32_t iRetCode = OP_FAILURE;

	if ( !fg_ThreadManager.iInitFlag )
	{
		fg_ThreadManager.pHashTbl = create_hash_tbl( 32 );
		if ( fg_ThreadManager.pHashTbl )
		{
			fg_ThreadManager.Mutex = create_mutex();
			if ( fg_ThreadManager.Mutex )
			{
				fg_ThreadManager.iInitFlag = 1;

				iRetCode = OP_SUCCESS;
			}
			else
			{
				destory_hash_tbl( &fg_ThreadManager.pHashTbl );
			}
		}
	}
	else
		iRetCode = OP_SUCCESS;

	return iRetCode;
}

/***************************************************************************************************
* thread end.
****************************************************************************************************/

void os_sleep( int32_t iMileSecond )
{
#if (__OS_WIN32__)
	Sleep( iMileSecond );
#elif (__OS_LINUX__)
	usleep( 1000 * iMileSecond );
#elif (__OS_IOS__)
    usleep( 1000 * iMileSecond );
#endif
}

//条件锁接口

CCondMutex *create_cond_mutex( void )
{
	CCondMutex *pNewCondMutex = NULL;

	pNewCondMutex = mem_malloc( sizeof(*pNewCondMutex) );
	if ( pNewCondMutex )
	{
#if (__OS_WIN32__)
		memset( pNewCondMutex, 0x00, sizeof(*pNewCondMutex) );

		pNewCondMutex->Mutex = create_mutex(  );
		if ( pNewCondMutex->Mutex )
		{
			// Create an auto-reset event.
			 pNewCondMutex->events_[SIGNAL] = CreateEvent (NULL,  // no security
												FALSE, // auto-reset event
												FALSE, // non-signaled initially
												NULL); // unnamed
			
			 // Create a manual-reset event.
			 pNewCondMutex->events_[BROADCAST] = CreateEvent (NULL,  // no security
												   TRUE,  // manual-reset
												   FALSE, // non-signaled initially
												   NULL); // unna
		}
		else
		{
			mem_free( pNewCondMutex );
			pNewCondMutex = NULL;
		}
#endif
	}

	return pNewCondMutex;
}

int32_t signal_cond_mutex( CCondMutex *pCondMutex )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pCondMutex )
	{
#if (__OS_WIN32__)
		// Try to release one waiting thread.
		 PulseEvent (pCondMutex->events_[SIGNAL]);
#else

#endif

		iRetCode = OP_SUCCESS;
	}

	return iRetCode;
}

int32_t broadcast_cond_mutex( CCondMutex *pCondMutex )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pCondMutex )
	{
#if (__OS_WIN32__)
		// Try to release all waiting threads.
		PulseEvent (pCondMutex->events_[BROADCAST]);

		iRetCode = OP_SUCCESS;
#else
		
#endif
	}

	return iRetCode;
}


int32_t wait_cond_mutex( CCondMutex *pCondMutex )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pCondMutex )
	{
#if (__OS_WIN32__)
		// Release the <external_mutex> here and wait for either event
		 // to become signaled, due to <pthread_cond_signal> being
		 // called or <pthread_cond_broadcast> being called.
		 unlock(pCondMutex->Mutex);
		 WaitForMultipleObjects (2, // Wait on both <events_>
								 pCondMutex->events_,
								 FALSE, // Wait for either event to be signaled
								 INFINITE); // Wait "forever"

		 iRetCode = OP_SUCCESS;
		
		 // Reacquire the mutex before returning.
		 lock(pCondMutex->Mutex);
#endif
	}

	return iRetCode;
}

void destory_cond_mutex( CCondMutex *pCondMutex )
{
	if ( pCondMutex )
	{
		
#if (__OS_WIN32__)
		destory_mutex( &pCondMutex->Mutex );
		CloseHandle( pCondMutex->events_[SIGNAL] );
		CloseHandle( pCondMutex->events_[BROADCAST] );
#endif
	}
}

int get_handle( void )
{
#define MAX_RANDOM_NUM  (0xefffffff)

	int iRet = 100;

	//printf( "get_handle:-->\r\n" );

	srand((int)time(0));
	
	iRet = rand();

	iRet = iRet > 0 ? iRet : -iRet;

	iRet = iRet % MAX_RANDOM_NUM;

	iRet += 50;

	return iRet;
}

//事件接口

LONG VOS_CreateEvent(VOS_Event *pstVosEvent)
{
	LONG result = VOS_OK;

#ifndef  WIN32

	result = pthread_mutex_init(&pstVosEvent->EventMutex, 0);
	if( VOS_OK != result )
	{
		return VOS_ERR_SYS;
	}

	result = pthread_cond_init(&pstVosEvent->EventCond, 0);
	if( VOS_OK != result )
	{
		pthread_mutex_destroy(&pstVosEvent->EventMutex);
		return VOS_ERR_SYS;
	}

#else

	pstVosEvent->EventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if( VOS_NULL == pstVosEvent->EventHandle )    
	{
		(void)CloseHandle(pstVosEvent->EventHandle);
		return VOS_ERR_SYS;
	}

#endif

	return result ;
}

LONG VOS_WaitEvent(VOS_Event *pstVosEvent, LONG lTimeOut)
{
	long lResult = VOS_OK;

#ifndef  WIN32

	struct timespec ts;
	struct timeval  tv;

	gettimeofday(&tv, 0);
	ts.tv_sec  = tv.tv_sec  + lTimeOut/1000;
	ts.tv_nsec = (tv.tv_usec + (lTimeOut %1000)*1000) * 1000; 


	(void)pthread_mutex_lock(&pstVosEvent->EventMutex);
	if( 0 != lTimeOut )
	{
		lResult = pthread_cond_timedwait(&pstVosEvent->EventCond,
			&pstVosEvent->EventMutex,&ts);
	}
	else
	{
		lResult = pthread_cond_wait(&pstVosEvent->EventCond,
			&pstVosEvent->EventMutex);
	}
	(void)pthread_mutex_unlock(&pstVosEvent->EventMutex);

	if( VOS_OK != lResult )
	{
		switch(lResult)
		{
		case ETIMEDOUT:
			{
				lResult = VOS_ERR_QUE_TIMEOUT;
				break;
			}

		default:
			{
				lResult = VOS_ERR_SYS;
				break;
			}
		}
	}

#else

	lResult = (long)WaitForSingleObject(pstVosEvent->EventHandle, (unsigned long)lTimeOut);/*lint !e613*/ //无此问题
	switch(lResult)
	{
	case WAIT_TIMEOUT:
		{
			lResult = VOS_ERR_QUE_TIMEOUT;
			break;
		}

	case WAIT_ABANDONED:
		{
			lResult = VOS_ERR_SYS;
			break;
		}
	case WAIT_OBJECT_0:
		{
			lResult = VOS_OK;
			break;
		}
	default:
		{
			lResult = VOS_ERR_SYS;                
		}
		break;                        
	}

#endif

	return lResult;
}/*lint !e818*/ //使用公共平台源代码，是否Const不做要求

LONG VOS_SetEvent(VOS_Event *pstVosEvent)
{
	LONG lResult = VOS_OK;

#ifndef  WIN32

	lResult = pthread_cond_signal(&pstVosEvent->EventCond);
	if(VOS_OK != lResult)
	{
		lResult = VOS_ERR_SYS;                
	}

#else

	lResult = SetEvent(pstVosEvent->EventHandle);/*lint !e613*/ //无此问题

	if(VOS_OK != lResult)
	{
		lResult = VOS_OK;                
	}
	else
	{
		lResult = VOS_ERR_SYS;
	}

#endif

	return lResult ;
}/*lint !e818*/ //无此问题
LONG VOS_ReSetEvent(VOS_Event *pstVosEvent)
{
	LONG lResult = VOS_OK;

#ifndef  WIN32

	lResult = pthread_mutex_init(&pstVosEvent->EventMutex, 0);
	if( VOS_OK != lResult )
	{
		return VOS_ERR_SYS;
	}

	lResult = pthread_cond_init(&pstVosEvent->EventCond, 0);
	if( VOS_OK != lResult )
	{
		pthread_mutex_destroy(&pstVosEvent->EventMutex);
		return VOS_ERR_SYS;
	}

#else

	lResult = ResetEvent(pstVosEvent->EventHandle);

	if(VOS_OK != lResult)
	{
		lResult = VOS_OK;                
	}
	else
	{
		lResult = VOS_ERR_SYS;
	}

#endif

	return lResult ;
}/*lint !e818*/ //无此问题

LONG VOS_DestroyEvent(VOS_Event *pstVosEvent )
{
	if ( VOS_NULL == pstVosEvent ) 
	{
		return VOS_ERR_PARAM ;
	}

#ifndef  WIN32
	pthread_cond_destroy(&pstVosEvent->EventCond);
	pthread_mutex_destroy(&pstVosEvent->EventMutex);
#else
	(void)CloseHandle(pstVosEvent->EventHandle);
#endif

	return VOS_OK ;
}/*lint !e818*/ //无此问题

//信号量接口
CSem create_sem( int iMaxVal )
{
#if (__OS_WIN32__)
	CSem newSem = NULL;

	newSem = CreateSemaphore(NULL, iMaxVal, iMaxVal,NULL);//;

	return newSem;
#elif (__OS_LINUX__)

	CSem pNewSem = NULL;

	pNewSem = mem_malloc(sizeof(*pNewSem));
	if ( pNewSem )
	{
		memset( pNewSem, 0x00, sizeof(*pNewSem) );

		if ( sem_init( pNewSem, iMaxVal, iMaxVal ) >= 0 )
			return pNewSem;
	}
	
	return NULL;
#elif (__OS_IOS__)
    CSem pNewSem = NULL;
    
	pNewSem = mem_malloc(sizeof(*pNewSem));
	if ( pNewSem )
	{
		memset( pNewSem, 0x00, sizeof(*pNewSem) );
        
		if ( sem_init( pNewSem, iMaxVal, iMaxVal ) >= 0 )
			return pNewSem;
	}
	
	return NULL;
#endif
}

int32_t wait_sem( CSem sem )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)

	if ( WaitForSingleObject(sem,INFINITE) >= 0 )//等待信号量
		iRetCode = OP_SUCCESS;
#elif (__OS_LINUX__)

	if ( sem )
		if ( sem_wait( sem ) >= 0 )
			iRetCode = OP_SUCCESS;
#elif (__OS_IOS__)
    if ( sem )
		if ( sem_wait( sem ) >= 0 )
			iRetCode = OP_SUCCESS;
#endif

	return iRetCode;
}

int32_t post_sem( CSem sem )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)
	if ( ReleaseSemaphore(sem ,1,NULL) )//释放对信号量的所有权
		iRetCode = OP_SUCCESS;
#elif (__OS_LINUX__)

	if ( sem )
	{
		if ( sem_post( sem ) >= 0 )
			iRetCode = OP_SUCCESS;
	}
#elif (__OS_IOS__)
    if ( sem )
	{
		if ( sem_post( sem ) >= 0 )
			iRetCode = OP_SUCCESS;
	}

#endif

	return iRetCode;
}

void destory_sem( CSem sem )
{
	if ( sem )
	{
		mem_free( sem );
		sem = NULL;
	}
}

int16u_t net2hosts( int16u_t iNetData )
{
	int16u_t iRetCode = 0;

	iRetCode = ntohs( iNetData );

	return iRetCode;
}

int16u_t host2nets( int16u_t iHostData )
{
	int16u_t iRetCode = 0;

	iRetCode = htons( iHostData );

	return iRetCode;
}

int32u_t net2hostl( int32u_t iNetData )
{
	int32u_t iRetCode = 0;

	iRetCode = ntohl( iNetData );

	return iRetCode;
}

int32u_t host2netl( int32u_t iHostData )
{
	int32u_t iRetCode = 0;

	iRetCode = htonl( iHostData );

	return iRetCode;
}

int32_t get_ip_by_domain(int8_t* sDestIp, int8_t* sDomain)
{
    int iRest = -1;

    struct hostent *stHost = NULL;
    int8_t *sIpaddr = NULL;

    if((NULL == sDestIp)||(NULL == sDomain))
    {
        //to-do
        return iRest;
    }

    if((stHost=gethostbyname((const char*)sDomain))==NULL)
    {
        //to-do
        return iRest;
    }


    sIpaddr = inet_ntoa(*((struct in_addr *)stHost->h_addr_list[0]));

    strcpy(sDestIp, sIpaddr);

    return 1;
}

unsigned long os_get_timetick_value()
{

#if (__OS_WIN32__)
	return GetTickCount();

#elif (__OS_LINUX__)
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);

#else
    struct timeval tv;
    gettimeofday( &tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif

}

//线程全局变量接口
int32_t os_thread_createKey(void* pParam)
{
	int32_t iRetCode = OP_SUCCESS;
#if (__OS_WIN32__)
	//暂时不处理
#elif (__OS_LINUX__)
	pthread_key_create(&fg_ThreadKey, pParam);
#elif (__OS_IOS__)
    pthread_key_create(&fg_ThreadKey, pParam);
#else
	iRetCode = OP_FAILURE;
#endif

	return iRetCode;
}

int32_t os_thread_setValue(CThreadKey key, int32_t* pValue)
{
	int32_t iRetCode = OP_SUCCESS;
	
#if (__OS_WIN32__)
	//暂时不处理
#elif (__OS_LINUX__)
	iRetCode = pthread_setspecific(key, pValue);
#elif (__OS_IOS__)
	iRetCode = pthread_setspecific(key, pValue);
#else
	iRetCode = OP_FAILURE;
#endif
	
	return iRetCode;
}

void* os_thread_getValue(CThreadKey key)
{

#if (__OS_WIN32__)
	//暂时不处理
#elif (__OS_LINUX__)
	return pthread_getspecific(key);
#elif (__OS_IOS__)
	return pthread_getspecific(key);
#endif
	return NULL;
}

int32_t os_thread_deleteKey()
{
	int32_t iRetCode = OP_SUCCESS;
	
#if (__OS_WIN32__)
	//暂时不处理
#elif (__OS_LINUX__)
	pthread_key_delete(fg_ThreadKey);
#elif (__OS_IOS__)
	pthread_key_delete(fg_ThreadKey);
#else
	iRetCode = OP_FAILURE;
#endif
	
	return iRetCode;
}



////////////////////线程私有的全局变量(每个线程独有的全局变量)///
//CThreadKey fg_ThreadKey;
//extern  int  *My_Errno( void );
//#define g_SdkErrNo  (*My_Errno())

int *My_Errno(void)
{	
#if (__OS_WIN32__)
	return &fg_ThreadKey;//如果是win32,未进行处理(需要实现)
#else
	int *pErrNo = (int *)os_thread_getValue(fg_ThreadKey);
	if(NULL == pErrNo)
	{
		pErrNo = (int *)malloc(sizeof(int));
		*pErrNo = -1;
		os_thread_setValue(fg_ThreadKey, pErrNo);
	}
	return pErrNo;
#endif
}
///////////////////////////////////////////////////////////////

int8_t *get_error_string(int32_t iErrorCode)
{
	int8_t *pRetCode = NULL;

		switch(iErrorCode)
		{
			case SDK_ERROR_NOT_INIT:
			case SDK_ERROR_NOT_SET_WWW_INFO:	
			case SDK_ERROR_CONNECT_WEB_SERVER://链接WEB服务器失败
			case SDK_ERROR_SEND_DATA://发送数据失败
			case SDK_ERROR_CONNECT_TO_DEVICE://链接设备失败
			case SDK_ERROR_OPEN_CHANNEL://打开通道失败
			case SDK_ERROR_CLOSE_CHANNEL://关闭通道失败
			case SDK_ERROR_INIT_DB_FAIL://初始化数据库失败
			case SDK_ERROR_NO_SIGNAL://没有网络 （这种情况是手机没有wifi信号）
			case SDK_ERROR_INPUT_PARAM://参数有误
			case SDK_ERROR_DEVICE_OFFLINE://设备不在线 
			case SDK_ERROR_RESPONSE_TIMEOUT://响应超时
			case SDK_ERROR_VERIFY://用户密码认证失败
				sprintf(fg_ErrorInfoBuf, "{\"flag\":\"%d\", \"msg\":\"\"}", iErrorCode);
				break;
			default:
				sprintf(fg_ErrorInfoBuf, "{\"flag\":\"%d\", \"msg\":\"\"}", SYSTEM_ERROR);
				break;
		}		

	pRetCode = fg_ErrorInfoBuf;
	return pRetCode;
}

int32_t get_error_code( void )
{
#if (LOG_SUPPORT)
	LOGD("get_error_code: fg_ThreadKey: %d,errno: %d\n", fg_ThreadKey, g_SdkErrNo);
#endif
	return g_SdkErrNo;
}

void set_error_code(int32_t iErrorCode)
{
#if (LOG_SUPPORT)
	LOGD("set_error_code:fg_ThreadKey: %d,errno: %d\n", fg_ThreadKey, g_SdkErrNo);
#endif
	g_SdkErrNo = iErrorCode;
}

