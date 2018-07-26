/**************************************************************************************************
* File Name: hash.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/


#include "hash.h"

#include "memory.h"

#include "log.h"

CHashTbl *create_hash_tbl( int32_t iMaxTblSize )
{
	CHashTbl *pHashTbl = NULL;

	pHashTbl = mem_malloc( sizeof(*pHashTbl) );
	if ( pHashTbl )
	{
		memset( pHashTbl, 0x00, sizeof(*pHashTbl) );

		pHashTbl->ppHashItemArray = (CHashItem **)mem_malloc( iMaxTblSize * sizeof(void *) );
		if ( pHashTbl->ppHashItemArray )
		{
			memset( (void *)pHashTbl->ppHashItemArray, 0x00, iMaxTblSize * sizeof(void *) );
			pHashTbl->iMaxHashTblSize = iMaxTblSize;
		}
		else
		{
			mem_free( pHashTbl );

			pHashTbl = NULL;
		}
	}

	return pHashTbl;
}

int32_t destory_hash_tbl( CHashTbl **ppHashTbl )
{
	int32_t iRetCode = -1;

	if ( ppHashTbl && *ppHashTbl )
	{
		mem_free( (*ppHashTbl)->ppHashItemArray );
		(*ppHashTbl)->ppHashItemArray = NULL;

		mem_free( *ppHashTbl );
		*ppHashTbl = NULL;

		iRetCode = OP_SUCCESS;
	}

	return iRetCode;
}

int32_t insert_hash_tbl( CHashTbl *pHashTbl, CHashItem *pNewHashItem )
{
	int32_t iRetCode = -1;

	if ( pHashTbl && pNewHashItem )
	{
		if ( !search_hash_tbl( pHashTbl, pNewHashItem->iHashId ) )
		{
			int32_t iHashKey = pNewHashItem->iHashId % pHashTbl->iMaxHashTblSize;
			CHashItem *pHashItem = pHashTbl->ppHashItemArray[iHashKey];
			
			pNewHashItem->LNode.Prev = pNewHashItem->LNode.Next = NULL;
			if ( pHashItem )
			{
				CListNode *pHeadLNode = &(pHashItem->LNode);
			
				iRetCode = insert_list_node_rear( &pHeadLNode, &(pNewHashItem->LNode) );

				if ( iRetCode >= 0 )
					pHashTbl->iWaterLevel++ ;
			}
			else
			{
				
				pHashTbl->ppHashItemArray[iHashKey] = pNewHashItem;

				pHashTbl->iWaterLevel++ ;
			
				iRetCode = OP_SUCCESS;
			}
		}
	}

	return iRetCode;
}

int32_t insert_hash_tbl_ext( CHashTbl *pHashTbl, CHashItem *pNewHashItem )
{
	int32_t iRetCode = -1;

	if ( pHashTbl && pNewHashItem )
	{
		int32_t iHashKey = pNewHashItem->iHashId % pHashTbl->iMaxHashTblSize;
		CHashItem *pHashItem = pHashTbl->ppHashItemArray[iHashKey];
		
		pNewHashItem->LNode.Prev = pNewHashItem->LNode.Next = NULL;
		if ( pHashItem )
		{
			CListNode *pHeadLNode = &(pHashItem->LNode);
		
			iRetCode = insert_list_node_rear( &pHeadLNode, &(pNewHashItem->LNode) );

			if ( iRetCode >= 0 )
				pHashTbl->iWaterLevel++ ;
		}
		else
		{
			
			pHashTbl->ppHashItemArray[iHashKey] = pNewHashItem;

			pHashTbl->iWaterLevel++ ;
		
			iRetCode = OP_SUCCESS;
		}
	}

	return iRetCode;
}

int32_t get_hash_size( CHashTbl *pHashTbl )
{
	int32_t iRetCode = -1;

	if ( pHashTbl )
	{
		int32_t iHashItemCount = 0;
		int32_t i = 0;

		for ( i = 0; i < pHashTbl->iMaxHashTblSize; i++ )
		{
			CHashItem *pHashItem = pHashTbl->ppHashItemArray[i];

			if ( pHashItem )
			{
				CListNode *pTempLNode = &(pHashItem->LNode);
			
				while ( pTempLNode )
				{
					iHashItemCount++;
					
					pTempLNode = pTempLNode->Next;
				}
			}
		}

		iRetCode = iHashItemCount;
	}

	return iRetCode;
}

CHashItem *remove_hash_tbl( CHashTbl *pHashTbl, int32u_t iHashId )
{
	CHashItem *pDelHashItem = NULL;

	if ( pHashTbl && iHashId >= 0 )
	{
		int32_t iHashKey = iHashId % pHashTbl->iMaxHashTblSize;
		CHashItem *pHashItem = pHashTbl->ppHashItemArray[iHashKey];

		if ( pHashItem )
		{
			CListNode *pTempLNode = &(pHashItem->LNode);
			CHashItem *pTempHashItem = NULL;

			while ( pTempLNode )
			{
				pTempHashItem = CONTAINER_OF(LNode,pTempLNode,CHashItem);
				if ( pTempHashItem->iHashId == iHashId )
				{
					CListNode *pHeadLNode = &pHashItem->LNode, *pNextLNode = NULL;

					pNextLNode = pTempLNode->Next;
					
					if ( remove_list_node( &pHeadLNode, pTempLNode ) >= 0 )
					{
						if ( pTempHashItem == pHashTbl->ppHashItemArray[iHashKey] )
						{
							if ( pNextLNode )
							{
								pHashTbl->ppHashItemArray[iHashKey] = 
									CONTAINER_OF( LNode, pNextLNode, CHashItem );
							}
							else
								pHashTbl->ppHashItemArray[iHashKey] = NULL;
						}
						
						pDelHashItem = pTempHashItem;
						
						pHashTbl->iWaterLevel-- ;
						
						break ;
					}
				}

				pTempLNode = pTempLNode->Next;
			}
		}
	}

	return pDelHashItem;
}

const CHashItem *search_hash_tbl( CHashTbl *pHashTbl, int32u_t iHashId )
{
	const CHashItem *pRetHashItem = NULL;

	if ( pHashTbl && iHashId >= 0 )
	{
		int32_t iHashKey = iHashId % pHashTbl->iMaxHashTblSize;
		CHashItem *pHashItem = pHashTbl->ppHashItemArray[iHashKey];

		if ( pHashItem )
		{
			CListNode *pTempLNode = &pHashItem->LNode;
			CHashItem *pTempHashItem = NULL;

			while ( pTempLNode )
			{
				pTempHashItem = CONTAINER_OF(LNode,pTempLNode,CHashItem);
				if ( pTempHashItem->iHashId == iHashId )
				{
					
					pRetHashItem = (const CHashItem *)pTempHashItem;

					break ;
				}

				pTempLNode = pTempLNode->Next;
			}
		}
	}

	return pRetHashItem;
}


