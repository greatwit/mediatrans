#ifndef __LOG_H__
#define __LOG_H__

#include "typedefs.h"

#define LOG_SUPPORT  1



#ifdef __cplusplus
extern "C"
{
#endif

#if (LOG_SUPPORT)

#if (__OS_LINUX__)
#define ANDROID_SUPPORT  (1)
#include <android/log.h>
#endif


	/* C files should define LOG_TAG before including this header */
#define LOG_TAG "HN/JNI/main"
#ifndef LOG_TAG
# error You must define LOG_TAG
#endif

#ifdef ANDROID_SUPPORT
# define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
# define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARNING,LOG_TAG,__VA_ARGS__)
#else
# define LOGD(...)  (void)0
# define LOGV(...)  (void)0
#define  LOGI(...)  (void)0
#define  LOGE(...)  (void)0
#define  LOGW(...)  (void)0
#endif //end android support


typedef enum
{
	LOG_PRIORITY_EMERG, //�����������Ҫ����֪ͨ������Ա��
	LOG_PRIORITY_ALERT, //Ӧ�ñ��������������⣬��ϵͳ���ݿⱻ�ƻ���ISP���Ӷ�ʧ��
	LOG_PRIORITY_CRIT, //��Ҫ�������Ӳ�̴��󣬱������Ӷ�ʧ��
	LOG_PRIORITY_ERR, //���󣬲��Ƿǳ���������һ��ʱ�����޸����ɡ�
	LOG_PRIORITY_WARNING, //������Ϣ�����Ǵ��󣬱���ϵͳ����ʹ����85%�ȡ�
	LOG_PRIORITY_NOTICE, //���Ǵ��������Ҳ����Ҫ��������
	LOG_PRIORITY_INFO, //�鱨��Ϣ��������ϵͳ��Ϣ������ɧ�ű��棬�������ݵȣ�����Ҫ����
	LOG_PRIORITY_DEBUG, //������ϸ�Ŀ����鱨����Ϣ��ͨ��ֻ�ڵ���һ������ʱʹ�á�

	LOG_END
}C_LOG_PRIORITY;

typedef enum
{
	LOG_TYPE_FILE, //�ļ���־
	LOG_TYPE_NET,//������־(�ݲ���)
	LOG_TYPE_CONSOLE, //����̨��ӡ
	LOG_TYPE_FILE_CONSOLE,//����̨and�ļ���ӡ

	LOG_TYPE_END
}C_LOG_TYPE;

//���ã� �ر���־
EXPORT_API void enable_log( int32_t iIsEnabled, int32_t iPriority );

//������־����
EXPORT_API int32_t set_log( int32_t iLogType, void *pParam );

EXPORT_API int32_t release_log( int32_t iLogType, void *pParam);

//��־�ӿ�
EXPORT_API int32_t sys_log( int32_t iPriority, const char *pMsg );

//����̨��־�ӿ�
EXPORT_API int32_t console_log( int32_t iPriority, const char *pMsg );

EXPORT_API int32_t get_log_priority( void );

//��־�ӿں� 
#define LOGD1(msg)                                                                   \
	do	                                                                    \
{	                                                                    \
	char rreeerrlogBuf[1024] = {0};	                                    \
	int32_t iMsgLen = strlen(msg);	                                    \
	if ((iMsgLen < 512) && strlen(__FILE__) < 256)	                    \
{	                                                                \
	sprintf( rreeerrlogBuf, "%s:%d %s", __FILE__, __LINE__, msg );	\
	sys_log( get_log_priority(), rreeerrlogBuf );	                \
}	                                                                \
}while (0)	

//����̨���Խӿں� 
#define CONSOLED(msg)  \
    do	\
{	\
    char rreeerrlogBuf[1024] = {0};	\
    int32_t iMsgLen = strlen(msg);	\
    if ((iMsgLen < 512) && strlen(__FILE__) < 256)	\
{	\
    sprintf( rreeerrlogBuf, "%s:%d %s", __FILE__, __LINE__, msg );	\
    console_log( LOG_PRIORITY_DEBUG, rreeerrlogBuf );	\
}	\
}while (0)	


#else

#define enable_log(a,b) 
#define set_log(a,b) 
#define sys_log(a) 
#define LOGD1(msg) 

#endif

#ifdef __cplusplus
}
#endif


#endif/* __LOG_H__ */
