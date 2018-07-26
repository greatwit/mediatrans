/**************************************************************************************************
* File Name: list.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/
#ifndef __LIST_H__
#define __LIST_H__

#include "typedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

//����
typedef struct CListNode_t
{
	struct CListNode_t *Prev;
	struct CListNode_t *Next;
}CListNode;

//�����ڵ����
EXPORT_API int32_t insert_list_node_rear( CListNode **ppListHead, CListNode *pNewListNode );

//ǰ�˽ڵ����
EXPORT_API int32_t insert_list_node_front( CListNode **ppListHead, CListNode *pNewListNode );

//�Ӷ�����ɾ���ڵ�
EXPORT_API int32_t remove_list_node( CListNode **ppListHead, CListNode *pNewListNode );

#ifdef __cplusplus
}
#endif

#endif/* __LIST_H__ */
