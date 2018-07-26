/**************************************************************************************************
* File Name: net_api.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*ע��:�ڵ�������ӿ�ǰ�� �����ȴ�����Ӧ��
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
	NET_EVENT_DATA_NOTIFY, //�׽��ֿɶ�
	NET_EVENT_ERROR_NOTIFY//�׽����������
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
	SOCKET_OPTION_SET_NO_BLOCK, //������
	SOCKET_OPTION_SET_SEND_BUFFER, //���÷��ͻ�������С
	SOCKET_OPTION_SET_RECV_BUFFER, //���ý��ջ�������С
	SOCKET_OPTION_REUSE_ADDR, //���������õ�ַ
	SOCKET_OPTION_SET_SENDTIMEOUT, 
	SOCKET_OPTION_SET_RECVTIMEOUT

}C_SOCKET_OPTION;

//�׽�����Ϥ����
typedef struct CSockParam_t
{	
	int32_t iOn;//�Ƿ�����

	int32_t iBuffSize;//��������С

	int32_t iTimeOut;
}CSockParam;

typedef struct CNetAddr_t
{
	char IP[32];
	int16u_t iPort;
}CNetAddr;




//������Ӧ��(�ȵ���)
EXPORT_API int32_t create_reactor( void );
//�ͷŷ�Ӧ��

EXPORT_API int32_t destory_reactor( int32_t iReactorId );

//ע�ᷴӦ���ص�����
EXPORT_API int32_t registry_reactor_callback( int32_t iReactorId, reactor_callback_t fcallback );


//��Ӧ������׽���
EXPORT_API int32_t add_reactor_socket( int32_t iReactorId, int32_t iSocketId );


//�ӷ�Ӧ����ɾ���׽���
EXPORT_API int32_t remove_reactor_socket( int32_t iReactorId, int32_t iSocketId );

//�����׽��ֽӿ�
EXPORT_API int32_t create_socket( const char *pIP, int16u_t iPort, 
								  const char *pLocalIP, int16u_t iLocalPort, int32_t iSocketType );
//�ر��׽��ֽӿ�
EXPORT_API int32_t close_socket( int32_t iSocketId );

EXPORT_API int32_t net_accept( int32_t iListenSocketId, CNetAddr *pAddr );

//�׽�����������
EXPORT_API int32_t set_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize );
EXPORT_API int32_t get_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize );

//���ͽ�������
//TCP
EXPORT_API int32_t net_send( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen );
EXPORT_API int32_t net_recv( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen );



//UDP
EXPORT_API int32_t net_sendto( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen, CNetAddr *pPeerAddr );
EXPORT_API int32_t net_recvfrom( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen, CNetAddr *pPeerNetAddr );

//���θ��ַ���IPת��
EXPORT_API int32u_t net_ip2n( const int8_t *pIP );
EXPORT_API const int8_t * net_n2ip( int32u_t iIP );

//�����IP
EXPORT_API const int8_t *net_get_local_ip( void );

#ifdef __cplusplus
}
#endif

#endif/* __NET_API_H__ */
