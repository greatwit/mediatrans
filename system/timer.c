#include "timer.h"

#include "memory.h"

#include "os_api.h"

#include "list.h"

#include "hash.h"

#include "log.h"

#define MAX_TIMER_HASH_SIZE  (12)

typedef struct CTimer_t
{
	int32_t iTimerId;//定时器ID

	int32_t iExpireTimeInMileSeconds;//定时器超时时间

	int32_t iCurrentTimeInMileSeconds;//当前时间

	timer_callback_t callback;//定时器超时回调函数

	int32_t iIsActive;//是否活跃

	void *pUserData;//用户数据

	CHashItem HItem;//哈希表字段
	CListNode LNode;//链表字段
}CTimer;

//待回收定时器
typedef struct CGCTimer_t
{
	int32_t iTimerId;

	CListNode LNode;
}CGCTimer;

//定时器管理
typedef struct CTimerManager_t
{
	int32_t iInitFlag;//是否初始化

	CHashTbl *pTimerHashTbl;//哈希表

	int32u_t iTimerTid;//定时器工作线程

	int32_t iIsRunning;//是否正在运行

	CListNode *pTimerHead;//定时器工作链表

	CListNode *pGCTimerHead;//待删除定时器

	CMutex Mutex;//同步锁
	
}CTimerManager;

static CTimerManager fg_TimerManager = {
	0, 
	NULL, 
	0, 
	0, 
	NULL, 
	NULL
};

static int32_t check_timer_manager_working( void );

static int32_t init_timer_manager( void );

static void release_timer_manager( void );

static void *timer_task( void *pParam );

static void schedule_timer( void );

static void timer_gc( void );

//初始化定时器
int32_t init_timer( void )
{
	int32_t iRetCode = -1;

	if ( check_timer_manager_working() < 0 )
		iRetCode = init_timer_manager();
	else
		iRetCode = 0;

	return iRetCode;
}

//创建新定时器
int32_t create_timer( timer_callback_t callback, int32_t iTimeInSeconds, void *pUserData )
{
	int32_t iRetCode = -1;

	if ( check_timer_manager_working() < 0 )
		return iRetCode;

	if ( callback && iTimeInSeconds > 0 )
	{
		CTimer *pNewTimer = NULL;

		lock( fg_TimerManager.Mutex );

		pNewTimer = mem_malloc( sizeof(*pNewTimer) );
		if ( pNewTimer )
		{
			int32_t iTimerHandler = -1;

			memset( pNewTimer, 0x00, sizeof(*pNewTimer) );

			pNewTimer->callback = callback;
			pNewTimer->iExpireTimeInMileSeconds = iTimeInSeconds * 1000;
			pNewTimer->pUserData = pUserData;
			pNewTimer->iIsActive = 1;

			iTimerHandler = get_handle();
			while ( search_hash_tbl( fg_TimerManager.pTimerHashTbl, iTimerHandler ) )
				iTimerHandler = get_handle();

			if ( iTimerHandler >= 0 )
			{
				pNewTimer->HItem.iHashId = iTimerHandler;
				pNewTimer->iTimerId = iTimerHandler;

				if ( insert_hash_tbl( fg_TimerManager.pTimerHashTbl, &pNewTimer->HItem ) >= 0 )
				{
					if ( insert_list_node_rear( &(fg_TimerManager.pTimerHead), &(pNewTimer->LNode) ) >= 0 )
						iRetCode = iTimerHandler;
				}
			}

			if ( iRetCode < 0 )
			{
				if ( iTimerHandler >= 0 )
					remove_hash_tbl( fg_TimerManager.pTimerHashTbl, iTimerHandler );

				mem_free( pNewTimer );
				pNewTimer = NULL;
			}
		}

		unlock( fg_TimerManager.Mutex );
	}

	return iRetCode;
}

//删除定时器
int32_t destory_timer( int32_t iTimerId )
{
	int32_t iRetCode = -1;

	//LOGD( "destory_timer:-->" );

	if ( check_timer_manager_working() < 0 )
		return iRetCode;

	if ( iTimerId >= 0 )
	{
		CGCTimer *pGCTimer = NULL;

		lock( fg_TimerManager.Mutex );

		//删除定时器
		pGCTimer = mem_malloc( sizeof(*pGCTimer) );
		if ( pGCTimer )
		{
			memset( pGCTimer, 0x00, sizeof(*pGCTimer) );

			pGCTimer->iTimerId = iTimerId;

			if ( insert_list_node_rear( &(fg_TimerManager.pGCTimerHead), &(pGCTimer->LNode) ) >= 0 )
				iRetCode = 0;
			else
			{
				mem_free( pGCTimer );
				pGCTimer = NULL;
			}
		}

		unlock( fg_TimerManager.Mutex );
	}

	//LOGD( "destory_timer end." );

	return iRetCode;
}

//释放定时器资源
void release_timer( void )
{
	release_timer_manager();
}

//检查定时器是否已经初始化
static int32_t check_timer_manager_working( void )
{
	int32_t iRetCode = -1;

	if ( fg_TimerManager.iInitFlag )
		iRetCode = 0;

	return iRetCode;
}

//初始化定时器
static int32_t init_timer_manager( void )
{
	int32_t iRetCode = -1;

	if ( !fg_TimerManager.iInitFlag )
	{
		fg_TimerManager.pTimerHashTbl = create_hash_tbl( MAX_TIMER_HASH_SIZE );
		fg_TimerManager.Mutex = create_mutex();
		fg_TimerManager.pTimerHead = NULL;
		fg_TimerManager.pGCTimerHead = NULL;
		if ( fg_TimerManager.pTimerHashTbl && fg_TimerManager.Mutex )
		{
			fg_TimerManager.iIsRunning = 1;
			fg_TimerManager.iTimerTid = os_thread_create( timer_task, NULL, 0 );

			if ( fg_TimerManager.iTimerTid > 0 )
			{
				fg_TimerManager.iInitFlag = 1;

				iRetCode = 0;
			}
			else
				fg_TimerManager.iIsRunning = 0;
		}

		if ( iRetCode < 0 )
		{
			if ( fg_TimerManager.pTimerHashTbl )
				destory_hash_tbl( &fg_TimerManager.pTimerHashTbl );

			if ( fg_TimerManager.Mutex )
				destory_mutex( &fg_TimerManager.Mutex );
		}
	}
    else
        iRetCode = 0;

	return iRetCode;
}

 time_t GetTime_t(int year, int month, int day, int hour, int min, int sec)
{
    struct tm time;
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;

    return mktime(&time);
}

 struct tm AddTime(time_t nSourTime, time_t tm)
{
    struct tm tmTemp;
    nSourTime += tm;

    tmTemp = *localtime(&nSourTime); 
    tmTemp.tm_year += 1900;
    tmTemp.tm_mon += 1;

    return tmTemp;
}

//释放定时器
static void release_timer_manager( void )
{
	if ( check_timer_manager_working() >= 0 )
	{
		if ( fg_TimerManager.iTimerTid > 0 )
		{
			fg_TimerManager.iIsRunning = 0;
			os_thread_destory( fg_TimerManager.iTimerTid );
			fg_TimerManager.iTimerTid = -1;
		}

		if ( fg_TimerManager.pTimerHashTbl )
			destory_hash_tbl( &fg_TimerManager.pTimerHashTbl );

		if ( fg_TimerManager.Mutex )
			destory_mutex( &fg_TimerManager.Mutex );
        
        fg_TimerManager.iInitFlag = 0;
	}
}

//定时器工作线程
static void *timer_task( void *pParam )
{
	while ( fg_TimerManager.iIsRunning )
	{
		timer_gc();

		schedule_timer();
		
		os_sleep( 100 );
	}

	return NULL;
}

static void schedule_timer( void )
{
	CListNode *pTempLNode = NULL;
	CTimer *pTimer = NULL;

	lock( fg_TimerManager.Mutex );

	pTempLNode = fg_TimerManager.pTimerHead;
	while ( pTempLNode )
	{
		pTimer = CONTAINER_OF( LNode, pTempLNode, CTimer );
		if ( pTimer )
		{
			if ( pTimer->iIsActive )
			{
				pTimer->iCurrentTimeInMileSeconds += 100;
				
				if ( pTimer->iCurrentTimeInMileSeconds >= pTimer->iExpireTimeInMileSeconds )
				{
					if ( pTimer->callback( pTimer->iTimerId, pTimer->pUserData ) >= 0 )
						pTimer->iCurrentTimeInMileSeconds = 0;
					else
					{
						//删除定时器
						CGCTimer *pGCTimer = mem_malloc( sizeof(*pGCTimer) );

						//LOGD( "schedule_timer:going to delete timer.\r\n" );
						if ( pGCTimer )
						{
							memset( pGCTimer, 0x00, sizeof(*pGCTimer) );
	
							pGCTimer->iTimerId = pTimer->iTimerId;
	
							if ( insert_list_node_rear( &(fg_TimerManager.pGCTimerHead), &(pGCTimer->LNode) ) < 0 )
							{
								mem_free( pGCTimer );
								pGCTimer = NULL;
							}
							else
							{
								pTimer->iIsActive = 0;
								//LOGD( "schedule_timer:add timer to delete list ok.\r\n" );
							}
						}
					}
				}

			}
		}
		
		pTempLNode = pTempLNode->Next;
	}

	unlock( fg_TimerManager.Mutex );
}

static void timer_gc( void )
{
	CListNode *pTempLNode = NULL, *pRemoveLNode = NULL;
	CGCTimer *pGCTimer = NULL;

	lock( fg_TimerManager.Mutex );

	pTempLNode = fg_TimerManager.pGCTimerHead;
	while ( pTempLNode )
	{
		pGCTimer = CONTAINER_OF( LNode, pTempLNode, CGCTimer );
		if ( pGCTimer )
		{
			CHashItem *pRemoveHashItem = remove_hash_tbl( fg_TimerManager.pTimerHashTbl, pGCTimer->iTimerId );

			if ( pRemoveHashItem )
			{
				CTimer *pRemoveTimer = NULL;

				//LOGD( "timer_gc:deleting timer.\r\n" );

				pRemoveTimer = CONTAINER_OF( HItem, pRemoveHashItem, CTimer );

				if ( remove_list_node( &(fg_TimerManager.pTimerHead), &(pRemoveTimer->LNode) ) >= 0 )
				{
					mem_free( pRemoveTimer );
					pRemoveTimer = NULL;
				}
				#if (LOG_SUPPORT)
				else
					LOGD( "timer_gc:remove timer from working list failed." );
				#endif
			}
			else
				LOGD( "timer_gc:search timer hash table failed.\r\n" );
		}
		
		pTempLNode = pTempLNode->Next;
	}

	pTempLNode = fg_TimerManager.pGCTimerHead;
	while ( pTempLNode )
	{
		pGCTimer = CONTAINER_OF( LNode, pTempLNode, CGCTimer );

		pTempLNode = pTempLNode->Next;

		mem_free( pGCTimer );
		pGCTimer = NULL;
	}
	fg_TimerManager.pGCTimerHead = NULL;
	
#if 0
	if ( fg_TimerManager.pGCTimerHead )
	{
		char logBuf[128];
		sprintf( logBuf, "timer_gc:Next-->%u, Prev-->%u\r\n", fg_TimerManager.pGCTimerHead->Next, fg_TimerManager.pGCTimerHead->Prev );
		LOGD( logBuf );
	}
#endif

	unlock( fg_TimerManager.Mutex );

}

