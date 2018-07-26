#ifndef HNPROT_H_H_H_H_H_H
#define HNPROT_H_H_H_H_H_H

#include "typedefs.h"

#define HNPROT_DATA_LEN			4096

#define PROTOCOL_HEAD           "$AB$" 

#define VERSION_01              0x01
#define VERSION_02              0x01

//commond
#define CMD_LOGIN               0x0201
#define CMD_LOGOUT              0x0202
#define CMD_GET_DEVICE_GROUP    0x0107
#define CMD_GET_DEVICE_LIST     0x0103
#define CMD_GET_DEVICE_ONLINE   0x010c
#define CMD_PTZ_CONTROL         0x0609

#define CMD_PTZ_REQUEST         0x3005

//��ѯ
#define HNGRPPAGE_MAX_SIZE		20
#define HNDEVPAGE_MAX_SIZE		20
#define HNLOGPAGE_MAX_SIZE		20
#define HNDEVPAGE_MAX_LIVE		200
#define NAME_COL_LEN            32
#define NOTE_COL_LEN            128

//�û��������
enum HnCmdUsrM
{
	HNCMDUSRM_BASE = 0x0200,
	HNCMDUSRM_LOGIN,
	HNCMDUSRM_LOGOUT,       //�û�ע��
	HNCMDUSRM_ALIVE,
	HNCMDUSRM_USRAUTH,		//��ȡ�û�Ȩ��
	HNCMDUSRM_USRLIST,		//��ȡ��ǰ�û��µ��û��б�
	HNCMDUSRM_USRADD,		//�ڵ�ǰ�û�������µ��û�
	HNCMDUSRM_USRMOD,		//�ڵ�ǰ�û����޸��û�
	HNCMDUSRM_USRINFO,		//�ڵ�ǰ�û����޸��û�ǰ����ȡ���޸��û�����Ϣ(�����޸ĸ��˻�����Ϣǰ��ȡ��Ϣ)
	HNCMDUSRM_USRDEL,		//�ڵ�ǰ�û���ɾ���û�
	HNCMDUSRM_SLFMOD,       //user�û��޸��Լ����û�������Ϣ����ϵ��ʽ�ȣ�
	HNCMDUSRM_SYSMNT,       //ϵͳά��
    
	HNCMDUSRM_QRYUSRLOG,    //��ѯ�û�������־
	HNCMDUSRM_QRYSYSLOG,    //��ѯϵͳά����־
	HNCMDUSRM_QRYALMLOG,    //��ѯ������־
	HNCMDUSRM_PSNPWDM,      //�û��޸ĸ�������
	HNCMDUSRM_TMOUTLOGOUT,  //��ʱע��
	HNCMDUSRM_USRALAMPHONEINFO,/* ��ȡ�û�����������Ϣ */
	HNCMDUSRM_USRALAMPHONEINFOSET,/* �����û�����������Ϣ */
    
	HNCMDDXM_AMETWARNGET,           //���Ԥ��ֵ��ȡ
	HNCMDDXM_AMETWARNSET,           //���Ԥ��ֵ����
	HNCMDDXM_AMETMESGET,            //���Ԥ��֪ͨ��ȡ
	HNCMDDXM_AMETMESSET,            //���Ԥ��֪ͨ����
	HNCMDDXM_AMETSTATINFO,          //��ȡ���ͳ����Ϣ
	HNCMDDXM_QRYBATTLOG,            //��ѯ�����־��Ϣ
	HNCMDDXM_QRYBATTGRPLOG,         //��ѯ�������־��Ϣ
	HNCMDDXM_QRYBATTCELLOG,         //��ѯ��������־��Ϣ
	HNCMDDXM_QRYAMETLOG,            //��ѯ�������־��Ϣ
	HNCMDDXM_QRYAMETWALOG,          //��ѯ���Ԥ����־��Ϣ
	HNCMDDXM_QRYACDNLOG,            //��ѯ�յ���־��Ϣ
	HNCMDDXM_QRYGPSLOG,             //��ѯgps��־��Ϣ
	HNCMDDXM_QRYGPSLASTINFO,        //��ѯgps���һ����Ϣ
	HNCMDDXM_QRYDXAILOG,            //��ѯģ������־��Ϣ
	HNCMDDXM_QRYDXDILOG,            //��ѯ��������־��Ϣ
	HNCMDDXM_QRYACDNLINEDATA,       //��ѯ�յ�ʵʱ��������Ҫ������
	HNCMDDXM_QRYBATTGRPLINEDATA,    //��ѯ������ʵʱ��������Ҫ������
	HNCMDDXM_QRYBATTCELLLINEDATA,   //��ѯ���ص���ʵʱ��������Ҫ������
	HNCMDDXM_QRYAMETLINEDATA,       //��ѯ���ʵʱ��������Ҫ������
	HNCMDDXM_QRYAILINEDATA,         //��ѯģ����ʵʱ��������Ҫ������
	HNCMDDXM_QRYAMETLIVELOG,        //��ѯ�����ʷ��־��Ϣ
	HNCMDUSRM_CHECKUSRLOGIN,        //����Ž��û����ε�½�û���Ϣ
	HNCMDDXM_QRYAMETPOWERBYHOURS,    //��һ(��)���ڵĺĵ���
};

enum HnPtzOper
{
	HNPTZOPER_NONE		= -1,//�ղ���
	HNPTZOPER_LEFTUP,		//����
	HNPTZOPER_UP,			//��
	HNPTZOPER_RIGHTUP,		//����
	HNPTZOPER_LEFT,			//��
	HNPTZOPER_RIGHT,		//��
	HNPTZOPER_LEFTDOWN,		//����
	HNPTZOPER_DOWN,			//��
	HNPTZOPER_RIGHTDOWN,	//����
	HNPTZOPER_ZOOMWIDE,		//��ͷ�Ŵ�
	HNPTZOPER_ZOOMTELE,		//��ͷ����
	HNPTZOPER_FOCUSFAR,		//Զ�۽�
	HNPTZOPER_FOCUSNEAR,	//���۽�
	HNPTZOPER_IRISLARGE,	//��Ȧ����
	HNPTZOPER_IRISSMALL,	//��Ȧ��С
	HNPTZOPER_ACTSTOP,		//����ֹͣ
	HNPTZOPER_ALMSEARCH, //alarm search
	HNPTZOPER_LIGHTON,	//�ƹ��
	HNPTZOPER_LIGHTOFF,	//�ƹ�ر�
	HNPTZOPER_SETPRESET,	//����Ԥ�õ�
	HNPTZOPER_CLEARPRESET,//���Ԥ�õ�
	HNPTZOPER_GOTOPRESET, //�˶���Ԥ�õ�
	HNPTZOPER_AUTOPANON, //�Զ�Pan��
	HNPTZOPER_AUTOPANOFF, //�Զ�Pan�ر�
	HNPTZOPER_SETLEFTLIMIT, //��������
	HNPTZOPER_SETRIGHTLIMIT, //�����Ҽ���
	HNPTZOPER_AUTOSCANON, //�Զ�ɨ���
	HNPTZOPER_AUTOSCANOFF, //�Զ�ɨ��ر�
	HNPTZOPER_ADDTOUR, //����Զ�Ѳ��
	HNPTZOPER_DELTOUR, //ɾ���Զ�Ѳ��
	HNPTZOPER_STARTTOUR, //�����Զ�Ѳ��
	HNPTZOPER_STOPTOUR, //�ر��Զ�Ѳ��
	HNPTZOPER_CLEARTOUR, //����Զ�Ѳ��
	HNPTZOPER_SETPATTERNBEGIN, //����ģʽ��ʼ
	HNPTZOPER_SETPATTERNEND, //����ģʽ����
	HNPTZOPER_STARTPATTERN, //��ʼģʽ
	HNPTZOPER_STOPPATTERN, //ֹͣģʽ
	HNPTZOPER_CLEARPATTERN, //���ģʽ
	HNPTZOPER_POSITION, //���ٶ�λ
	HNPTZOPER_AUXON, //�������ܴ�
	HNPTZOPER_AUXOFF, //�������عر�
	HNPTZOPER_MENU, //����˵�
	HNPTZOPER_EXIT, //�˳�����˵�
	HNPTZOPER_ENTER, //ȷ��
	HNPTZOPER_ESC, //ȡ��
	HNPTZOPER_MENUUP, //�˵����²���
	HNPTZOPER_MENUDOWN, //�˵����²���
	HNPTZOPER_MENULEFT, //�˵����Ҳ���
	HNPTZOPER_MENURIGHT, //�˵����Ҳ���
	HNPTZOPER_TWOPOINTSCAN, //����ɨ��
};


typedef enum HNDSTID
{
	DSTID_LOGIN = 81,
	DSTID_QUERY_GROUP,
	DSTID_QUERY_DEVLIST,
	DSTID_QUERY_LIVE
}
HNDSTID;

typedef struct _hn_prot_head
{
	BYTE	head[4];	//$AB$
	BYTE	vers1;		//���汾��
	BYTE	vers2;		//�ΰ汾��
	WORD	cmd;		//����ָ��
	DWORD	ssrc;		//�Ự��
	DWORD	dstid;		//Ŀ��ID
	short	code;		//������
	WORD	len;		//���ݳ���
	
}HN_PROT_HEAD;

typedef struct _hn_netmsg
{
	HN_PROT_HEAD	head;
	char			buf[HNPROT_DATA_LEN];
}HN_NETMSG;

typedef struct _hn_cmdbuf
{
	int			len;
	char		buf[6*1024];
}HN_CMDBUF;

//�û���Ϣ�ṹ��
typedef struct _hn_user
{
	int			usrid;			//�û�ID
	char		name[32];	   	//�û���
	char		pswd[36];	   	//����
	char		grpnm[8];       //�û�������
}HN_USER;


//��������Ϣ
typedef struct _hnserver
{
	char		url[32];	//������ip��ַ
	char		usr[32];	//��������½�û�����Ŀǰ��Ч
	char		pwd[32];	//��������½���룬Ŀǰ��Ч
	WORD	port;		//�������˿�
	char		reser[6];	//����
}HNSERVER;

//ϵͳ��������Ϣ
typedef struct _hn_server
{
	HNSERVER	alarmsrv;
	HNSERVER	mediasrv;
	HNSERVER  recrdsrv;
}HN_SERVER;


//�豸�������Ϣ
typedef struct _hn_devgrp
{
	int		grpid;                      //�豸����
	int		parent;						//�豸��������ԱID
	int		usrid;						//�豸���������û�ID��δ����Ϊ0
	char		grpnm[NAME_COL_LEN];     //�豸������
	char		note[NOTE_COL_LEN];       //��ע
}HN_DEVGRP; //sizeof 172

//�豸���ѯ������Ϣ
typedef struct _hn_devgrp_query
{
	int		pageno;					//ҳ��
	int		pagesize;					//ҳ��С
	int		parent;					//�豸��������ԱID
	int		usrid;					//�豸���������û�ID��δ����Ϊ0
}HN_DEVGRP_QUERY;

//�豸���ѯ��ҳ��Ϣ
typedef struct _hn_devgrp_page
{
	int			allpage;				//��ҳ��
	int			pageno;				//��ǰ��ѯ��ҳ��
	int			itemnum;				//��ǰҳ������
	HN_DEVGRP	item[HNGRPPAGE_MAX_SIZE];//��ǰҳ�ķ�����Ϣ
}HN_DEVGRP_PAGE;

//�豸������Ϣ
typedef struct _hn_device
{
	int			devid;					//�豸�߼�id�����ݿ������(�豸���)
	int			manufactid;				//�豸���̱��
	int			serialid;					//�豸����id
	int			grpid;					//�豸����
	char			name[NAME_COL_LEN];	//�豸����
	char			user[32];					//�û���
	char			pswd[32];				//��������
	char			note[48];					//��ע
	char			type;                    //�豸����,dvs,ipcam��
	char			chan;                    //��Ƶ����Ƶͨ����
	char			aicount;                  //��������·��
	char			status;					//�豸״̬
	int         creatorid;					//������id
}HN_DEVICE;  //sizeof 168

//�豸�б��ѯ������Ϣ
typedef struct _hn_device_query
{
	int			pageno;					//ҳ��
	int			pagesize;					//ҳ��С
	int			grpid;					//�豸��������ID
}HN_DEVICE_QUERY;

//�豸�б��ѯ��ҳ��Ϣ
typedef struct _hn_device_page
{
	int			allpage;				//��ҳ��
	int			pageno;				//��ǰ��ѯ��ҳ��
	int			itemnum;				//��ǰҳ������
	HN_DEVICE	item[HNDEVPAGE_MAX_SIZE];//��ǰҳ�ķ�����Ϣ
}HN_DEVICE_PAGE;

//�����豸��Ϣ
typedef struct _hn_devlive
{
	int			devid;					//�豸�߼�id�����ݿ������(�豸���)
	int      	usrid;                 	//�û�Id
	char			type;                 	//�豸����,dvs,ipcam��
	char			chan;                   	//��Ƶ����Ƶͨ����
	char			aicount;              	//��������·��
	char			status;					//�豸״̬
	int			incid;					//�豸���̱��
}HN_DEVLIVE; //sizeof 16

//�����豸��ѯ��Ϣ
typedef struct _hn_devlive_page
{
	int				allpage;				//��ҳ��
	int				pageno;				//��ǰ��ѯ��ҳ��
	int				itemnum;				//��ǰҳ������
	HN_DEVLIVE	item[HNDEVPAGE_MAX_LIVE];//��ǰҳ�ķ�����Ϣ
}HN_DEVLIVE_PAGE;


//�޸�����
typedef struct _hn_usr_pwdm
{
	int     usrid;
	char    name[32];
	char    oldpwd[36];
	char    newpwd[36];
}HN_USR_PWDM;


//��̨������Ϣ
typedef struct _hn_dev_ptzctl
{
	int			chan;			//��̨����ͨ��
	int			ptzcmd;			//��̨����ָ��
	int			param;			//��̨���Ʋ���
	char		protocol[28];		//��̨Э�飬Ŀǰ��Ч
}HN_DEV_PTZCTL;


#endif
