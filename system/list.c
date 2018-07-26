/**************************************************************************************************
* File Name: list.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/


#include "list.h"

#include "log.h"

int32_t insert_list_node_rear( CListNode **ppListHead, CListNode *pNewListNode )
{
	int32_t iRetCode = OP_FAILURE;

	if ( ppListHead && pNewListNode )
	{
		CListNode *pListHead = *ppListHead;

		if ( pListHead )
		{
			pNewListNode->Next = pListHead->Next;

			if ( pListHead->Next )
				pListHead->Next->Prev = pNewListNode;

			pListHead->Next = pNewListNode;
			pNewListNode->Prev = pListHead;

			iRetCode = OP_SUCCESS;
		}
		else
		{
			pNewListNode->Prev = pNewListNode->Next = NULL;
			
			*ppListHead = pNewListNode;

			iRetCode = OP_SUCCESS;
		}
	}

	return iRetCode;
}

int32_t insert_list_node_front( CListNode **ppListHead, CListNode *pNewListNode )
{
	int32_t iRetCode = OP_FAILURE;

	if ( ppListHead && pNewListNode )
	{
		CListNode *pListHead = *ppListHead;

		if ( pListHead )
		{
			pNewListNode->Next = pListHead;
			pListHead->Prev = pNewListNode;
			pNewListNode->Prev = NULL;

			*ppListHead = pNewListNode;

			iRetCode = OP_SUCCESS;
		}
		else
		{
			pNewListNode->Prev = pNewListNode->Next = NULL;
			
			*ppListHead = pNewListNode;

			iRetCode = OP_SUCCESS;
		}
	}

	return iRetCode;
}

int32_t remove_list_node( CListNode **ppListHead, CListNode *pRemoveListNode )
{
	int32_t iRetCode = OP_FAILURE;

	if ( ppListHead && pRemoveListNode )
	{
		CListNode *pListHead = *ppListHead;

		if ( pListHead )
		{
			if ( pListHead == pRemoveListNode )
			{
				if ( pRemoveListNode->Next )
				{
					(*ppListHead) = pRemoveListNode->Next;
					pRemoveListNode->Next->Prev = NULL;
				}
				else
				{
					pRemoveListNode->Prev = pRemoveListNode->Next = NULL;
					(*ppListHead)  = NULL;
				}

				iRetCode = OP_SUCCESS;
			}
			else
			{
				if ( pRemoveListNode->Prev )
					pRemoveListNode->Prev->Next = pRemoveListNode->Next;
				if ( pRemoveListNode->Next )
					pRemoveListNode->Next->Prev = pRemoveListNode->Prev;

				iRetCode = OP_SUCCESS;
			}
		}
		else
			LOGD("!if ( pListHead ) failed");
	}
	else
		LOGD("!if ( ppListHead && pRemoveListNode ) failed");

	return iRetCode;
}

