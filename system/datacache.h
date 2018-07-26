#ifndef __DATACACHE_H__
#define __DATACACHE_H__

#include "typedefs.h"

#include "os_api.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct CDataCache_t//环形缓冲类型
{
	int8u_t *pDataBuf;
	int32_t Front;
	int32_t Rear;
	int32_t BufLen;          //current buffer length
	int32_t iCurrDetectIndex;
	int32_t DataBufSize;     //buffer total length

	CMutex locker;
}CDataCache;

EXPORT_API int32_t init_datacache( CDataCache *const pDataCache, int32_t iMaxLen );
EXPORT_API int32_t fini_datacache( CDataCache *const pDataCache );

EXPORT_API int32_t write_datacache( CDataCache *const pDataCache, const void *pData, const int iDataLen );

EXPORT_API int32_t read_datacache( CDataCache *const pDataCache, void *pOutDataBuf, const int iDataBufLen );
EXPORT_API int32_t snifer_datacache( CDataCache *const pDataCache, void *pOutDataBuf, const int iDataBufLen );

EXPORT_API int32_t search_datacache( CDataCache *const pDataCache, const unsigned char *pKeyBuf, const int iKeyBufLen );

EXPORT_API int32_t clear_datacache( CDataCache *const pDataCache );

EXPORT_API int32_t get_datacache_size( CDataCache *const pDataCache );

EXPORT_API int32_t is_datacache_full( CDataCache *const pDataCache );

EXPORT_API int32_t reset_datacache( CDataCache *const pDataCache );

EXPORT_API void    show_datacache( CDataCache *const pDataCache );


EXPORT_API int32_t get_datacache_left_size( CDataCache *const pDataCache );

EXPORT_API int     read_offset( CDataCache *const pDataCache, const int iDataBufLen );

#ifdef __cplusplus
}
#endif

#endif/* __DATACACHE_H__ */

