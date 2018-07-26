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

//查询
#define HNGRPPAGE_MAX_SIZE		20
#define HNDEVPAGE_MAX_SIZE		20
#define HNLOGPAGE_MAX_SIZE		20
#define HNDEVPAGE_MAX_LIVE		200
#define NAME_COL_LEN            32
#define NOTE_COL_LEN            128

//用户管理操作
enum HnCmdUsrM
{
	HNCMDUSRM_BASE = 0x0200,
	HNCMDUSRM_LOGIN,
	HNCMDUSRM_LOGOUT,       //用户注销
	HNCMDUSRM_ALIVE,
	HNCMDUSRM_USRAUTH,		//获取用户权限
	HNCMDUSRM_USRLIST,		//获取当前用户下的用户列表
	HNCMDUSRM_USRADD,		//在当前用户下添加新的用户
	HNCMDUSRM_USRMOD,		//在当前用户下修改用户
	HNCMDUSRM_USRINFO,		//在当前用户下修改用户前，获取待修改用户的信息(包括修改个人基本信息前获取信息)
	HNCMDUSRM_USRDEL,		//在当前用户下删除用户
	HNCMDUSRM_SLFMOD,       //user用户修改自己的用户基本信息（联系方式等）
	HNCMDUSRM_SYSMNT,       //系统维护
    
	HNCMDUSRM_QRYUSRLOG,    //查询用户操作日志
	HNCMDUSRM_QRYSYSLOG,    //查询系统维护日志
	HNCMDUSRM_QRYALMLOG,    //查询报警日志
	HNCMDUSRM_PSNPWDM,      //用户修改个人密码
	HNCMDUSRM_TMOUTLOGOUT,  //超时注销
	HNCMDUSRM_USRALAMPHONEINFO,/* 获取用户报警配置信息 */
	HNCMDUSRM_USRALAMPHONEINFOSET,/* 设置用户报警配置信息 */
    
	HNCMDDXM_AMETWARNGET,           //电表预警值获取
	HNCMDDXM_AMETWARNSET,           //电表预警值设置
	HNCMDDXM_AMETMESGET,            //电表预警通知获取
	HNCMDDXM_AMETMESSET,            //电表预警通知设置
	HNCMDDXM_AMETSTATINFO,          //获取电表统计信息
	HNCMDDXM_QRYBATTLOG,            //查询电池日志信息
	HNCMDDXM_QRYBATTGRPLOG,         //查询电池组日志信息
	HNCMDDXM_QRYBATTCELLOG,         //查询单体电池日志信息
	HNCMDDXM_QRYAMETLOG,            //查询电表抄表日志信息
	HNCMDDXM_QRYAMETWALOG,          //查询电表预警日志信息
	HNCMDDXM_QRYACDNLOG,            //查询空调日志信息
	HNCMDDXM_QRYGPSLOG,             //查询gps日志信息
	HNCMDDXM_QRYGPSLASTINFO,        //查询gps最后一条信息
	HNCMDDXM_QRYDXAILOG,            //查询模拟量日志信息
	HNCMDDXM_QRYDXDILOG,            //查询数字量日志信息
	HNCMDDXM_QRYACDNLINEDATA,       //查询空调实时曲线所需要的数据
	HNCMDDXM_QRYBATTGRPLINEDATA,    //查询蓄电池组实时曲线所需要的数据
	HNCMDDXM_QRYBATTCELLLINEDATA,   //查询蓄电池单体实时曲线所需要的数据
	HNCMDDXM_QRYAMETLINEDATA,       //查询电表实时曲线所需要的数据
	HNCMDDXM_QRYAILINEDATA,         //查询模拟量实时曲线所需要的数据
	HNCMDDXM_QRYAMETLIVELOG,        //查询电表历史日志信息
	HNCMDUSRM_CHECKUSRLOGIN,        //检查门禁用户二次登陆用户信息
	HNCMDDXM_QRYAMETPOWERBYHOURS,    //查一(七)天内的耗电量
};

enum HnPtzOper
{
	HNPTZOPER_NONE		= -1,//空操作
	HNPTZOPER_LEFTUP,		//左上
	HNPTZOPER_UP,			//上
	HNPTZOPER_RIGHTUP,		//右上
	HNPTZOPER_LEFT,			//左
	HNPTZOPER_RIGHT,		//右
	HNPTZOPER_LEFTDOWN,		//左下
	HNPTZOPER_DOWN,			//下
	HNPTZOPER_RIGHTDOWN,	//右下
	HNPTZOPER_ZOOMWIDE,		//镜头放大
	HNPTZOPER_ZOOMTELE,		//镜头拉近
	HNPTZOPER_FOCUSFAR,		//远聚焦
	HNPTZOPER_FOCUSNEAR,	//近聚焦
	HNPTZOPER_IRISLARGE,	//光圈调大
	HNPTZOPER_IRISSMALL,	//光圈调小
	HNPTZOPER_ACTSTOP,		//动作停止
	HNPTZOPER_ALMSEARCH, //alarm search
	HNPTZOPER_LIGHTON,	//灯光打开
	HNPTZOPER_LIGHTOFF,	//灯光关闭
	HNPTZOPER_SETPRESET,	//设置预置点
	HNPTZOPER_CLEARPRESET,//清除预置点
	HNPTZOPER_GOTOPRESET, //运动到预置点
	HNPTZOPER_AUTOPANON, //自动Pan打开
	HNPTZOPER_AUTOPANOFF, //自动Pan关闭
	HNPTZOPER_SETLEFTLIMIT, //设置左极限
	HNPTZOPER_SETRIGHTLIMIT, //设置右极限
	HNPTZOPER_AUTOSCANON, //自动扫描打开
	HNPTZOPER_AUTOSCANOFF, //自动扫描关闭
	HNPTZOPER_ADDTOUR, //添加自动巡航
	HNPTZOPER_DELTOUR, //删除自动巡航
	HNPTZOPER_STARTTOUR, //开启自动巡航
	HNPTZOPER_STOPTOUR, //关闭自动巡航
	HNPTZOPER_CLEARTOUR, //清除自动巡航
	HNPTZOPER_SETPATTERNBEGIN, //设置模式开始
	HNPTZOPER_SETPATTERNEND, //设置模式结束
	HNPTZOPER_STARTPATTERN, //开始模式
	HNPTZOPER_STOPPATTERN, //停止模式
	HNPTZOPER_CLEARPATTERN, //清除模式
	HNPTZOPER_POSITION, //快速定位
	HNPTZOPER_AUXON, //辅助功能打开
	HNPTZOPER_AUXOFF, //辅助开关关闭
	HNPTZOPER_MENU, //球机菜单
	HNPTZOPER_EXIT, //退出球机菜单
	HNPTZOPER_ENTER, //确认
	HNPTZOPER_ESC, //取消
	HNPTZOPER_MENUUP, //菜单上下操作
	HNPTZOPER_MENUDOWN, //菜单上下操作
	HNPTZOPER_MENULEFT, //菜单左右操作
	HNPTZOPER_MENURIGHT, //菜单左右操作
	HNPTZOPER_TWOPOINTSCAN, //两点扫描
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
	BYTE	vers1;		//主版本号
	BYTE	vers2;		//次版本号
	WORD	cmd;		//操作指令
	DWORD	ssrc;		//会话号
	DWORD	dstid;		//目标ID
	short	code;		//错误码
	WORD	len;		//数据长度
	
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

//用户信息结构体
typedef struct _hn_user
{
	int			usrid;			//用户ID
	char		name[32];	   	//用户名
	char		pswd[36];	   	//密码
	char		grpnm[8];       //用户组名称
}HN_USER;


//服务器信息
typedef struct _hnserver
{
	char		url[32];	//服务器ip地址
	char		usr[32];	//服务器登陆用户名，目前无效
	char		pwd[32];	//服务器登陆密码，目前无效
	WORD	port;		//服务器端口
	char		reser[6];	//保留
}HNSERVER;

//系统服务器信息
typedef struct _hn_server
{
	HNSERVER	alarmsrv;
	HNSERVER	mediasrv;
	HNSERVER  recrdsrv;
}HN_SERVER;


//设备组基本信息
typedef struct _hn_devgrp
{
	int		grpid;                      //设备组编号
	int		parent;						//设备所属管理员ID
	int		usrid;						//设备分组所属用户ID，未分配为0
	char		grpnm[NAME_COL_LEN];     //设备组名称
	char		note[NOTE_COL_LEN];       //备注
}HN_DEVGRP; //sizeof 172

//设备组查询条件信息
typedef struct _hn_devgrp_query
{
	int		pageno;					//页号
	int		pagesize;					//页大小
	int		parent;					//设备所属管理员ID
	int		usrid;					//设备分组所属用户ID，未分配为0
}HN_DEVGRP_QUERY;

//设备组查询分页信息
typedef struct _hn_devgrp_page
{
	int			allpage;				//总页数
	int			pageno;				//当前查询的页号
	int			itemnum;				//当前页的项数
	HN_DEVGRP	item[HNGRPPAGE_MAX_SIZE];//当前页的分组信息
}HN_DEVGRP_PAGE;

//设备基本信息
typedef struct _hn_device
{
	int			devid;					//设备逻辑id，数据库的主键(设备编号)
	int			manufactid;				//设备厂商编号
	int			serialid;					//设备出厂id
	int			grpid;					//设备组编号
	char			name[NAME_COL_LEN];	//设备名称
	char			user[32];					//用户名
	char			pswd[32];				//明文密码
	char			note[48];					//备注
	char			type;                    //设备类型,dvs,ipcam等
	char			chan;                    //视频的视频通道数
	char			aicount;                  //报警输入路数
	char			status;					//设备状态
	int         creatorid;					//创建者id
}HN_DEVICE;  //sizeof 168

//设备列表查询条件信息
typedef struct _hn_device_query
{
	int			pageno;					//页号
	int			pagesize;					//页大小
	int			grpid;					//设备所属分组ID
}HN_DEVICE_QUERY;

//设备列表查询分页信息
typedef struct _hn_device_page
{
	int			allpage;				//总页数
	int			pageno;				//当前查询的页号
	int			itemnum;				//当前页的项数
	HN_DEVICE	item[HNDEVPAGE_MAX_SIZE];//当前页的分组信息
}HN_DEVICE_PAGE;

//在线设备信息
typedef struct _hn_devlive
{
	int			devid;					//设备逻辑id，数据库的主键(设备编号)
	int      	usrid;                 	//用户Id
	char			type;                 	//设备类型,dvs,ipcam等
	char			chan;                   	//视频的视频通道数
	char			aicount;              	//报警输入路数
	char			status;					//设备状态
	int			incid;					//设备产商编号
}HN_DEVLIVE; //sizeof 16

//在线设备查询信息
typedef struct _hn_devlive_page
{
	int				allpage;				//总页数
	int				pageno;				//当前查询的页号
	int				itemnum;				//当前页的项数
	HN_DEVLIVE	item[HNDEVPAGE_MAX_LIVE];//当前页的分组信息
}HN_DEVLIVE_PAGE;


//修改密码
typedef struct _hn_usr_pwdm
{
	int     usrid;
	char    name[32];
	char    oldpwd[36];
	char    newpwd[36];
}HN_USR_PWDM;


//云台控制信息
typedef struct _hn_dev_ptzctl
{
	int			chan;			//云台控制通道
	int			ptzcmd;			//云台控制指令
	int			param;			//云台控制参数
	char		protocol[28];		//云台协议，目前无效
}HN_DEV_PTZCTL;


#endif
