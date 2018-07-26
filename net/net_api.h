/**************************************************************************************************
* File Name: net_api.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*注意:在调用网络接口前， 必须先创建反应器
***************************************************************************************************/
#ifndef __NET_API_H__
#define __NET_API_H__

#include "typedefs.h"

#include <HNnetApi.h>

#ifdef __cplusplus
extern "C"
{
#endif


    
typedef enum
{
	NET_EVENT_DATA_NOTIFY, //套接字可读
	NET_EVENT_ERROR_NOTIFY//套接字网络错误
}C_NET_EVENT;

typedef enum
{
	SOCKET_CLIENT_TCP, 
	SOCKET_CLIENT_UDP, 
	SOCKET_SERVER_TCP, 
	SOCKET_SERVER_UDP, 
	SOCKET_CLIENT_MULTICAST, 
	SOCKET_SERVER_MULTICAST, 
}C_SOCKET_TYPE;

typedef enum
{
	SOCKET_OPTION_SET_NO_BLOCK, //非阻塞
	SOCKET_OPTION_SET_SEND_BUFFER, //设置发送缓冲区大小
	SOCKET_OPTION_SET_RECV_BUFFER, //设置接收缓冲区大小
	SOCKET_OPTION_REUSE_ADDR, //服务器重用地址
	SOCKET_OPTION_SET_SENDTIMEOUT, 
	SOCKET_OPTION_SET_RECVTIMEOUT

}C_SOCKET_OPTION;

//套接字熟悉参数
typedef struct CSockParam_t
{	
	int32_t iOn;//是否启用

	int32_t iBuffSize;//缓冲区大小

	int32_t iTimeOut;
}CSockParam;

typedef struct CNetAddr_t
{
	char IP[32];
	int16u_t iPort;
}CNetAddr;




//创建反应器(先调用)
EXPORT_API int32_t create_reactor( void );
//释放反应器

EXPORT_API int32_t destory_reactor( int32_t iReactorId );

//注册反应器回调函数
EXPORT_API int32_t registry_reactor_callback( int32_t iReactorId, reactor_callback_t fcallback );


//向反应器添加套接字
EXPORT_API int32_t add_reactor_socket( int32_t iReactorId, int32_t iSocketId );


//从反应器中删除套接字
EXPORT_API int32_t remove_reactor_socket( int32_t iReactorId, int32_t iSocketId );

//创建套接字接口
EXPORT_API int32_t create_socket( const char *pIP, int16u_t iPort, 
								  const char *pLocalIP, int16u_t iLocalPort, int32_t iSocketType );
//关闭套接字接口
EXPORT_API int32_t close_socket( int32_t iSocketId );

EXPORT_API int32_t net_accept( int32_t iListenSocketId, CNetAddr *pAddr );

//套接字属性设置
EXPORT_API int32_t set_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize );
EXPORT_API int32_t get_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize );

//发送接收数据
//TCP
EXPORT_API int32_t net_send( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen );
EXPORT_API int32_t net_recv( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen );



//UDP
EXPORT_API int32_t net_sendto( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen, CNetAddr *pPeerAddr );
EXPORT_API int32_t net_recvfrom( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen, CNetAddr *pPeerNetAddr );

//整形跟字符串IP转换
EXPORT_API int32u_t net_ip2n( const int8_t *pIP );
EXPORT_API const int8_t * net_n2ip( int32u_t iIP );

//活动本机IP
EXPORT_API const int8_t *net_get_local_ip( void );

#ifdef __cplusplus
}
#endif

#endif/* __NET_API_H__ */
