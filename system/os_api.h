/**************************************************************************************************
* File Name: os_api.h
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

#ifndef __OS_API_H__
#define __OS_API_H__

#include "typedefs.h"


#if (__OS_WIN32__)
#include <windows.h>
#elif (__OS_LINUX__)
#include <errno.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#elif (__OS_IOS__)
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif

//vos define
#ifndef  VOS_NULL
#define  VOS_NULL               NULL
#endif

#ifndef  VOS_SUCCESS
#define  VOS_SUCCESS             0
#endif

#ifndef  VOS_FAIL
#define  VOS_FAIL               -1
#endif

	typedef  enum
	{
		VOS_OK                  =      0x0,
		VOS_ERR                 =      0x1,
		VOS_ERR_PARAM           =      0x2,    
		VOS_ERR_MEM             =      0x3,
		VOS_ERR_SYS             =      0x4,    

		VOS_ERR_QUE_EMPTY       =      0x1000,    
		VOS_ERR_QUE_LEN         =      0x1001,
		VOS_ERR_QUE_TIMEOUT     =      0x1002,
		VOS_ERR_MUTEX_TIMEOUT   =      0x1003,    
		VOS_ERR_SEMA_TIMEOUT    =      0x1004,    
		VOS_ERR_LIST_EMPTY      =      0x1005, 
		VOS_ERR_DATANOTENOUGH   =      0x1006,

		VOS_SYS_ERR_BUTT

	}VOS_SYS_ERR;
//vos define end.

/**************************************************************************************************
* 宏定义:
***************************************************************************************************/
#define OS_THREAD_PRIORITY_NORMAL  (1)
#define OS_THREAD_PRIORITY_HIGH  (2)
#define OS_THREAD_PRIORITY_LOW  (3)

/**************************************************************************************************
* 类型定义:
***************************************************************************************************/
typedef void *(*os_thread_t)( void * );

#if (__OS_WIN32__)
#define MUTEX_TYPE  CRITICAL_SECTION

typedef CRITICAL_SECTION * CMutex;

typedef struct CCondMutex_t
{
	enum {
		SIGNAL = 0,
		BROADCAST = 1,
		MAX_EVENTS = 2
	  }C_COND_MUTEX_ENUM;

	  HANDLE events_[MAX_EVENTS];
	  // Signal and broadcast event HANDLEs.

	  CMutex Mutex;
}CCondMutex;

typedef void *CSem;
typedef int  CThreadKey;//win32暂时不处理


#elif (__OS_LINUX__)

#define MUTEX_TYPE  pthread_mutex_t

typedef pthread_mutex_t * CMutex;

typedef sem_t * CSem;

typedef void * CCondMutex;

typedef pthread_key_t  CThreadKey;
#elif (__OS_IOS__)
    
#define MUTEX_TYPE pthread_mutex_t
typedef pthread_mutex_t * CMutex;
typedef sem_t * CSem;
typedef void *CCondMutex;
typedef pthread_key_t  CThreadKey;

    
#endif


//跨平台系统调用接口定义
//线程接口
EXPORT_API int32u_t os_thread_create( os_thread_t fthread, void *pParam, int32_t iPriority );

EXPORT_API int32_t os_thread_destory( int32u_t iThreadId );

//互斥锁接口
EXPORT_API CMutex create_mutex( void );

EXPORT_API int32_t init_mutex( CMutex pMutex );

EXPORT_API int32_t lock( CMutex mutex );

EXPORT_API int32_t unlock( CMutex mutex );

EXPORT_API int32_t destory_mutex( CMutex *pMutex );

//
EXPORT_API void os_sleep( int32_t iMileSecond );

//条件锁接口
EXPORT_API CCondMutex *create_cond_mutex( void );
EXPORT_API int32_t signal_cond_mutex( CCondMutex *pCondMutex );
EXPORT_API int32_t broadcast_cond_mutex( CCondMutex *pCondMutex );

EXPORT_API int32_t wait_cond_mutex( CCondMutex *pCondMutex );
EXPORT_API void destory_cond_mutex( CCondMutex *pCondMutex );

EXPORT_API int get_handle( void );

//事件
#ifdef WIN32

typedef struct tagVOSEvent 
{
	HANDLE EventHandle;
}VOS_Event;

#else

typedef struct tagVOSEvent 
{
	pthread_mutex_t EventMutex;
	pthread_cond_t  EventCond;
}VOS_Event;

#endif

LONG VOS_CreateEvent(VOS_Event *pstVosEvent);
LONG VOS_WaitEvent(VOS_Event *pstVosEvent, LONG lTimeOut);
LONG VOS_SetEvent(VOS_Event *pstVosEvent);
LONG VOS_ReSetEvent(VOS_Event *pstVosEvent);
LONG VOS_DestroyEvent(VOS_Event *pstVosEvent );

//信号量接口
EXPORT_API CSem create_sem( int32_t iMaxVal );
EXPORT_API int32_t wait_sem( CSem sem );
EXPORT_API int32_t post_sem( CSem sem );
EXPORT_API void destory_sem( CSem sem );

//信号处理接口

//

EXPORT_API int16u_t net2hosts( int16u_t iNetData );

EXPORT_API int16u_t host2nets( int16u_t iHostData );

EXPORT_API int32u_t net2hostl( int32u_t iNetData );

EXPORT_API int32u_t host2netl( int32u_t iHostData );

EXPORT_API int32_t get_ip_by_domain(int8_t* sDestIp, int8_t* sDomain);

//获取timetick
unsigned long os_get_timetick_value();

//线程全局变量接口
EXPORT_API int32_t os_thread_createKey(void*);
EXPORT_API int32_t os_thread_setValue(CThreadKey key, int32_t* pValue);
EXPORT_API void*   os_thread_getValue(CThreadKey key);
EXPORT_API int32_t os_thread_deleteKey();


//错误码接口
EXPORT_API int8_t *get_error_string(int32_t iErrorCode);
EXPORT_API int32_t get_error_code( void );
EXPORT_API void set_error_code(int32_t iErrorCode);


////////////////////线程私有的全局变量(每个线程独有的全局变量)///
static int8_t fg_ErrorInfoBuf[128] = {0};
static CThreadKey fg_ThreadKey;
extern  int  *My_Errno( void );
#define g_SdkErrNo  (*My_Errno())

////错误码定义
typedef enum
{
	ERROR_CODE_NO_ERR, 
	
	SYSTEM_ERROR = -0x0001, // 系统内部错误
	SDK_ERROR_NOT_INIT = -0x0002, //SDK没有初始化
	SDK_ERROR_NOT_SET_WWW_INFO = -0x0003, //没有设置WEB服务器	
	SDK_ERROR_CONNECT_WEB_SERVER = -0x0004, //连接WEB服务器失败
	SDK_ERROR_SEND_DATA = -0x0005, //发送数据失败
	SDK_ERROR_CONNECT_TO_DEVICE = -0x0006, //链接设备失败
	SDK_ERROR_OPEN_CHANNEL = -0x0007, //打开通道失败
	SDK_ERROR_CLOSE_CHANNEL = -0x0008, //关闭通道失败
	SDK_ERROR_INIT_DB_FAIL = -0x0009, //初始化本地数据库失败
	
	SDK_ERROR_NO_SIGNAL = -0x000A, //没有网络 （这种情况是手机没有wifi信号）
	SDK_ERROR_INPUT_PARAM = -0x000B,//参数无效
	SDK_ERROR_DEVICE_OFFLINE = -0x000C, //设备不在线 
	SDK_ERROR_RESPONSE_TIMEOUT = -0x000D, //响应超时
	SDK_ERROR_VERIFY = -0x000E,// 用户名或密码错误 
	SDK_ERROR_DEVICE_VERIFY = -0x0010,//设备访问密码错误
	
	WEB_ERROR_USER_EXIST = -0x0011,//用户已经存在
	WEB_ERROR_EMAIL_EXIST = -0x0012, //邮件已经存在
	WEB_ERROR_PHONE_EXIST = -0x0013, //手机号码已经存在
		
	WEB_ERROR_NOT_RIGHT = -0x0014,//无权限操作
	WEB_ERROR_NOT_OBJECT = -0x0015, //对象不存在
	
	WEB_ERROR_NOT_SESSION = -0x0016, //session不存在
	WEB_ERROR_SESSION_OFFLINE = -0x0017, //session强行下线
	WEB_ERROR_SESSION_USER_STOP = -0x0018, //session用户停用
	WEB_ERROR_NOT_SESSION_LOGIN_OTHER = -0x0019, //session用户在其他地方登录
	

}C_GIE_ERROR_CODE;


#ifdef __cplusplus
}
#endif

#endif/* __OS_API_H__ */

