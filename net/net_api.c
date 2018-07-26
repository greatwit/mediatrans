/**************************************************************************************************
* File Name: net_api.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/



#include "net_api.h"

#include "hash.h"
#include "os_api.h"
#include "select.h"
#include "epoll.h"
#include "kqueue.h"
#include "memory.h"

#include <time.h>


#include "log.h"


#if (__OS_LINUX__)
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#elif (__OS_IOS__)

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#elif (__OS_WIN32__)


#endif

//网络反应器
typedef struct CReactor_t
{
	int32_t iReactorId;//反应器ID
	
	CHashTbl *pSocketTbl;//套接字哈希表

	reactor_callback_t reactor_callback;

	CNetEngine *pNetEngine;
	
	CHashItem HItem;
}CReactor;

typedef struct CReactorManager_t
{
	CHashTbl *pReactorTbl;//反应器哈希表

	CMutex Mutex;

	int32_t iInitFlag;
}CReactorManager;


static CReactorManager fg_ReactorManager = {
	NULL, 
	NULL, 
	0
};

static int32_t init_reactor_manager( void );

int32_t on_net_event_notify( int32_t iSocketId, int32_t iNetEvent, void *pUserData )
{
	int32_t iRetCode = OP_FAILURE;

	//printf( "on_net_event_notify:-->\r\n" );
	CReactor *pReactor = (CReactor *)pUserData;
	if ( pUserData && iSocketId > 0 && iNetEvent >= 0 )
	{
	//	printf( "iSocketId-->%d, iNetEvent-->%d, pUserData-->%u.\r\n", iSocketId, iNetEvent, pUserData );
		
		if ( pReactor->reactor_callback )
		{
			iRetCode = pReactor->reactor_callback( pReactor->iReactorId, iSocketId, iNetEvent );
		}
	}

	return iRetCode;
}

//创建反应器
int32_t create_reactor( void )
{
	int32_t iRetCode = OP_FAILURE;
	CReactor *pNewReactor = NULL;

	if ( !fg_ReactorManager.iInitFlag )
		if ( init_reactor_manager() < 0 )
			return iRetCode;

	lock( fg_ReactorManager.Mutex );

	pNewReactor = mem_malloc( sizeof(*pNewReactor) );
	if ( pNewReactor )
	{
		memset( pNewReactor, 0x00, sizeof(*pNewReactor) );

		pNewReactor->pSocketTbl = create_hash_tbl( 128 );
		if ( pNewReactor->pSocketTbl )
		{
			int32_t iTempHandle = -1;
			
			while ( (iTempHandle = get_handle()) > 0 )
			{
				if ( !search_hash_tbl( fg_ReactorManager.pReactorTbl, iTempHandle ) )
				{
					break ;
		
				}
			}

			if ( iTempHandle > 0 )
			{
				pNewReactor->iReactorId = iTempHandle;
									
				pNewReactor->pNetEngine = create_engine( pNewReactor );
				if ( pNewReactor->pNetEngine )
				{
					pNewReactor->HItem.iHashId = pNewReactor->iReactorId ;
					if ( OP_SUCCESS == insert_hash_tbl( fg_ReactorManager.pReactorTbl, &pNewReactor->HItem ) )
					{
						if ( pNewReactor->pNetEngine->init( pNewReactor->pNetEngine ) >= 0 )
						{
							
							iRetCode = pNewReactor->iReactorId;
			
							#if 0//(LOG_SUPPORT)
							printf( "create_reactor ok.pNewReactor->iReactorId-->%d.\r\n", pNewReactor->iReactorId );
#endif
							
						}

					}
				}

			}
		}

		if ( iRetCode < 0 )
		{
			if ( pNewReactor->pNetEngine )
				destory_engine( &pNewReactor->pNetEngine );

			if ( pNewReactor->pSocketTbl )
				destory_hash_tbl( &pNewReactor->pSocketTbl );

			mem_free( pNewReactor );
			pNewReactor = NULL;
		}
		
	}

	unlock( fg_ReactorManager.Mutex );

	return iRetCode;
}

//释放反应器
int32_t destory_reactor( int32_t iReactorId )
{
	int32_t iRetCode = OP_FAILURE;
	CHashItem *pRemoveHashItem = NULL;

	if ( !fg_ReactorManager.iInitFlag )
		return iRetCode;
	
	lock( fg_ReactorManager.Mutex );

	pRemoveHashItem = remove_hash_tbl( fg_ReactorManager.pReactorTbl, iReactorId );
	if ( pRemoveHashItem )
	{
		CReactor *pReactor = NULL;

		pReactor = CONTAINER_OF(HItem,pRemoveHashItem,CReactor);

#if (LOG_SUPPORT)
		//LOGD( "pReactor->pNetEngine->release( pReactor->pNetEngine );\r\n" );
#endif

		pReactor->pNetEngine->release( pReactor->pNetEngine );
#if (LOG_SUPPORT)
		//LOGD( "destory_engine( &pReactor->pNetEngine );\r\n" );
#endif

#if (LOG_SUPPORT)
		//LOGD( "destory_engine( &pReactor->pNetEngine );\r\n" );
#endif

		destory_engine( &(pReactor->pNetEngine) );

#if (LOG_SUPPORT)
		//LOGD( "destory_hash_tbl( &pReactor->pSocketTbl );\r\n" );
#endif

		destory_hash_tbl( &(pReactor->pSocketTbl) );

		mem_free( pReactor );
		pReactor = NULL;

		iRetCode = OP_SUCCESS;
	}

	unlock( fg_ReactorManager.Mutex );

	return iRetCode;
}

//向反应器添加套接字
int32_t add_reactor_socket( int32_t iReactorId, int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;
	const CHashItem *pSearchHashItem = NULL;

	if ( !fg_ReactorManager.iInitFlag )
		return iRetCode;
	

	lock( fg_ReactorManager.Mutex );

	pSearchHashItem = search_hash_tbl( fg_ReactorManager.pReactorTbl, iReactorId );
	if ( pSearchHashItem )
	{
		CReactor *pReactor = NULL;

		pReactor = CONTAINER_OF(HItem,pSearchHashItem,CReactor);

		if ( pReactor->pNetEngine && pReactor->pNetEngine->add_socket )
			iRetCode = pReactor->pNetEngine->add_socket( pReactor->pNetEngine, iSocketId );

		if ( iRetCode < 0 )
		{
			if ( pReactor->pNetEngine && pReactor->pNetEngine->remove_socket )
				iRetCode = pReactor->pNetEngine->remove_socket( pReactor->pNetEngine, iSocketId );
			
		}
	}
	
	unlock( fg_ReactorManager.Mutex );

	return iRetCode;

}

//注册反应器回调函数
int32_t registry_reactor_callback( int32_t iReactorId, reactor_callback_t fcallback )
{
	int32_t iRetCode = OP_FAILURE;
	const CHashItem *pSearchHashItem = NULL;

	if ( !fg_ReactorManager.iInitFlag )
		return iRetCode;
	

	lock( fg_ReactorManager.Mutex );

	pSearchHashItem = search_hash_tbl( fg_ReactorManager.pReactorTbl, iReactorId );
	if ( pSearchHashItem )
	{
		CReactor *pReactor = NULL;

		pReactor = CONTAINER_OF(HItem,pSearchHashItem,CReactor);

		pReactor->reactor_callback = fcallback;

		iRetCode = OP_SUCCESS;
	}
	
	unlock( fg_ReactorManager.Mutex );

	return iRetCode;
}

/*****************************************************************************************
* 套接字创建接口START
******************************************************************************************/

//创建套接字接口
int32_t create_socket( const char *pIP, int16u_t iPort, 
						const char *pLocalIP, int16u_t iLocalPort, int32_t iSocketType )
{
	int32_t iRetCode = OP_FAILURE;

	if ( pIP && iPort > 0 )
	{
#if (__OS_WIN32__)	
		SOCKET tempSocket = 0;
		int32_t iStreamType = -1;

		switch ( iSocketType )
		{
		case SOCKET_CLIENT_TCP:
			{
				iStreamType = SOCK_STREAM;
			}
			break ;

		case SOCKET_CLIENT_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}
			break ;

		case SOCKET_SERVER_TCP:
			{
				iStreamType = SOCK_STREAM;
			}
			break ;

		case SOCKET_SERVER_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
		case SOCKET_CLIENT_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
		case SOCKET_SERVER_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
		default:
			{

			}break ;
		}//iSocketType to iStreamType
		if ( iStreamType >= 0 )
		{
			tempSocket = socket(AF_INET,iStreamType,0);

			if( tempSocket !=INVALID_SOCKET )
			{
				switch ( iSocketType )
				{
				case SOCKET_CLIENT_TCP:
				case SOCKET_CLIENT_UDP:
					{
						struct sockaddr_in localAddress, serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_port = htons(iPort);
						
						if ( *pIP >= '0' && *pIP <= '9' )
							serverAddress.sin_addr.S_un.S_addr = inet_addr(pIP);
						else
						{
							struct hostent *hostinfo = NULL;

							hostinfo = gethostbyname(pIP);
							if (hostinfo == NULL)
							{

								LOGD("Unknown host %s.\r\n");
								//set_error_code( SDK_ERROR_NO_SIGNAL );
								set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);//没有网络与服务器地址错误,目前无法区分
								goto FAILURE;

							}
							serverAddress.sin_addr = *((struct in_addr *) hostinfo->h_addr);
						}
						
						memset(&localAddress,0,sizeof(localAddress));

						if ( pLocalIP )
						{
							localAddress.sin_family=AF_INET;
							localAddress.sin_port = htons(iLocalPort);
							
							if ( *pIP >= '0' && *pIP <= '9' )
								localAddress.sin_addr.S_un.S_addr = inet_addr(pLocalIP);
							else
							{
								struct hostent *hostinfo = NULL;

								hostinfo = gethostbyname(pLocalIP);
								if (hostinfo == NULL)
								{

									LOGD("Unknown host %s.\r\n");
									//set_error_code( SDK_ERROR_NO_SIGNAL );
									set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);//没有网络与服务器地址错误,目前无法区分
									goto FAILURE;

								}
								localAddress.sin_addr = *((struct in_addr *) hostinfo->h_addr);
							}
						}

						if ( SOCKET_CLIENT_UDP == iSocketType )
						{
							if ( bind( tempSocket,(const struct sockaddr *)&localAddress, sizeof(localAddress) ) < 0 )
							{
								goto FAILURE;
							}
						}

						//建立和服务器的连接 
						if(connect(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR)
						{
#if (__OS_LINUX__)
							if ( !(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) )
#elif (__OS_WIN32__)
							int32_t iErrNo = WSAGetLastError();
							printf( "iErrNo-->%d.\r\n", iErrNo );
							if ( !(WSAEWOULDBLOCK == iErrNo || WSAEINTR == iErrNo) )
#endif
							{
								//printf( "errno-->%d.\r\n", errno );
							}

							set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);
							//printf("建立连接失败！");
							
						}
						else
							iRetCode = tempSocket;
					}
					break ;

				case SOCKET_SERVER_TCP:
				case SOCKET_SERVER_UDP:
					{
						struct sockaddr_in serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
						serverAddress.sin_port = htons(iPort);

						if ( set_socket_option( tempSocket, SOCKET_OPTION_REUSE_ADDR, NULL, 0 ) >= 0 )
						{
							if ( iSocketType == SOCKET_SERVER_TCP )
							{
								int iOpRet = bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress) );
								//绑定 
								if( iOpRet==SOCKET_ERROR)
								{
									//printf("套接字绑定到端口失败！端口: %d/n",iPort);

								}
								else
								{
									//进入侦听状态 
									iOpRet = listen(tempSocket,20);
									if( iOpRet == SOCKET_ERROR )
									{
										//printf("侦听失败！");

									}
									else
										iRetCode = tempSocket;
								}
							}
							else
							{
								if(bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR)
								{
								}
								else
									iRetCode = tempSocket;
							}
						}

					}break ;
				case SOCKET_CLIENT_MULTICAST:
					{

					}break ;
				case SOCKET_SERVER_MULTICAST:
					{

					}break ;
				default:
					{

					}break ;
				}
			}
		}
#elif (__OS_LINUX__)

		int32_t tempSocket = 0;
		int32_t iStreamType = -1;

		switch ( iSocketType )
		{
		case SOCKET_CLIENT_TCP:
			{
				iStreamType = SOCK_STREAM;
			}
			break ;

		case SOCKET_CLIENT_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}
			break ;

		case SOCKET_SERVER_TCP:
			{
				iStreamType = SOCK_STREAM;
			}
			break ;

		case SOCKET_SERVER_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}
			break ;

		case SOCKET_CLIENT_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}
			break ;

		case SOCKET_SERVER_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}
			break ;

		default:
			break ;
		}
		if ( iStreamType >= 0 )
		{
			tempSocket = socket(AF_INET, iStreamType, 0);
			if( tempSocket > 0)
			{
				switch ( iSocketType )
				{
				case SOCKET_CLIENT_TCP:
				case SOCKET_CLIENT_UDP:
					{
					#if 0
						if(iStreamType == SOCK_STREAM)
						{
							int flags = fcntl(tempSocket, F_GETFL, 0);
							fcntl(tempSocket, F_SETFL, flags | O_NONBLOCK); //设置为非阻塞模式,有时connect会阻塞
						}
					#endif

						struct sockaddr_in serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_port = htons(iPort);
						
						if ( *pIP >= '0' && *pIP <= '9' )
							serverAddress.sin_addr.s_addr = inet_addr(pIP);
						else
						{
							struct hostent *hostinfo = NULL;
							int i = 0;
							char str[32] = { 0x00, };

							hostinfo = gethostbyname(pIP);
							if (hostinfo == NULL)
							{
							#if (LOG_SUPPORT)
								LOGD( "Unknown host %s.\n", pIP );
							#endif
							#if 0
								if(HOST_NOT_FOUND == h_errno)
								{
									set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);
								}
								else
								{
									set_error_code(SDK_ERROR_NO_SIGNAL);
								}
							#endif
								set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);//没有网络与服务器地址错误,目前无法区分
								goto FAILURE;

							}

							serverAddress.sin_addr = *((struct in_addr *) ((void *)hostinfo->h_addr_list[0]));
						}
						
						#if (LOG_SUPPORT)
							LOGD("host %s:%d.\n", pIP, iPort);
						#endif
						//建立和服务器的连接 
						if(connect(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0)
						{
							set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);
							LOGE("connect failed..\n");
						}
						else
							iRetCode = tempSocket;
					}
					break ;

				case SOCKET_SERVER_TCP:
				case SOCKET_SERVER_UDP:
					{
						struct sockaddr_in serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
						serverAddress.sin_port = htons(iPort);

						if ( iSocketType == SOCKET_SERVER_TCP )
						{
							if ( set_socket_option( tempSocket, SOCKET_OPTION_REUSE_ADDR, NULL, 0 ) >= 0 )
							{
								//绑定 
								if(bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0)
								{
									LOGD("bind failed??????????????");

								}
								else
								{
									//进入侦听状态 
									if(listen(tempSocket,20) < 0)
									{
										LOGD("listen failed.");
									}
									else
										iRetCode = tempSocket;
								}
							}
						}
						else
						{
							//绑定 
							if(bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
								LOGD("bind failed????????????????");

							}
							else
								iRetCode = tempSocket;
						}
					}break ;
				case SOCKET_CLIENT_MULTICAST:
					{

					}break ;
				case SOCKET_SERVER_MULTICAST:
					{

					}break ;
				default:
					{

					}break ;
				}

				if ( iRetCode < 0 )
				{
					close_socket( tempSocket );
					tempSocket = -1;
				}
			}
			else
			{
				LOGE("create socket failed! value:%d errcode:%s\n", tempSocket, strerror(errno));
			}
		}
		else
			LOGD("!if ( iStreamType >= 0 ) failed????????????????");

#elif (__OS_IOS__)

        int32_t tempSocket = 0;
		int32_t iStreamType = -1;
        
		switch ( iSocketType )
		{
            case SOCKET_CLIENT_TCP:
			{
				iStreamType = SOCK_STREAM;
			}break ;
            case SOCKET_CLIENT_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
            case SOCKET_SERVER_TCP:
			{
				iStreamType = SOCK_STREAM;
			}break ;
            case SOCKET_SERVER_UDP:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
            case SOCKET_CLIENT_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
            case SOCKET_SERVER_MULTICAST:
			{
				iStreamType = SOCK_DGRAM;
			}break ;
            default:
			{
				
			}break ;
		}
		if ( iStreamType >= 0 )
		{
			if( ( tempSocket = socket(AF_INET,iStreamType,0) ) > 0 )
			{
				switch ( iSocketType )
				{
                    case SOCKET_CLIENT_TCP:
                    case SOCKET_CLIENT_UDP:
					{
						struct sockaddr_in serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_port = htons(iPort);
						
						if ( *pIP >= '0' && *pIP <= '9' )
							serverAddress.sin_addr.s_addr = inet_addr(pIP);
						else
						{
							struct hostent *hostinfo = NULL;
							int i = 0;
							char str[32] = { 0x00, };
                            
							hostinfo = gethostbyname(pIP);
							if (hostinfo == NULL)
							{
#if (LOG_SUPPORT)
								char logBuf[128];
								sprintf( logBuf, "Unknown host %s.\n", pIP );
								LOGD( logBuf );
#endif
#if 0
                                if(HOST_NOT_FOUND == h_errno)
								{
									set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);
								}
								else
								{
									set_error_code(SDK_ERROR_NO_SIGNAL);
								}
#endif
								set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);//没有网络与服务器地址错误,目前无法区分
								goto FAILURE;
                                
							}
                            
							serverAddress.sin_addr =
                            *((struct in_addr *) ((void *)hostinfo->h_addr));
						}
						
						//建立和服务器的连接
						if(connect(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0)
						{
							LOGD("connect to server failed.");
							set_error_code(SDK_ERROR_CONNECT_WEB_SERVER);
						}
						else
							iRetCode = tempSocket;
					}
                    break ;
                        
                    case SOCKET_SERVER_TCP:
                    case SOCKET_SERVER_UDP:
					{
						struct sockaddr_in serverAddress;
						memset(&serverAddress,0,sizeof(serverAddress));
						serverAddress.sin_family=AF_INET;
						serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
						serverAddress.sin_port = htons(iPort);
                        
						if ( iSocketType == SOCKET_SERVER_TCP )
						{
							if ( set_socket_option( tempSocket, SOCKET_OPTION_REUSE_ADDR, NULL, 0 ) >= 0 )
							{
								//绑定
								if(bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
									LOGD("bind failed??????????????");
                                    
								}
								else
								{
									//进入侦听状态
									if(listen(tempSocket,20) < 0){
										LOGD("listen failed.");
                                        
									}
									else
										iRetCode = tempSocket;
								}
							}
						}
						else
						{
							//绑定
							if(bind(tempSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
								LOGD("bind failed????????????????");
                                
							}
							else
								iRetCode = tempSocket;
						}
					}break ;
                    case SOCKET_CLIENT_MULTICAST:
					{
                        
					}break ;
                    case SOCKET_SERVER_MULTICAST:
					{
                        
					}break ;
                    default:
					{
                        
					}break ;
				}
                
				if ( iRetCode < 0 )
				{
					close_socket( tempSocket );
					tempSocket = -1;
				}
			}
#if (LOG_SUPPORT)
			else
			{
				LOGD("!if( ( tempSocket = socket(AF_INET,iStream failed????????????????????");
			}
#endif
		}
		else
			LOGD("!if ( iStreamType >= 0 ) failed????????????????");

#endif
	}
	else
		LOGD("!if ( pIP && iPort > 0 ) failed????????????????");

FAILURE:

	
	return iRetCode;
}

//关闭套接字接口
int32_t close_socket( int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;

	if ( iSocketId > 0 )
	{
#if (__OS_WIN32__)
		if ( closesocket( iSocketId ) >= 0 )
			iRetCode = OP_SUCCESS;
#elif (__OS_LINUX__)
		if ( close( iSocketId ) >= 0 )
			iRetCode = OP_SUCCESS;
#elif (__OS_IOS__)
        if ( close( iSocketId ) >= 0 )
			iRetCode = OP_SUCCESS;
#endif

	}

	return iRetCode;
}

//接收新的客户端套接字
int32_t net_accept( int32_t iListenSocketId, CNetAddr *pAddr )
{
	int32_t iRetCode = -1;

	if ( iListenSocketId > 0 && pAddr )
	{
#if (__OS_WIN32__)
		
		struct sockaddr_in stCliAddr;
		int32_t iLen = 0;
		char *pIP = NULL;

		iLen=sizeof(stCliAddr);
		
		iRetCode = accept( iListenSocketId, (struct sockaddr *)&stCliAddr, &iLen );
		pIP = inet_ntoa( stCliAddr.sin_addr );
		if ( pIP )
			memcpy( pAddr->IP, pIP, strlen(pIP) + 1 );
		pAddr->iPort = ntohs(stCliAddr.sin_port);

#elif (__OS_LINUX__)

		struct sockaddr_in stCliAddr;
		int32_t iLen = 0;
		char *pIP = NULL;

		iLen=sizeof(stCliAddr);
		
		iRetCode = accept( iListenSocketId, (struct sockaddr *)&stCliAddr, &iLen );
		pIP = inet_ntoa( stCliAddr.sin_addr );
		if ( pIP )
			memcpy( pAddr->IP, pIP, strlen(pIP) + 1 );
		pAddr->iPort = ntohs(stCliAddr.sin_port);
#elif (__OS_IOS__)
        struct sockaddr_in stCliAddr;
		int32_t iLen = 0;
		char *pIP = NULL;
        
		iLen=sizeof(stCliAddr);
		
		iRetCode = accept( iListenSocketId, (struct sockaddr *)&stCliAddr, &iLen );
		pIP = inet_ntoa( stCliAddr.sin_addr );
		if ( pIP )
			memcpy( pAddr->IP, pIP, strlen(pIP) + 1 );
		pAddr->iPort = ntohs(stCliAddr.sin_port);

#endif


	}

	return iRetCode;
}


//套接字属性设置
int32_t set_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize )
{
	int32_t iRetCode = OP_FAILURE;

	if ( iSocketId > 0 && iCmd >= 0 )
	{
		switch ( iCmd )
		{
		case SOCKET_OPTION_SET_NO_BLOCK:
			{
#if (__OS_WIN32__)
				unsigned long ul = 1;
				int iOpRet = ioctlsocket( iSocketId, FIONBIO, (unsigned long*)&ul );
				if ( iOpRet == SOCKET_ERROR )
					;
				else
					iRetCode = OP_SUCCESS;
#elif (__OS_LINUX__)

				int32_t iFlags = fcntl( iSocketId, F_GETFL, 0 );
				if ( fcntl( iSocketId, F_SETFL, iFlags | O_NONBLOCK ) >= 0 )
					iRetCode = OP_SUCCESS;
#elif (__OS_IOS__)
                int32_t iFlags = fcntl( iSocketId, F_GETFL, 0 );
				if ( fcntl( iSocketId, F_SETFL, iFlags | O_NONBLOCK ) >= 0 )
					iRetCode = OP_SUCCESS;

#endif

			}break ;
		case SOCKET_OPTION_SET_SEND_BUFFER:
			{
#if (__OS_WIN32__)
				CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					int32_t iOpRet = 
						setsockopt( iSocketId, SOL_SOCKET, SO_SNDBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize) );

					if ( SOCKET_ERROR != iOpRet )
						iRetCode = OP_SUCCESS;
				}

#elif (__OS_LINUX__)

				CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					int32_t iOpRet = 
						setsockopt( iSocketId, SOL_SOCKET, SO_SNDBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize) );

					if (iOpRet >= 0 )
						iRetCode = OP_SUCCESS;
				}
#elif (__OS_IOS__)
                CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					int32_t iOpRet =
                    setsockopt( iSocketId, SOL_SOCKET, SO_SNDBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize) );
                    
					if (iOpRet >= 0 )
						iRetCode = OP_SUCCESS;
				}


#endif
			}break ;
		case SOCKET_OPTION_SET_RECV_BUFFER:
			{
#if (__OS_WIN32__)
				CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					if ( SOCKET_ERROR !=
						setsockopt( iSocketId, SOL_SOCKET, SO_RCVBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize) ) )
						iRetCode = OP_SUCCESS;
				}
#elif (__OS_LINUX__)
				
				CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					int32_t iOpRet = 
						setsockopt( iSocketId, SOL_SOCKET, SO_RCVBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize ) );

					if (iOpRet >= 0 )
						iRetCode = OP_SUCCESS;
				}
                
#elif (__OS_IOS__)
                
                CSockParam *pSockParam = (CSockParam *)pParam;
				
				if ( pSockParam )
				{
					int32_t iOpRet =
                    setsockopt( iSocketId, SOL_SOCKET, SO_RCVBUF, (const char *)&pSockParam->iBuffSize, sizeof(pSockParam->iBuffSize ) );
                    
					if (iOpRet >= 0 )
						iRetCode = OP_SUCCESS;
				}
				
#endif

			}break ;
		case SOCKET_OPTION_REUSE_ADDR:
			{
#if (__OS_WIN32__)
				BOOL bReuseaddr=TRUE;
				if ( SOCKET_ERROR != setsockopt( iSocketId, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(BOOL)) )
					iRetCode = OP_SUCCESS;
#elif (__OS_LINUX__)

				int32_t iReUse = 1;
				if ( setsockopt( iSocketId, SOL_SOCKET, SO_REUSEADDR, (const char*)&iReUse, sizeof(iReUse)) >= 0 )
					iRetCode = OP_SUCCESS;
                
#elif (__OS_IOS__)
                int32_t iReUse = 1;
				if ( setsockopt( iSocketId, SOL_SOCKET, SO_REUSEADDR, (const char*)&iReUse, sizeof(iReUse)) >= 0 )
					iRetCode = OP_SUCCESS;
	
#endif
			}break ;
		case SOCKET_OPTION_SET_SENDTIMEOUT:
			{
#if (__OS_WIN32__)
				CSockParam *pSockParam = (CSockParam *)pParam;

				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet = 
							setsockopt( iSocketId, SOL_SOCKET, SO_SNDTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( SOCKET_ERROR != iOpRet )
							iRetCode = OP_SUCCESS;
				}
#elif (__OS_LINUX__)

				CSockParam *pSockParam = (CSockParam *)pParam;

				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet = 
							setsockopt( iSocketId, SOL_SOCKET, SO_SNDTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( iOpRet >= 0 )
							iRetCode = OP_SUCCESS;
				}
                
#elif (__OS_IOS__)
                CSockParam *pSockParam = (CSockParam *)pParam;
                
				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet =
                    setsockopt( iSocketId, SOL_SOCKET, SO_SNDTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( iOpRet >= 0 )
                        iRetCode = OP_SUCCESS;
				}

#endif
			}break ;
		case SOCKET_OPTION_SET_RECVTIMEOUT:
			{
#if (__OS_WIN32__)
				CSockParam *pSockParam = (CSockParam *)pParam;

				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet = 
							setsockopt( iSocketId, SOL_SOCKET, SO_RCVTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( SOCKET_ERROR != iOpRet )
							iRetCode = OP_SUCCESS;
				}
#elif (__OS_LINUX__)

				CSockParam *pSockParam = (CSockParam *)pParam;

				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet = 
							setsockopt( iSocketId, SOL_SOCKET, SO_RCVTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( iOpRet >= 0 )
							iRetCode = OP_SUCCESS;
				}
                
#elif (__OS_IOS__)
                CSockParam *pSockParam = (CSockParam *)pParam;
                
				if ( pSockParam )
				{
					int32_t iTimeOut = pSockParam->iTimeOut;
					int32_t iOpRet =
                    setsockopt( iSocketId, SOL_SOCKET, SO_RCVTIMEO, (const char *)&iTimeOut, sizeof(iTimeOut) );
					if ( iOpRet >= 0 )
                        iRetCode = OP_SUCCESS;
				}

#endif
			}break ;
		default:
			{

			}break ;
		}
	}

	return iRetCode;
}

int32_t get_socket_option( int32_t iSocketId, int32_t iCmd, void *pParam, int32_t iParamSize )
{
	int32_t iRetCode = OP_FAILURE;

	return iRetCode;
}

int32_t net_send( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)

	if ( iSocketId > 0 && pDataBuf && iDataLen > 0 )
	{
		int iNSent = send( iSocketId, pDataBuf, iDataLen, 0 );
		
		if( iNSent == SOCKET_ERROR )
		{

		}
		else
			iRetCode = iNSent;//N Bytes sent.
	}

#elif (__OS_LINUX__)

	if ( iSocketId > 0 && pDataBuf && iDataLen > 0 )
	{
		int iNSent = send( iSocketId, pDataBuf, iDataLen, 0 );

#if (LOG_SUPPORT)
		LOGD("send: iSocketId[%d], iDataLen[%d], iNSent[%d]\n", iSocketId, iDataLen, iNSent);
#endif

		if( iNSent < 0 )
		{

		}
		else
			iRetCode = iNSent;//N Bytes sent.
	}
    
#elif (__OS_IOS__)
    if ( iSocketId > 0 && pDataBuf && iDataLen > 0 )
	{
		int iNSent = send( iSocketId, pDataBuf, iDataLen, 0 );
		
		if( iNSent < 0 )
		{
            
		}
		else
			iRetCode = iNSent;//N Bytes sent.
	}
    

#endif


	return iRetCode;
}

int32_t net_recv( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen )
{
	int32_t iRetCode = OP_FAILURE;

	if ( iSocketId > 0 && pDataBuf && iDataBufLen > 0 )
	{
#if (__OS_WIN32__)

		int iNReceived = recv( iSocketId, pDataBuf, iDataBufLen, 0 );
		if ( iNReceived == SOCKET_ERROR)
		{

		}
		else
			iRetCode = iNReceived;
#elif (__OS_LINUX__)

	int iNReceived = recv( iSocketId, pDataBuf, iDataBufLen, 0 );

#if (LOG_SUPPORT)
			LOGD("recv: iSocketId[%d], iDataBufLen[%d], iNReceived[%d]\n", iSocketId, iDataBufLen, iNReceived);
#endif

	if ( iNReceived < 0 )
	{

	}
	else
		iRetCode = iNReceived;
#elif (__OS_IOS__)
        
    int iNReceived = recv( iSocketId, pDataBuf, iDataBufLen, 0 );
    if ( iNReceived < 0 )
    {
            
    }
    else
        iRetCode = iNReceived;
#endif
	}

	return iRetCode;
}

//UDP
int32_t net_sendto( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataLen, CNetAddr *pPeerAddr )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)
	struct sockaddr_in addr;
	int iLen = sizeof(addr);
	int iNReceived = -1;

	memset( &addr, 0x00, sizeof(addr) );
	if ( pPeerAddr )
	{
		char *pIP = pPeerAddr->IP;

		memset(&addr,0,sizeof(addr));
		addr.sin_family=AF_INET;
		addr.sin_port = htons(pPeerAddr->iPort);
		
		if ( *pIP >= '0' && *pIP <= '9' )
			addr.sin_addr.S_un.S_addr = inet_addr(pIP);
		else
		{
			struct hostent *hostinfo = NULL;

			hostinfo = gethostbyname(pIP);
			if (hostinfo == NULL)
			{
				//printf("Unknown host %s.\n", pIP);

				return iRetCode;
			}
			addr.sin_addr = *((struct in_addr *) hostinfo->h_addr);
		}

		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, (struct sockaddr *)&addr, iLen );
	}
	else
		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, NULL, 0 );

	if ( iNReceived == SOCKET_ERROR)
	{

	}
	else
		iRetCode = iNReceived;
#elif (__OS_LINUX__)

	struct sockaddr_in addr;
	int iLen = sizeof(addr);
	int iNReceived = -1;

	memset( &addr, 0x00, sizeof(addr) );
	if ( pPeerAddr )
	{
		char *pIP = pPeerAddr->IP;

		memset(&addr,0,sizeof(addr));
		addr.sin_family=AF_INET;
		addr.sin_port = htons(pPeerAddr->iPort);
		
		if ( *pIP >= '0' && *pIP <= '9' )
			addr.sin_addr.s_addr = inet_addr(pIP);
		else
		{
			struct hostent *hostinfo = NULL;

			hostinfo = gethostbyname(pIP);
			if (hostinfo == NULL)
			{
			//	printf("Unknown host %s.\n", pIP);

				return iRetCode;
			}
			addr.sin_addr = *((struct in_addr *) hostinfo->h_addr);
		}

		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, (struct sockaddr *)&addr, iLen );
	}
	else
		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, NULL, 0 );

	if ( iNReceived < 0 )
	{

	}
	else
		iRetCode = iNReceived;
#elif (__OS_IOS__)
    struct sockaddr_in addr;
	int iLen = sizeof(addr);
	int iNReceived = -1;
    
	memset( &addr, 0x00, sizeof(addr) );
	if ( pPeerAddr )
	{
		char *pIP = pPeerAddr->IP;
        
		memset(&addr,0,sizeof(addr));
		addr.sin_family=AF_INET;
		addr.sin_port = htons(pPeerAddr->iPort);
		
		if ( *pIP >= '0' && *pIP <= '9' )
			addr.sin_addr.s_addr = inet_addr(pIP);
		else
		{
			struct hostent *hostinfo = NULL;
            
			hostinfo = gethostbyname(pIP);
			if (hostinfo == NULL)
			{
                //	printf("Unknown host %s.\n", pIP);
                
				return iRetCode;
			}
			addr.sin_addr = *((struct in_addr *) hostinfo->h_addr);
		}
        
		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, (struct sockaddr *)&addr, iLen );
	}
	else
		iNReceived = sendto( iSocketId, pDataBuf, iDataLen, 0, NULL, 0 );
    
	if ( iNReceived < 0 )
	{
        
	}
	else
		iRetCode = iNReceived;
#endif

	return iRetCode;
}

int32_t net_recvfrom( int32_t iSocketId, int8u_t *pDataBuf, int32_t iDataBufLen, CNetAddr *pPeerNetAddr )
{
	int32_t iRetCode = OP_FAILURE;

#if (__OS_WIN32__)
		struct sockaddr_in addr;
		int32_t iNReceived = -1;
		int32_t iOutLen = sizeof(addr);

		memset( &addr, 0x00, sizeof(addr) );
		iNReceived = recvfrom( iSocketId, pDataBuf, iDataBufLen, 0, (struct sockaddr *)&addr, &iOutLen);
		if ( iNReceived == SOCKET_ERROR)
		{
	
		}
		else
		{
			if ( pPeerNetAddr )
			{
				char *pIP = inet_ntoa( addr.sin_addr );

				if ( pIP )
					memcpy( pPeerNetAddr->IP, pIP, strlen(pIP) + 1 );
				pPeerNetAddr->iPort = ntohs(addr.sin_port);
			}
			iRetCode = iNReceived;
		}

#elif (__OS_LINUX__)

	struct sockaddr_in addr;
	int32_t iNReceived = -1;
	int32_t iOutLen = 0;

	memset( &addr, 0x00, sizeof(addr) );
	iNReceived = recvfrom( iSocketId, pDataBuf, iDataBufLen, 0, (struct sockaddr *)&addr, &iOutLen );
	if ( iNReceived < 0 )
	{

	}
	else
	{
		if ( pPeerNetAddr )
		{
			char *pIP = inet_ntoa( addr.sin_addr );

			if ( pIP )
				memcpy( pPeerNetAddr->IP, pIP, strlen(pIP) + 1 );
			pPeerNetAddr->iPort = ntohs(addr.sin_port);
		}
		iRetCode = iNReceived;
	}
#elif (__OS_IOS__)
    struct sockaddr_in addr;
	int32_t iNReceived = -1;
	int32_t iOutLen = 0;
    
	memset( &addr, 0x00, sizeof(addr) );
	iNReceived = recvfrom( iSocketId, pDataBuf, iDataBufLen, 0, (struct sockaddr *)&addr, &iOutLen );
	if ( iNReceived < 0 )
	{
        
	}
	else
	{
		if ( pPeerNetAddr )
		{
			char *pIP = inet_ntoa( addr.sin_addr );
            
			if ( pIP )
				memcpy( pPeerNetAddr->IP, pIP, strlen(pIP) + 1 );
			pPeerNetAddr->iPort = ntohs(addr.sin_port);
		}
		iRetCode = iNReceived;
	}

#endif

	return iRetCode;
}

int32u_t net_ip2n( const int8_t *pIP )
{
	int32u_t iRetCode = 0;

	iRetCode = inet_addr( pIP );

	return iRetCode;
}

const int8_t * net_n2ip( int32u_t iIP )
{
	const int8_t *pRetCode = NULL;
	struct in_addr inaddr;

	inaddr.s_addr = iIP;
	pRetCode = inet_ntoa( inaddr );

	return pRetCode;
}

//活动本机IP
const int8_t *net_get_local_ip( void )
{
	const int8_t *pLocalIP = NULL;

	char pHostNameBuf[128] = { 0x00, };
	struct hostent *pHostAddr = NULL;
	struct in_addr addr;

	gethostname( pHostNameBuf, sizeof(pHostNameBuf) );
	pHostAddr = gethostbyname( pHostNameBuf );
	if ( pHostAddr )
	{
		memcpy( &addr.s_addr, pHostAddr->h_addr_list[0], 
				sizeof(addr.s_addr) );

		pLocalIP = inet_ntoa( addr );
	}

	return pLocalIP;
}

/*****************************************************************************************
* 套接字创建接口END
******************************************************************************************/


//从反应器中删除套接字
int32_t remove_reactor_socket( int32_t iReactorId, int32_t iSocketId )
{
	int32_t iRetCode = OP_FAILURE;
	
	const CHashItem *pSearchHashItem = NULL;

	if ( !fg_ReactorManager.iInitFlag )
		return iRetCode;
	

	lock( fg_ReactorManager.Mutex );

	pSearchHashItem = search_hash_tbl( fg_ReactorManager.pReactorTbl, iReactorId );
	if ( pSearchHashItem )
	{
		CReactor *pReactor = NULL;
		//CSocket *pDelSocket = NULL;
		CHashItem *pDelHashItem = NULL;

		pReactor = CONTAINER_OF(HItem,pSearchHashItem,CReactor);

		if ( pReactor->pNetEngine && pReactor->pNetEngine->remove_socket )
			iRetCode = pReactor->pNetEngine->remove_socket( pReactor->pNetEngine, iSocketId );
		else
			LOGD("!if ( pReactor->pNetEngine && pReactor->pNetE failed??????????????");

	}
	else
		LOGD("!if ( pSearchHashItem ) failed?????????????");

	unlock( fg_ReactorManager.Mutex );

	return iRetCode;

}

static int32_t init_reactor_manager( void )
{
	int32_t iRetCode = OP_FAILURE;

	fg_ReactorManager.pReactorTbl = create_hash_tbl( 6 );
	if ( fg_ReactorManager.pReactorTbl )
	{
		fg_ReactorManager.Mutex = create_mutex();
		if ( fg_ReactorManager.Mutex )
		{
#if (__OS_WIN32__)
			WSADATA wsa;
			int iOpRet = WSAStartup(MAKEWORD(2,2),&wsa);
			if( iOpRet == 0 )
			{
#endif
			fg_ReactorManager.iInitFlag = 1;
			iRetCode = OP_SUCCESS;
#if (__OS_WIN32__)
			}
#endif
		}
		else
		{
			destory_hash_tbl( &fg_ReactorManager.pReactorTbl );
		}
	}
	
	return iRetCode;
}



