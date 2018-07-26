/**************************************************************************************************
* File Name: queue.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/


#include "queue.h"

#include "log.h"

int32_t en_queue( CQueue *pQueue, CQueueNode *pNewQNode )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pQueue && pNewQNode )
	{
		lock( pQueue->locker );
	
		if ( pQueue->iCurrWaterLevel < pQueue->iMaxWaterLevel )
		{
			pNewQNode->LNode.Prev = pNewQNode->LNode.Next = NULL;
			
			if ( (pQueue->Front == pQueue->Rear) && !pQueue->Front )
			{
				//队列为空
				pQueue->Front = pQueue->Rear = pNewQNode;

				pQueue->iCurrWaterLevel++;

				iRetCode = OP_SUCCESS;
			}
			else
			{
				//队列不为空
				if ( pQueue->Rear )
				{
					CListNode *pHeadLNode = &(pQueue->Rear->LNode);
					
					pNewQNode->LNode.Prev = pNewQNode->LNode.Next = NULL;
					if ( OP_SUCCESS == insert_list_node_rear( &pHeadLNode, &(pNewQNode->LNode) ) )
					{
						pQueue->Rear = pNewQNode;
					
						pQueue->iCurrWaterLevel++;
					
						iRetCode = OP_SUCCESS;
					}
				}
			}
		}

		unlock( pQueue->locker );
		
	}

	return iRetCode;
}

CQueueNode *de_queue( CQueue *pQueue )
{
	CQueueNode *pDelQNode = NULL;
	
	if ( pQueue )
	{
		CQueueNode *pFront = NULL, *pNewFront = NULL;
		
		lock( pQueue->locker );

		pFront = pQueue->Front;

		if ( pFront )
		{
			CListNode *pNewFrontListNode = NULL;

			pDelQNode = pFront;
			
			pNewFrontListNode = pFront->LNode.Next;
			if ( pNewFrontListNode )
			{
				pNewFront = CONTAINER_OF(LNode,pNewFrontListNode,CQueueNode);

				if ( pNewFront )
				{
					pQueue->Front = pNewFront;
				}
			}
			else
			{
				pQueue->Front = pQueue->Rear = NULL;
			}

			pDelQNode->LNode.Prev = pDelQNode->LNode.Next = NULL;

			pQueue->iCurrWaterLevel--;
		}

		unlock( pQueue->locker );
	}

	return pDelQNode;
}

int32_t remove_queue( CQueue *pQueue, CQueueNode *pRemoveQNode )
{
	int32_t iRetCode = -1;

	if ( pQueue && pQueue->Front && pRemoveQNode )
	{
		CQueueNode *pFront = NULL, *pNewFront = NULL;
		CListNode *pNewFrontListNode = NULL;
		
		lock( pQueue->locker );

		//队列不为空
		if ( pRemoveQNode == pQueue->Front )
		{
			//删除队首节点
			pNewFrontListNode = pRemoveQNode->LNode.Next;

			if ( pNewFrontListNode )
			{
				pNewFrontListNode->Prev = NULL;
				pNewFront = CONTAINER_OF(LNode,pNewFrontListNode,CQueueNode);
				pQueue->Front = pNewFront;

				iRetCode = 0;
				
			}
			else
			{
				pQueue->Front = pQueue->Rear = NULL;
				iRetCode = 0;
			}
		}
		else
		{
			//删除普通节点
			CListNode *pQListHead = &(pQueue->Front->LNode);

			if ( remove_list_node( &pQListHead, &(pRemoveQNode->LNode) ) >= 0 )
				iRetCode = 0;
			else
				LOGD("!if ( remove_list_node( &pQListHe failed?????????????????????");
		}

		if ( iRetCode >= 0 )
			pQueue->iCurrWaterLevel--;


		unlock( pQueue->locker );
	}
	else
		LOGD("!if ( pQueue && pRemoveQNode ) failed??????????????????");

	return iRetCode;
}

int32_t set_water_level( CQueue *pQueue, int32_t iNewWaterLevel )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pQueue && iNewWaterLevel > 0 )
	{
		lock( pQueue->locker );
		
		pQueue->iMaxWaterLevel = iNewWaterLevel;

		iRetCode = OP_SUCCESS;

		unlock( pQueue->locker );
	}

	return iRetCode;
}


