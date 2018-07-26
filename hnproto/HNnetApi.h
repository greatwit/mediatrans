/**************************************************************************************************
* File Name: select.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __HNNET_API_H__
#define __HNNET_API_H__

#include "typedefs.h"

#include <AnBBaseType.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef int32_t (*reactor_callback_t)( int32_t iReactorId, int32_t iSocketId, int32_t iEvent );
typedef int32_t (*stream_callback_t)(char*buffer, int32_t iLen);
    
DEV_SDK_API int32_t createSdk(stream_callback_t iocallback);
DEV_SDK_API int32_t destroySdk();

DEV_SDK_API int32_t creatSession( const char *pRemoteIP, int16u_t iRemotePort );

DEV_SDK_API int32_t login( int32_t sessionId, char *username, char *password );
DEV_SDK_API int32_t logout( int32_t sessionId );
    
DEV_SDK_API int32_t getLensGroupInfoList(int32_t sessionId, const char*pUserId);
DEV_SDK_API int32_t getLensInfoList(int32_t sessionId, const char*pLensGroupId);


DEV_SDK_API int32_t queryGroup(int32_t sessionId, int pagesize, int usrid);
DEV_SDK_API int32_t queryDeviceList( int32_t sessionId, int pagesize, int groupid);
DEV_SDK_API int32_t queryDeviceOnline( int32_t sessionId, int usrid);

DEV_SDK_API int32_t changePassWord(int32_t sessionId, int usrid, char *username, char *oldpass, char* newpass);

DEV_SDK_API int32_t sendKeepAlive( int32_t sessionId);
    
DEV_SDK_API int32_t sendPtzControl( int32_t sessionId, const char*pLendId, int commond);
    

#ifdef __cplusplus
}
#endif

#endif	/* __HNNET_API_H__ */
