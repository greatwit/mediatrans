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

#include "HNnetApi.h"
#include <HnMd5.h>
#include <log.h>
#include <HnProto.h>
#include <net_api.h>
#include <datacache.h>

#include <AnBCmdCode.h>

int g_reactorid;
CDataCache *mDatacache = NULL;
char *mBuffer = NULL;
int8u_t readbuff[4096] = {0};
#define READ_LENGHT sizeof(readbuff)
stream_callback_t gStreamCallback;

int32_t protoCallback( int32_t iReactorId, int32_t iSocketId, int32_t iEvent )
{
    
    int result = -1;
	int len =0;
	char head[20] = {0};
	
	if(iSocketId==0xff)
	{
		return result;
	}
    
	len = net_recv(iSocketId, readbuff, READ_LENGHT);
	LOGE("receive data length:%d\n", len);
	if(len<0)
		return result;
    

    write_datacache(mDatacache, readbuff, len);
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
            result = gStreamCallback(mBuffer, len);
            free(mBuffer);
        }
        else
            break;
    }

    
	return result;
}

int32_t createSdk(stream_callback_t streamcallback)
{
	int result = -1;

	g_reactorid = result = create_reactor( );
	if(result<0)
		return result;

	result = registry_reactor_callback( g_reactorid, protoCallback );
    gStreamCallback = streamcallback;
    mDatacache = (CDataCache *)malloc(sizeof(CDataCache));
	init_datacache(mDatacache, 10*READ_LENGHT);
    
	return result;
}

int32_t destroySdk()
{
	int result = -1;

	result = destory_reactor(g_reactorid);
	if(mDatacache)
	{
		fini_datacache(mDatacache);
		free(mDatacache);
	}
	return result;
}

int32_t creatSession( const char *pRemoteIP, int16u_t remotePort )
{
	int result = -1;
	if(pRemoteIP==NULL || remotePort <=0)
		return result;

	result = create_socket( pRemoteIP, remotePort, "", 0,  SOCKET_CLIENT_TCP);
	add_reactor_socket(g_reactorid, result);
	return result;
}

int32_t login( int32_t sessionId, char *username, char *password )
{
	int result = -1;
    
	ANB_LOGINMSG *pLogin = NULL;
	HN_CMDBUF cmdbuf = {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;
    
	if(username==NULL || password==NULL)
		return result;
    
	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = ANB_CMD_CENTER_LOGIN_REQ;
	prothead->ssrc = sessionId;
	prothead->dstid= 0;
	prothead->len = sizeof(ANB_LOGINMSG);
    
	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;
    
	pLogin = (ANB_LOGINMSG*)msg->buf;
	pLogin->nType = ANB_CLIENT;
	strcpy(pLogin->szUserName, username);
	strcpy(pLogin->szPassword, password);
    
	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
    
	return result;
}


int32_t logout( int32_t sessionId )
{
    int result = -1;
    
	HN_CMDBUF cmdbuf = {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;
    
    
	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = ANB_CMD_CENTER_LOGOUT_REQ;
	prothead->ssrc = sessionId;
	prothead->dstid= 0;
	prothead->len = 0;
    
	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

    
	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	
	result = remove_reactor_socket(g_reactorid, sessionId);
	LOGD("remove_reactor_socket=================%d\n",result);
	result = close_socket(sessionId);
	LOGD("close_socket=================%d\n",result);
    
	return result;
}

int32_t getLensGroupInfoList(int32_t sessionId, const char*pUserId)
{
    int result = -1;
    
	ANB_GetLensGroupListReq *pLensGroupReq = NULL;
	HN_CMDBUF cmdbuf = {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;
    
	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = ANB_CMD_CENTER_GET_LENS_GROUP_LIST_REQ;
	prothead->ssrc  = sessionId;
	prothead->dstid = 0;
	prothead->len = sizeof(ANB_GetLensGroupListReq);
    
	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;
    
	pLensGroupReq = (ANB_GetLensGroupListReq*)msg->buf;
    
	memset(pLensGroupReq->szUserID, 0x0, sizeof(pLensGroupReq->szUserID));
	strncpy(pLensGroupReq->szUserID, pUserId, ANB_ID_LEN);
    
    
	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	//result = add_reactor_socket(g_reactorid, sessionId);
    
	return result;
}

int32_t getLensInfoList(int32_t sessionId, const char*pLensGroupId)
{
    int result = -1;
    
	ANB_GetLensListReq *pReq = NULL;
	HN_CMDBUF cmdbuf = {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;
    
	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = ANB_CMD_CENTER_GET_LENS_LIST_REQ;
	prothead->ssrc  = sessionId;
	prothead->dstid = 0;
	prothead->len = sizeof(ANB_GetLensListReq);
    
	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;
    
	pReq = (ANB_GetLensListReq*)msg->buf;
    
	memset(pReq->szLensGroupID, 0x0, sizeof(pReq->szLensGroupID));
	strncpy(pReq->szLensGroupID, pLensGroupId, ANB_ID_LEN);
    
    
	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	//result = add_reactor_socket(g_reactorid, sessionId);
    
	return result;
}

int32_t queryGroup(int32_t sessionId, int pagesize, int usrid)
{
	int result = -1;

	HN_DEVGRP_QUERY *query = NULL;
	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;

	if(pagesize<=0 || usrid <=0)
		return result;

	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = CMD_GET_DEVICE_GROUP;
	prothead->ssrc = sessionId;
	prothead->dstid= 0;
	prothead->len = sizeof(HN_DEVGRP_QUERY);

	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

	query = (HN_DEVGRP_QUERY*)msg->buf;
	query->pageno = 1;
	query->pagesize = pagesize;
	query->parent = 0;
	query->usrid  = usrid;

	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	printf("queryGroup send lenght:%d\n", result);

	//result = add_reactor_socket(g_reactorid, sessionId);

	return result;
}

int32_t queryDeviceList( int32_t sessionId, int pagesize, int groupid )
{
	int result = -1;
	HN_DEVICE_QUERY *query = NULL;
	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;

	if(pagesize<=0)
		return result;

	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = CMD_GET_DEVICE_LIST;
	prothead->ssrc = sessionId;
	prothead->dstid= 0;
	prothead->len = sizeof(HN_DEVICE_QUERY);

	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

	query = (HN_DEVICE_QUERY*)msg->buf;
	query->pageno = 1;
	query->pagesize = pagesize;
	query->grpid  = groupid;

	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	printf("query device list send lenght:%d\n", result);

	return result;
}

int32_t queryDeviceOnline( int32_t sessionId, int usrid)
{
	int result = -1;
	//HN_DEVICE_QUERY *query = NULL;
	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;

	if(usrid<=0)
		return result;

	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = CMD_GET_DEVICE_ONLINE;
	prothead->ssrc = sessionId;
	prothead->dstid = 0;
	prothead->len = 0;

	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	printf("==============query device live send lenght:%d\n", result);

	return result;
}

int32_t sendKeepAlive( int32_t sessionId)
{
	int result = -1;
	//HN_DEVICE_QUERY *query = NULL;
	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;

	if(sessionId<=0)
		return result;

	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = HNCMDUSRM_ALIVE;
	prothead->ssrc = sessionId;
	prothead->dstid = 0;
	prothead->len = 0;

	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	printf("==============sendKeepAlive send lenght:%d\n", result);

	return result;
}

DEV_SDK_API int32_t sendPtzControl( int32_t sessionId, const char*pLendId, int commond)
{
    int result = -1;
    HN_CMDBUF cmdbuf= {0};
    HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
    HN_PROT_HEAD *prothead = &msg->head;
    
    memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
    prothead->vers1 = VERSION_01;
    prothead->vers2 = VERSION_02;
    prothead->cmd = CMD_PTZ_REQUEST;
    prothead->ssrc = sessionId;
    prothead->dstid= 0;
    prothead->len = sizeof(ANB_PTZCONTROL_INFO);
    
    cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;
    
    ANB_PTZCONTROL_INFO *query = NULL;
    query = (ANB_PTZCONTROL_INFO*)msg->buf;
    strcpy(query->lensID.szLensID, pLendId);
    
    query->PTZCtrlPara.dwPTZCommand = commond;
    query->PTZCtrlPara.dwSpeed      = 60;
    
    result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
    printf("------------------ptz commond send result:%d\n", result);
    
    return result;
}


int32_t changePassWord( int32_t sessionId, int usrid, char *username, char *oldpass, char* newpass)
{
	int result = -1;

	HN_USR_PWDM *password = NULL;
	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD *prothead = &msg->head;

	if(username==NULL||oldpass==NULL||newpass==NULL)
	{
		return result;
	}

	memcpy(prothead->head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead->vers1 = VERSION_01;
	prothead->vers2 = VERSION_02;
	prothead->cmd = HNCMDUSRM_PSNPWDM;
	prothead->ssrc = sessionId;
	prothead->dstid= 0;
	prothead->len = sizeof(HN_USR_PWDM);
	
	cmdbuf.len = sizeof(HN_PROT_HEAD) + prothead->len;

	password = (HN_USR_PWDM*)msg->buf;
	password->usrid = usrid;
	strcpy(password->name, username);
	strcpy(password->oldpwd, oldpass);
	strcpy(password->newpwd, newpass);

	if(HnMD5Data ((const unsigned char *)password->oldpwd, strlen(password->oldpwd), 
		password->oldpwd, sizeof(password->oldpwd))<0)
	{
		return OP_FAILURE;
	}
	if(HnMD5Data ((const unsigned char *)password->newpwd, strlen(password->newpwd), 
		password->newpwd, sizeof(password->newpwd))<0)
	{
		return OP_FAILURE;
	}

	result = net_send( sessionId, (int8u_t *)cmdbuf.buf, cmdbuf.len );
	printf("change password send lenght:%d\n", result);

	return result;
}