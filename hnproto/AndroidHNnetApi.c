/**************************************************************************************************
* File Name: HNnetApi.c
* Writer: xx
* Create Date: 2014-8-8 14:30
* Update Table:
*----------------------------------------------------------------
* 
*
*
*
***************************************************************************************************/

//#include "AndroidHNnetApi.h"
#include <HnProto.h>
#include "HNnetApi.h"
#include <datacache.h>
#include <jni.h>


#include <android/log.h>
#include <log.h>

#define JNI_API_NAME(A) 		Java_com_haineng_player_stream_NetProtoLib_##A
#define CALLBACK_CLASS_NAME 	"com/haineng/player/stream/NetProtoLib"

#define JNI_VERSION JNI_VERSION_1_6

JavaVM		*mJavaVm;
JNIEnv		*mEnv=NULL;
JNIEnv		*mRecvEnv=NULL;
jmethodID    mCallbackId;
jclass		 mAnalyzeCidUtil;

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	// Keep a reference on the Java VM.
	int result = -1;
	mJavaVm = vm;

	result = (*mJavaVm)->GetEnv(mJavaVm, (void**) &mEnv, JNI_VERSION);
	if(mEnv==NULL)
		LOGD("GetEnv failed, result:%d\n.", result);

	LOGD("JNI interface loaded.");
	return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) 
{
	//if(mRecvEnv)
	//	(*mJavaVm)->DetachCurrentThread(mJavaVm); 
}

int g_reactorid;
static CDataCache *mDatacache = NULL;
static char *mBuffer = NULL;
static int8u_t readbuff[4096] = {0};
#define READ_LENGHT sizeof(readbuff)

int32_t jcallback( int32_t iReactorId, int32_t iSocketId, int32_t iEvent )
{
	int result = -1;

	int len =0;
	char head[20] = {0};
	
	if(iSocketId==0xff)
	{
		if(mRecvEnv)
		{
			(*mJavaVm)->DetachCurrentThread(mJavaVm);
			LOGE("DetachCurrentThread=============\n");
		}
		return result;
	}

	len = net_recv(iSocketId, readbuff, READ_LENGHT);
	LOGE("receive data length:%d\n", len);
	if(len<0)
		return result;

	if(mRecvEnv)
	{
		write_datacache(mDatacache, readbuff, len);
		while(1)
		{
			if(get_datacache_size(mDatacache)<20)
				break;
			snifer_datacache(mDatacache, head, sizeof(head));
			HN_PROT_HEAD *prothead = ( HN_PROT_HEAD *)head;
	
			if(prothead->len <= get_datacache_size(mDatacache)-20)
			{
				mBuffer = (char*)malloc(prothead->len+20);
				len = read_datacache(mDatacache, mBuffer, prothead->len+20);
				result = ReturnCallback(mRecvEnv, mBuffer, len);
				free(mBuffer);
			}
			else
				break;
				
		}
	}
	else
	{
		result = (*mJavaVm)->AttachCurrentThread(mJavaVm, &mRecvEnv, NULL);  
		if(result < 0)  
		{  
			LOGE("AttachCurrentThread failed\n");
			return result;  
		}
		else
		{
			len = write_datacache(mDatacache, readbuff, len);
			LOGD("write_datacache result:%d\n", len);
			while(1)
			{
				if(get_datacache_size(mDatacache)<20)
					break;
				snifer_datacache(mDatacache, head, sizeof(head));
				HN_PROT_HEAD *prothead = (HN_PROT_HEAD *)head;

				if(prothead->len <= get_datacache_size(mDatacache)-20)
				{
					mBuffer = (char*)malloc(prothead->len+20);
					len = read_datacache(mDatacache, mBuffer, prothead->len+20);
					result = ReturnCallback(mRecvEnv, mBuffer, len);
					free(mBuffer);
				}
				else
					break;
			}
		}
	}

	return result;
}

int ReturnCallback(JNIEnv *env, char*stream, int iLen)
{
	jbyteArray strarray;
	jboolean okCopy;
	char* pVideoDataBuf;
	int result = -1;

	//result = (*mJavaVm)->GetEnv(mJavaVm, (void**) &mEnv, JNI_VERSION_1_6);
	if(env)
	{
		strarray = (*env)->NewByteArray(env, iLen);

		pVideoDataBuf = (char*)(*env)->GetByteArrayElements(env, strarray, &okCopy);
		memcpy(pVideoDataBuf, stream, iLen);

		if(mAnalyzeCidUtil)
			result = (*env)->CallStaticIntMethod(env, mAnalyzeCidUtil, mCallbackId, strarray);

		(*env)->ReleaseByteArrayElements(env, strarray, (jbyte*)pVideoDataBuf, 0);
		(*env)->DeleteLocalRef( env, strarray);
	}
	else
	{
		LOGE("GetEnv return NULL\n");
	}
	return result;
}


//---------------------------jni------------------------------------>
JNIEXPORT jint JNICALL JNI_API_NAME(createSdk)
(JNIEnv *pEnv, jclass cls)
{
	int result = -1;

	g_reactorid = result = create_reactor( );
	if(result<0)
		return result;

	result = registry_reactor_callback( g_reactorid, jcallback );

	//find java callback function
	mAnalyzeCidUtil = (*pEnv)->FindClass(pEnv, CALLBACK_CLASS_NAME);  
	//g_env = env;
	if (NULL == mAnalyzeCidUtil) 
	{  
		LOGE("NULL == mAnalyzeCidUtil");
		return -1;  
	}  

	//
	mCallbackId = (*pEnv)->GetStaticMethodID(pEnv, mAnalyzeCidUtil, "iocallback", "([B)I");  
	if (NULL == mCallbackId) 
	{  
		(*pEnv)->DeleteLocalRef(pEnv, mAnalyzeCidUtil); //
		LOGE("mCallbackId == NULL");
		return -2;  
	}

	mDatacache = (CDataCache *)malloc(sizeof(CDataCache));
	init_datacache(mDatacache, 10*READ_LENGHT);
	LOGD("createSdk successfuly...");

	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(destroySdk)
(JNIEnv *pEnv, jclass cls)
{
	int result = 0;
	result = destroySdk(); 
	if(mDatacache)
	{
		fini_datacache(mDatacache);
		free(mDatacache);
	}
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(createSession)
(JNIEnv *pEnv, jclass cls, jstring remoteIP, jint port)
{
	LPCTSTR pip = NULL;
	int32_t result = -1;
	jboolean isCopy;

	pip = (*pEnv)->GetStringUTFChars( pEnv, remoteIP, &isCopy );
	if ( pip )
	{
		result = creatSession( pip, port );
		(*pEnv)->ReleaseStringUTFChars( pEnv, remoteIP, pip );
	}
	LOGE("result:%d\n", result);
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(login)
(JNIEnv *pEnv, jclass cls, jint sessionId, jstring username, jstring password)
{
	LPCTSTR puser = NULL,pword = NULL;
	int32_t result = -1;
	jboolean isCopy;

	puser = (*pEnv)->GetStringUTFChars( pEnv, username, &isCopy );
	pword = (*pEnv)->GetStringUTFChars( pEnv, password, &isCopy );
	if ( puser&&pword )
	{
		result = login( sessionId, puser, pword );
		(*pEnv)->ReleaseStringUTFChars( pEnv, username, puser );
		(*pEnv)->ReleaseStringUTFChars( pEnv, password, pword );
	}
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(logout)
(JNIEnv *pEnv, jclass cls, jint sessionId )
{

	int32_t result = -1;
	result = logout( sessionId );
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(queryGroup)
(JNIEnv *pEnv, jclass cls, jint sessionId, jint pagesize, jint usrid)
{
	int32_t result = -1;
	result = queryGroup(sessionId, pagesize, usrid);
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(queryGroupLensList)
(JNIEnv *pEnv, jclass cls, jint sessionId, jstring usrid)
{
	int32_t result = -1;
	jboolean isCopy;
	LPCTSTR pusrid = NULL;
	pusrid = (*pEnv)->GetStringUTFChars( pEnv, usrid, &isCopy );
	
	if ( pusrid )
	{
		result = getLensGroupInfoList(sessionId, pusrid);
		(*pEnv)->ReleaseStringUTFChars( pEnv, usrid, pusrid );
	}
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(queryLensInfoList)
(JNIEnv *pEnv, jclass cls, jint sessionId, jstring grpid)
{
	int32_t result = -1;
	jboolean isCopy;
	LPCTSTR pgrpid = NULL;
	pgrpid = (*pEnv)->GetStringUTFChars( pEnv, grpid, &isCopy );
	
	if ( pgrpid )
	{
		result = getLensInfoList(sessionId, pgrpid);
		(*pEnv)->ReleaseStringUTFChars( pEnv, grpid, pgrpid );
	}
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(queryDeviceList)
(JNIEnv *pEnv, jclass cls, jint sessionId, jint pagesize, jint groupid )
{
	int32_t result = -1;
	result = queryDeviceList(sessionId, pagesize, groupid);
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(queryDeviceOnline)
(JNIEnv *pEnv, jclass cls, jint sessionId, jint usrid)
{
	int32_t result = -1;
	result = queryDeviceOnline(sessionId, usrid);
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(sendKeepAlive)
(JNIEnv *pEnv, jclass cls, jint sessionId, jint usrid)
{
	int32_t result = -1;
	result = sendKeepAlive(sessionId);
	return result;
}

JNIEXPORT jint JNICALL JNI_API_NAME(changePassWord)
(JNIEnv *pEnv, jclass cls, jint sessionId, jint usrid, jstring username, jstring oldpass, jstring newpass)
{
	LPCTSTR puser = NULL,poldword = NULL,pnewword = NULL;
	int32_t result = -1;
	jboolean isCopy;

	puser = (*pEnv)->GetStringUTFChars( pEnv, username, &isCopy );
	poldword = (*pEnv)->GetStringUTFChars( pEnv, oldpass, &isCopy );
	pnewword = (*pEnv)->GetStringUTFChars( pEnv, newpass, &isCopy );

	if ( puser && poldword && pnewword )
	{
		result = changePassWord( sessionId, usrid, puser, poldword, pnewword);
		(*pEnv)->ReleaseStringUTFChars( pEnv, username, puser );
		(*pEnv)->ReleaseStringUTFChars( pEnv, oldpass, poldword );
		(*pEnv)->ReleaseStringUTFChars( pEnv, newpass, pnewword );
	}
	return result;
}

JNIEXPORT jstring JNICALL JNI_API_NAME(getMd5Data)
(JNIEnv *pEnv, jclass cls, jstring md5data)
{
	LPCTSTR pmd5 = NULL;
	jboolean isCopy;
	char resmd5[36] = {0};
	if(md5data == NULL)
		return NULL;
	pmd5 = (*pEnv)->GetStringUTFChars( pEnv, md5data, &isCopy );
	if ( pmd5 )
	{
		if(HnMD5Data ((const unsigned char *)pmd5, strlen(pmd5), resmd5, sizeof(resmd5))<0)
		{
			(*pEnv)->ReleaseStringUTFChars( pEnv, md5data, pmd5 );
			return NULL;
		}
		(*pEnv)->ReleaseStringUTFChars( pEnv, md5data, pmd5 );
	}
	return (*pEnv)->NewStringUTF(pEnv,resmd5);
}
