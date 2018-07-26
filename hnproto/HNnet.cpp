// HNnet.cpp : 定义控制台应用程序的入口点。
//
#include <stdlib.h>
#include <stdio.h>
#include <net_api.h>
#include <typedefs.h>

#include <HnComn.h>
#include <HnMd5.h>

#include "HNnetApi.h"

int gSessionid;


HN_SERVER serverinfo = {0};
HN_USER userinfo = {0};
HN_DEVGRP_PAGE resgroup = {0};
HN_DEVICE_PAGE devicepage = {0};
HN_DEVLIVE_PAGE devicelive = {0};

int32_t callback_t( int32_t iReactorId, int32_t iSocketId, int32_t iEvent )
{
	
	int8u_t buffer[4096] = {0};
	int iLen = net_recv(iSocketId, buffer, 4096);
	
	if(iLen<=0)
	{
		//int iRes = remove_reactor_socket(iReactorId, iSocketId);
		//printf("=======remove_reactor_socket======%d\n", iRes);
		return 0;
	}

	printf("=======callback_t======iSocketId:%d\n", iSocketId);
	printf("=======net_recv======%d\n", iLen);

	if(iLen>0)
		printf("%s\n", buffer);

	HN_PROT_HEAD *prothead = (HN_PROT_HEAD *)buffer;
	printf("=======destine cmd======%d\n", prothead->cmd);


	switch(prothead->cmd)
	{
		case CMD_LOGIN:
			//serverinfo = (HN_SERVER *)(buffer+sizeof(HN_PROT_HEAD) );
			memcpy(&serverinfo, buffer+sizeof(HN_PROT_HEAD), sizeof(HN_SERVER));
			memcpy(&userinfo, buffer+sizeof(HN_PROT_HEAD)+ sizeof(HN_SERVER), sizeof(HN_USER));
			//userinfo = (HN_USER *)(buffer+sizeof(HN_PROT_HEAD)+ sizeof(HN_SERVER));
			break;

		case CMD_GET_DEVICE_GROUP:
			//resgroup = (HN_DEVGRP *)(buffer+sizeof(HN_PROT_HEAD));
			memcpy(&resgroup, buffer+sizeof(HN_PROT_HEAD), sizeof(HN_DEVGRP_PAGE));
			break;

		case CMD_GET_DEVICE_LIST:
			memcpy(&devicepage, buffer+sizeof(HN_PROT_HEAD), sizeof(HN_DEVICE_PAGE));
			break;

		case CMD_GET_DEVICE_ONLINE:
			memcpy(&devicelive, buffer+sizeof(HN_PROT_HEAD), sizeof(HN_DEVLIVE_PAGE));
			break;

		case HNCMDUSRM_PSNPWDM:
			printf("..");
			break;

		default:
			break;
	}


	return 0;
}

const char*ipadd = "192.168.8.65";
int port = 8000;
const char*username = "tt2";
const char*password = "2";

int main(int argc, char* argv[])
{
	int32_t iResult = -1;

	iResult = createSdk(callback_t);
	printf("=======createSdk======:%d\n", iResult);

	iResult = gSessionid = creatSession(ipadd, port);//58.251.161.159  192.168.8.65
	printf("=======creatSession======:%d\n", iResult);
	

	iResult = login(gSessionid, (char*)username, (char*)password);
	printf("=======login======:%d\n", iResult);
	getchar();

	iResult = queryGroup(gSessionid, HNGRPPAGE_MAX_SIZE, userinfo.usrid);
	printf("=======queryGroup======:%d\n", iResult);
	getchar();

	iResult = queryDeviceList(gSessionid, HNGRPPAGE_MAX_SIZE, resgroup.item[0].grpid);
	printf("=======queryDeviceList======:%d\n", iResult);
	getchar();

	iResult = queryDeviceOnline(gSessionid, userinfo.usrid);
	printf("=======queryDeviceLive======:%d\n", iResult);
	getchar();

	while(1)
	{
		Sleep(10000);
		iResult = sendKeepAlive(gSessionid);
		printf("=======sendKeepAlive======:%d\n", iResult);
	}

	iResult = changePassWord(gSessionid, userinfo.usrid, (char*)username, (char*)password, "2");
	printf("=======changePassWord======:%d\n", iResult);
	getchar();

	iResult = logout(gSessionid, (char*)username, (char*)password);
	printf("=======logout======:%d\n", iResult);

	iResult = destroySdk();
	printf("=======destroySdk======:%d\n", iResult);

	getchar();
	return 0;
}


/*
int gReactorFd;
int gServerFd;
int gClientFd;

int8u_t buffer[2048] = {0};
char request[1024] = {0};




int32_t callback_t( int32_t iReactorId, int32_t iSocketId, int32_t iEvent )
{
printf("=======callback_t======iSocketId:%d\n", iSocketId);
if(iSocketId == gServerFd)
{
printf("=======accept socket======%d\n", iSocketId);
}
int iLen = net_recv(iSocketId, buffer, 2048);
printf("=======net_recv======%d\n", iLen);
if(iLen<=0)
{
int iRes = remove_reactor_socket(iReactorId, iSocketId);
printf("=======remove_reactor_socket======%d\n", iRes);
}


if(iLen>0)
printf("%s\n", buffer);
return 0;
}

	sprintf(request, "GET /%s HTTP/1.1\r\n\
					 Host: %s:%d\r\n\
					 User-Agent: Mozilla/5.0 (X11; Linux i686; rv:2.0) Gecko/20100101 Firefox/4.0\r\n\
					 Accept: text/html,application/xhtml+xml,application/xml;q=0.9,;q=0.8\r\n\
					 Accept-Language: en-us,en;q=0.5\r\n\
					 Accept-Encoding: gzip, deflate\r\n\
					 Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n\
					 Keep-Alive: 115\r\n\
					 Connection: keep-alive", "", "www.baidu.com", 80);

	gReactorFd = iResult =  create_reactor( );
	printf("======create_reactor=======%d\n", iResult);
	iResult = registry_reactor_callback( gReactorFd, callback_t );
	printf("=======registry_reactor_callback======%d\n", iResult);

	//gServerFd = create_socket( "", 81, "", 0,  SOCKET_SERVER_TCP);
	//printf("=====create_socket server========%d\n", gServerFd);
	//iResult = add_reactor_socket(gReactorFd, gServerFd);
	//printf("=======add_reactor_socket======%d\n", iResult);
	//58.251.161.159 192.168.171.150 111.13.100.92
	gClientFd= create_socket( "58.251.161.159", 8000, "", 0,  SOCKET_CLIENT_TCP);//58.251.161.159
	printf("=====create_socket client========%d\n", gClientFd);

	HN_CMDBUF cmdbuf= {0};
	HN_NETMSG *msg = (HN_NETMSG*)&cmdbuf.buf;
	HN_PROT_HEAD &prothead = msg->head;
	memcpy(&prothead.head, PROTOCOL_HEAD, strlen(PROTOCOL_HEAD));
	prothead.vers1 = 0x01;
    prothead.vers2 = 0x01;
	prothead.cmd = 0x0201;
	prothead.ssrc = gClientFd;
	prothead.len = 80;

	HN_USER *user = (HN_USER*)msg->buf;
	strcpy(user->name, "test");
	strcpy(user->pswd, "1");
 
	int buflen = sizeof(user->pswd);
	if(HnMD5Data ((const unsigned char *)user->pswd, strlen(user->pswd), user->pswd, buflen))
		printf("md5 successful!\n");

	iResult = net_send( gClientFd, (int8u_t *)cmdbuf.buf, 100 );
	printf("=====net_send========%d\n", iResult);

	iResult = add_reactor_socket(gReactorFd, gClientFd);
	printf("=====add_reactor_socket========%d\n", iResult);


	close_socket(gServerFd);
	close_socket(gClientFd);
	close_socket(gReactorFd);
*/