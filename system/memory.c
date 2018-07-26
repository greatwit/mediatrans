#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "os_api.h"

#include "log.h"
#include "hash.h"

#if (!DEBUG_SUPPORT)

void *mem_malloc_ext( int32_t iMemSize, const int8_t *pFileName, const int32_t iLineNo )
{
	void *pNewMem = NULL;


	pNewMem = malloc( iMemSize );


	return pNewMem;

}

int32_t mem_free( void *pMemBuf )
{
	int32_t iRetCode = -1;

	
	if ( pMemBuf )
	{
		free( pMemBuf );

		iRetCode = 0;
	}

	return iRetCode;
}

#else

#define SHOW_MEM_INFO_SUPPORT  (0)

#define MAX_MEM_ITEM_SIZE  (128)

#define MAX_MEM_ALLOC_SIZE  (128)
#define MIDDLE_MEM_ALLOC_SIZE  (MAX_MEM_ALLOC_SIZE/2)
#define SMALL_MEM_ALLOC_SIZE  (MIDDLE_MEM_ALLOC_SIZE/2)

typedef struct CMemItem_t
{
	void *pMemBuf;

	int iMemBufLen;

	int8_t btMemInfo[512];

	CHashItem HItem;
}CMemItem;

static CHashItem *pfg_UsedMemItemArray[MAX_MEM_ITEM_SIZE] = { NULL, };
static CHashItem *pfg_AvailableMemItemArray[MAX_MEM_ITEM_SIZE] = { NULL, };

static int32_t fg_InitFlag = 0;//内存模块是否初始化
static MUTEX_TYPE fg_MemLocker;//内存模块锁
static int32_t fg_iTotalMemCounter = 0;//总共申请的内存
static int32_t fg_iUsedMemCounter = 0;//正在使用的内存个数
static int32_t fg_iFreeMemCounter = 0;//申请空闲内存个数
static int32_t fg_iTotalMemInBytes = 0;//总共分配的内存
static int32_t fg_iTotalFreeMemInBytes = 0;//
static int32_t fg_iTotalUsedMemInBytes = 0;

//内存地址为HASH ID
static CHashTbl fg_UsedMemTbl = 
{
	pfg_UsedMemItemArray, 
	0, 
	MAX_MEM_ITEM_SIZE
};

//内存大小为HASH ID， 不唯一
static CHashTbl fg_AvailableMemTbl = 
{
	pfg_AvailableMemItemArray, 
	0, 
	MAX_MEM_ITEM_SIZE
};

static int32_t is_mem_ready( void );

static int32_t insert_mem_hash_tbl( CHashTbl *pHashTbl, CHashItem *pNewHashItem );

#if (SHOW_MEM_INFO_SUPPORT)
static void mem_show( void );
#endif

void *mem_malloc_ext( int32_t iMemSize, const int8_t *pFileName, const int32_t iLineNo )
{
	void *pMemBuf = NULL;
	CHashItem *pHashItem = NULL;

	if ( is_mem_ready() < 0 )
	{

		//return pMemBuf;
	}

	//lock( &fg_MemLocker );

	pHashItem = remove_hash_tbl( &fg_AvailableMemTbl, iMemSize );
	if ( pHashItem )
	{
		CMemItem *pMemItem = NULL;

		fg_iFreeMemCounter--;

		pMemItem = CONTAINER_OF(HItem,pHashItem,CMemItem);
		pMemItem->HItem.iHashId = (int32u_t)pMemItem->pMemBuf;//换内存地址为KEY
		sprintf( pMemItem->btMemInfo, "%s:%d", pFileName, iLineNo );

		fg_iTotalFreeMemInBytes -= pMemItem->iMemBufLen;
		fg_iTotalFreeMemInBytes -= sizeof(*pMemItem);

		if ( OP_SUCCESS == insert_hash_tbl( &fg_UsedMemTbl, &pMemItem->HItem ) )
		{
			fg_iUsedMemCounter++;
			fg_iTotalUsedMemInBytes += pMemItem->iMemBufLen;
			fg_iTotalUsedMemInBytes += sizeof(*pMemItem);
			pMemBuf = (void *)pMemItem->pMemBuf;
		}
		else
		{
			LOGD("!if ( OP_SUCCESS == insert_hash_tbl( &fg_UsedMemTbl,  failed?????????????");
			fg_iTotalMemCounter--;
		}

		if ( !pMemBuf )
		{
			LOGD("put memory to used table failed????????????????????????????");
			if ( pMemItem->pMemBuf )
			{
				fg_iTotalMemInBytes -= pMemItem->iMemBufLen;
				free( pMemItem->pMemBuf );
				pMemItem->pMemBuf = NULL;
			}

			fg_iTotalMemInBytes -= sizeof(*pMemItem);
			
			free( pMemItem );
			pMemItem = NULL;
		}
	}
	else
	{
		CMemItem *pMemItem = NULL;
		#if 0//(SHOW_MEM_INFO_SUPPORT)
		#if (LOG_SUPPORT)
		char logBuf[128];

		sprintf(logBuf, "get %d bytes from free mem table failed?????????????????????????", 
						iMemSize );
		LOGD(logBuf);

		#endif
		#endif

		pMemItem = malloc( sizeof(*pMemItem) );
		if ( pMemItem )
		{
			
			
			memset( pMemItem, 0x00, sizeof(*pMemItem) );

			pMemItem->pMemBuf = malloc(iMemSize);
			if ( pMemItem->pMemBuf )
			{
				
				
				pMemItem->iMemBufLen = iMemSize;

				pMemItem->HItem.iHashId = (int32u_t)pMemItem->pMemBuf;//内存地址为KEY

				sprintf( pMemItem->btMemInfo, "MEM_DEBUG:%s:%d", pFileName, iLineNo );

#if (SHOW_MEM_INFO_SUPPORT)
				#if (LOG_SUPPORT)
					{
					char logBuf[128];
					sprintf( logBuf, "MALLOC %d bytes: %s", iMemSize, pMemItem->btMemInfo );
				LOGD( logBuf );

					}
				#endif
#endif

				if ( OP_SUCCESS == insert_hash_tbl( &fg_UsedMemTbl, &(pMemItem->HItem) ) )
				{
					fg_iTotalMemInBytes += sizeof(*pMemItem);
					fg_iTotalMemInBytes += pMemItem->iMemBufLen;
					
					fg_iTotalMemCounter++;
					fg_iUsedMemCounter++;
					fg_iTotalUsedMemInBytes += pMemItem->iMemBufLen;
					fg_iTotalUsedMemInBytes += sizeof(*pMemItem);
					pMemBuf = (void *)pMemItem->pMemBuf;
				}
			}

			if ( !pMemBuf )
			{
				LOGD("put memory to used table failed??????????????????????????");
				if ( pMemItem )
				{
					if ( pMemItem->pMemBuf )
					{
						free( pMemItem->pMemBuf );
						pMemItem->pMemBuf = NULL;

					}
					
					free( pMemItem );
					pMemItem = NULL;

				}
			}
		}
	}

	//unlock( &fg_MemLocker );	
#if (SHOW_MEM_INFO_SUPPORT)
	mem_show();
#endif
    
    if ( pMemBuf )
    {
        memset( pMemBuf, 0x00, iMemSize );
    }
	
	return pMemBuf;
}

int32_t mem_free( void *pMemBuf )
{
	int32_t iRetCode = -1;
#if (SHOW_MEM_INFO_SUPPORT)
	int8_t logBuf[256] = { 0x00, };
#endif

	if ( is_mem_ready() < 0 )
		return iRetCode;

	lock( &fg_MemLocker );
	if ( pMemBuf )
	{
		CHashItem *pHashItem = NULL;
	
		pHashItem = remove_hash_tbl( &fg_UsedMemTbl, (int32u_t)pMemBuf );
		if ( pHashItem )
		{
			CMemItem *pMemItem = NULL;

			fg_iUsedMemCounter--;

			pMemItem = CONTAINER_OF(HItem,pHashItem,CMemItem);
			pMemItem->HItem.iHashId = pMemItem->iMemBufLen;//换长度为KEY

			fg_iTotalUsedMemInBytes -= pMemItem->iMemBufLen;
			fg_iTotalUsedMemInBytes -= sizeof(*pMemItem);

#if (SHOW_MEM_INFO_SUPPORT)
			sprintf( logBuf, "RECYCLE %d bytes, %s.", pMemItem->iMemBufLen,pMemItem->btMemInfo );
			LOGD(logBuf);
#endif

			iRetCode = insert_hash_tbl_ext( &fg_AvailableMemTbl, &pMemItem->HItem );
			if ( iRetCode >= 0 )
			{

				fg_iFreeMemCounter++;
				fg_iTotalFreeMemInBytes += pMemItem->iMemBufLen;
				fg_iTotalFreeMemInBytes += sizeof(*pMemItem);
			}
			else
			{
				if ( pMemItem->pMemBuf )
				{
					fg_iTotalMemInBytes -= pMemItem->iMemBufLen;
					
					free( pMemItem->pMemBuf );
					pMemItem->pMemBuf = NULL;
					
				}

				fg_iTotalMemInBytes -= sizeof(*pMemItem);
				
				free( pMemItem );
				pMemItem = NULL;
				fg_iTotalMemCounter--;

				LOGD("!if ( iRetCode >= 0 ) failed????????????????????");
			}
		}
		#if (LOG_SUPPORT)
		else
		{
			LOGD("pMemBuf--->%u", (int32u_t)pMemBuf);
			LOGD("!if ( pHashItem ) failed?????????????????????");
		}
		#endif
	}
	unlock( &fg_MemLocker );
	
	return iRetCode;
}

static int32_t is_mem_ready( void )
{
	if ( fg_InitFlag )
		return 0;

	return -1;
}


int32_t init_mem( void )
{
	int32_t iRetCode = -1;


	if ( !fg_InitFlag )
	{
		if ( init_mutex( &fg_MemLocker ) >= 0 )
		{
			fg_InitFlag = 1;
			iRetCode = 0;
		}
	}
	else
		iRetCode = 0;


	return iRetCode;
}

void release_mem(void* pParam)
{
	if(NULL != pParam)
	{
		free(pParam);
		pParam = NULL;
	}
}

#if (SHOW_MEM_INFO_SUPPORT)
static void mem_show( void )
{
	int8_t logBuf[256] = { 0x00, };
	int32_t i = 0, iUsedItemCounter = 0;

	if ( is_mem_ready() < 0 )
		return ;

	lock( &fg_MemLocker );

#if 1
	sprintf( logBuf, "--------->Total Memory Size-->%d bytes, Total Free Memory Size-->%d bytes, Total Used Memory Size-->%d bytes, fg_iTotalMemCounter-->%d, fg_iUsedMemCounter-->%d, fg_iFreeMemCounter-->%d.", 
		fg_iTotalMemInBytes, fg_iTotalFreeMemInBytes, 
		fg_iTotalUsedMemInBytes, 
		fg_iTotalMemCounter, fg_iUsedMemCounter, fg_iFreeMemCounter );
	LOGD(logBuf);
#endif


	unlock( &fg_MemLocker );


}
#endif

#endif

