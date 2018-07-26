#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "config.h"

#include "typedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif


#if (DEBUG_SUPPORT)

int32_t init_mem( void );

void *mem_malloc_ext( int32_t iMemSize, const int8_t *pFileName, const int32_t iLineNo );


#define mem_malloc(a) mem_malloc_ext(a, __FILE__, __LINE__)

int32_t mem_free( void *pMemBuf );


void release_mem(void*);


#else

#define mem_malloc  malloc
#define mem_free  free

#endif

#ifdef __cplusplus
}
#endif


#endif

