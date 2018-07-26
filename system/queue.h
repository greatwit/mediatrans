/**************************************************************************************************
* File Name: queue.h
* Writer: lgz
* Create Date: 2013-3-25 12:36
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "typedefs.h"
#include "list.h"

#include "os_api.h"

#ifdef __cplusplus
extern "C"
{
#endif

//队列节点
typedef struct CQueueNode_t
{
	CListNode LNode;
}CQueueNode;

//队列
typedef struct CQueue_t
{
	CQueueNode *Front;
	CQueueNode *Rear;

	int32_t iCurrWaterLevel;

	int32_t iMaxWaterLevel;

	CMutex locker;
}CQueue;

EXPORT_API int32_t en_queue( CQueue *pQueue, CQueueNode *pNewQNode );

EXPORT_API CQueueNode *de_queue( CQueue *pQueue );

EXPORT_API int32_t remove_queue( CQueue *pQueue, CQueueNode *pRemoveQNode );

EXPORT_API int32_t set_water_level( CQueue *pQueue, int32_t iNewWaterLevel );

#ifdef __cplusplus
}
#endif

#endif/* __QUEUE_H__ */
