/**************************************************************************************************
* File Name: hash.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include "typedefs.h"
#include "list.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct CHashItem_t
{	
	int32u_t iHashId;

	void *pData;

	CListNode LNode;
}CHashItem;

typedef struct CHashTbl_t
{
	CHashItem **ppHashItemArray;

	int32_t iWaterLevel;

	int32_t iMaxHashTblSize;
}CHashTbl;

EXPORT_API CHashTbl *create_hash_tbl( int32_t iMaxTblSize );

EXPORT_API int32_t destory_hash_tbl( CHashTbl **ppHashTbl );

EXPORT_API int32_t insert_hash_tbl( CHashTbl *pHashTbl, CHashItem *pNewHashItem );

EXPORT_API int32_t insert_hash_tbl_ext( CHashTbl *pHashTbl, CHashItem *pNewHashItem );

EXPORT_API int32_t get_hash_size( CHashTbl *pHashTbl );

EXPORT_API CHashItem *remove_hash_tbl( CHashTbl *pHashTbl, int32u_t iHashId );

EXPORT_API const CHashItem *search_hash_tbl( CHashTbl *pHashTbl, int32u_t iHashId );

#ifdef __cplusplus
}
#endif

#endif/* __HASH_H__ */
