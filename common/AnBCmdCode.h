/****************************************************************************************
*Copyrights  2014，深圳安邦科技有限公司
*All rights reserved.
*
* Filename： AnBCmdCode.h
* Indentifier： 
* Description：内部交互消息命令码
* Version：V1.0
* Author:       dengyongjun
* Finished：    2014年08月25日
* History:
******************************************************************************************/

#ifndef _ANB_CMD_CODE_H_
#define _ANB_CMD_CODE_H_

//通用消息
typedef enum
{
    ANB_CMD_GENERAL_BASE        = 0x0000,

    ANB_CMD_GENERAL_CENNECT     = 0x0001,               //连接消息
    ANB_CMD_GENERAL_HEARBEAT    = 0x0002,               //心跳消息

}ANB_CMD_GENERAL;


//中心服务器交互消息
typedef enum
{
    ANB_CMD_CENTER_BASE                                 = 0x1000,               //中心服务器基类定义

    ANB_CMD_CENTER_LOGIN_REQ                            = 0x1001,               //客户端登陆中心服务器请求
    ANB_CMD_CENTER_LOGIN_RSP                            = 0x1002,               //客户端登陆中心服务器应答

    ANB_CMD_CENTER_LOGOUT_REQ                           = 0x1003,               //客户端登出中心服务器请求
    ANB_CMD_CENTER_LOGOUT_RSP                           = 0x1004,               //客户端登出中心服务器应答

    ANB_CMD_CENTER_GET_LENS_GROUP_LIST_REQ              = 0x1005,               //获取镜头组列表请求
    ANB_CMD_CENTER_GET_LENS_GROUP_LIST_RSP              = 0x1006,               //获取镜头组列表应答

    ANB_CMD_CENTER_GET_LENS_LIST_REQ                    = 0x1007,               //获取镜头列表请求
    ANB_CMD_CENTER_GET_LENS_LIST_RSP                    = 0x1008,               //获取镜头列表应答

    ANB_CMD_CENTER_GET_MEDIA_INFO_REQ                   = 0x1009,               //获取IPC对应的流媒体转发服务器信息请求
    ANB_CMD_CENTER_GET_MEDIA_INFO_RSP                   = 0x100A,               //获取IPC对应的流媒体转发服务器信息应答

    ANB_CMD_CENTER_QUERY_REQ                            = 0x100B,               //客户端录像查询存储服务器请求
    ANB_CMD_CENTER_QUERY_RSP                            = 0x100C,               //客户端录像查询存储服务器应答

    ANB_CMD_CENTER_GET_RECORD_INFO_REQ                   = 0x100D,               //获取IPC对应的存储服务器信息请求
    ANB_CMD_CENTER_GET_RECORD_INFO_RSP                   = 0x100E,               //获取IPC对应的存储服务器信息应答

}ANB_CMD_CENTER;

//告警服务器交互消息
typedef enum
{
    ANB_CMD_ALARM_BASE                                  = 0x2000,               //告警消息基类

    ANB_CMD_ALARM_LOGIN_REQ                             = 0x2001,               //客户端登陆告警服务器请求
    ANB_CMD_ALARM_LOGIN_RSP                             = 0x2002,               //客户端登陆告警服务器应答

    ANB_CMD_ALARM_LOGOUT_REQ                            = 0x2003,               //客户端登出告警服务器请求
    ANB_CMD_ALARM_LOGOUT_RSP                            = 0x2004,               //客户端登出告警服务器应答

    ANB_CMD_ALARM_ALIVE_REQ                                = 0x2005,                //客户端向告警服务器发心跳请求 C====>>S
    ANB_CMD_ALARM_ALIVE_RSP                                = 0x2006,                //告警服务器向客户端发心跳应答 C<<====S

    ANB_CMD_ALARM_REPORT_REQ                            = 0x2007,                //告警消息上报请求         C====>>S
    ANB_CMD_ALARM_REPORT_RSP                            = 0x2008,                //对上报的告警消息进行应答 C<<====S

    ANB_CMD_ALARM_LNKINFO_REQ                            = 0x2009,                //上报到中心服务器的联动请求 alm_server=====>>center_server
    ANB_CMD_ALARM_LNKINFO_RSP                            = 0x200a,                //中心服务器对联动请求的应答 alm_server<<=====center_server

    ANB_CMD_ALARM_LNKRPT_REQ                            = 0x200b,                //报警服务器上报到用户客户端的请求（包括联动信息和告警信息）alm_server=====>>client
    ANB_CMD_ALARM_LNKRPT_RSP                            = 0x200c,                //用户客户端对报警服务器的上报请求进行响应                    alm_server<<=====client

    ANB_CMD_ALARM_PAYLOAD_REQ                            = 0x200d,                //中心服务器向报警服务器请求连接负载情况  alm_server<<=====center_server
    ANB_CMD_ALARM_PAYLOAD_RSP                            = 0x200e,                //报警服务器向中心服务器作出连接负载应答  alm_server=====>>center_server

    ANB_CMD_ALARM_PAYLOAD_RPT_REQ                        = 0x200f,                //报警服务器向中心服务器主动上报连接负载情况 alm_server=====>>center_server
    ANB_CMD_ALARM_PAYLOAD_RPT_RSP                        = 0x2010,                //中心服务器对报警服务器主动上报的负载作应答 alm_server<<=====center_server

}ANB_CMD_ALARM;


typedef enum
{
    ANB_CMD_UNIFORM_BASE                                = 0x3000,               //统一接入消息基类

    ANB_CMD_UNIFORM_LOGIN_REQ                           = 0x3001,               //客户端登陆统一接入服务器请求
    ANB_CMD_UNIFORM_LOGIN_RSP                           = 0x3002,               //客户端登陆统一接入服务器应答

    ANB_CMD_UNIFORM_LOGOUT_REQ                          = 0x3003,               //客户端登出统一接入服务器请求
    ANB_CMD_UNIFORM_LOGOUT_RSP                          = 0x3004,               //客户端登出统一接入服务器应答

    ANB_CMD_UNIFORM_PTZ_CONTROL_REQ                     = 0x3005,               //客户端操作云台请求
    ANB_CMD_UNIFORM_PTZ_CONTROL_RSP                     = 0x3006,               //统一接入服务器响应云台操作应答

    ANB_CMD_UNIFORM_ADD_PRESET_REQ                      = 0x3007,               //添加预置位请求
    ANB_CMD_UNIFORM_ADD_PRESET_RSP                      = 0x3008,               //添加预置位应答

    ANB_CMD_UNIFORM_DEL_PRESET_REQ                      = 0x3009,               //删除预置位请求
    ANB_CMD_UNIFORM_DEL_PRESET_RSP                      = 0x300A,               //删除预置位应答

    ANB_CMD_UNIFORM_GET_PRESET_REQ                      = 0x300B,               //获取预置位请求
    ANB_CMD_UNIFORM_GET_PRESET_RSP                      = 0x300C,               //获取预置位应答

    ANB_CMD_UNIFORM_CALL_PRESET_REQ                     = 0x300D,               //调用预置位请求
    ANB_CMD_UNIFORM_CALL_PRESET_RSP                     = 0x300E,               //调用预置位应答

    ANB_CMD_UNIFORM_SET_PRESETOUR_REQ                   = 0x3011,               //设置巡航请求
    ANB_CMD_UNIFORM_SET_PRESETOUR_RSP                   = 0x3012,               //设置巡航应答

    ANB_CMD_UNIFORM_GET_PRESETOUR_REQ                   = 0x3013,               //获取巡航请求
    ANB_CMD_UNIFORM_GET_PRESETOUR_RSP                   = 0x3014,               //获取巡航应答

    ANB_CMD_UNIFORM_CALL_PRESETOUR_REQ                  = 0x3015,               //调用巡航请求
    ANB_CMD_UNIFORM_CALL_PRESETOUR_RSP                  = 0x3016,               //调用巡航应答

    ANB_CMD_UNIFORM_GET_GUARDER_INFO_REQ                = 0x3017,               //获取看守位请求
    ANB_CMD_UNIFORM_GET_GUARDER_INFO_RSP                = 0x3018,               //获取看守位应答

    ANB_CMD_UNIFORM_SET_GUARDER_INFO_REQ                = 0x3019,               //设置看守位请求
    ANB_CMD_UNIFORM_SET_GUARDER_INFO_RSP                = 0x301A,               //设置看守位应答

    ANB_CMD_UNIFORM_GET_VIDEO_COLOR_REQ                 = 0x3021,               //获取视频色彩请求
    ANB_CMD_UNIFORM_GET_VIDEO_COLOR_RSP                 = 0x3022,               //获取视频色彩应答

    ANB_CMD_UNIFORM_SET_VIDEO_COLOR_REQ                 = 0x3023,               //设置视频色彩请求
    ANB_CMD_UNIFORM_SET_VIDEO_COLOR_RSP                 = 0x3024,               //设置视频色彩应答

    ANB_CMD_UNIFORM_GET_VIDEO_CONFIG_REQ                 = 0x3025,               //设置视频编码配置请求
    ANB_CMD_UNIFORM_GET_VIDEO_CONFIG_RSP                 = 0x3026,               //设置视频编码配置应答

    ANB_CMD_UNIFORM_SET_VIDEO_CONFIG_REQ                 = 0x3027,               //获取视频编码配置请求
    ANB_CMD_UNIFORM_SET_VIDEO_CONFIG_RSP                 = 0x3028,               //获取视频编码配置应答
    
}ANB_CMD_UNIFORM;


typedef enum
{
    ANB_CMD_RECORD_BASE                                = 0x4000,               //统一接入消息基类

    ANB_CMD_RECORD_LOGIN_REQ                           = 0x4001,               //客户端登陆存储服务器请求
    ANB_CMD_RECORD_LOGIN_RSP                           = 0x4002,               //客户端登陆存储服务器应答

    ANB_CMD_RECORD_LOGOUT_REQ                          = 0x4003,               //客户端登出存储服务器请求
    ANB_CMD_RECORD_LOGOUT_RSP                          = 0x4004,               //客户端登出存储服务器应答

    ANB_CMD_RECORD_QUERY_REQ                           = 0x4005,               //客户端录像查询存储服务器请求
    ANB_CMD_RECORD_QUERY_RSP                           = 0x4006,               //客户端录像查询存储服务器应答

    ANB_CMD_RECORD_DOWNLOAD_REQ                        = 0x4007,               //客户端录像下载存储服务器请求
    ANB_CMD_RECORD_DOWNLOAD_RSP                        = 0x4008,               //客户端录像下载存储服务器应答

    ANB_CMD_RECORD_PLAYBACK_REQ                        = 0x4009,               //客户端录像回放存储服务器请求
    ANB_CMD_RECORD_PLAYBACK_RSP                        = 0x400A,               //客户端录像回放存储服务器应答

    ANB_CMD_RECORD_STOP_REQ                            = 0x400B,               //客户端停止录像回放或者下载存储服务器请求
    ANB_CMD_RECORD_STOP_RSP                            = 0x400C,               //客户端停止录像回放或者下载存储服务器应答

    ANB_CMD_RECORD_CTRL_PLAYBACK_REQ                   = 0x400D,               //客户端控制录像回放存储服务器请求
    ANB_CMD_RECORD_CTRL_PLAYBACK_RSP                   = 0x400E,               //客户端控制录像回放存储服务器应答

    ANB_CMD_RECORD_PAUSE_PLAYBACK_REQ                  = 0x4011,               //客户端暂停录像回放存储服务器请求
    ANB_CMD_RECORD_PAUSE_PLAYBACK_RSP                  = 0x4012,               //客户端暂停录像回放存储服务器应答

    ANB_CMD_RECORD_RESUME_PLAYBACK_REQ                 = 0x4011,               //客户端恢复录像回放存储服务器请求
    ANB_CMD_RECORD_RESUME_PLAYBACK_RSP                 = 0x4012,               //客户端恢复录像回放存储服务器应答

    ANB_CMD_RECORD_START_EVENT_RECORD_REQ              = 0x4013,                //开始事件录像请求
    ANB_CMD_RECORD_START_EVENT_RECORD_RSP               = 0x4014,               //开始事件录像应答

    ANB_CMD_RECORD_STOP_EVENT_RECORD_REQ                = 0x4015,                //停止事件录像请求
    ANB_CMD_RECORD_STOP_EVENT_RECORD_RSP                = 0x4016,               //停止事件录像应答
}ANB_CMD_RECORD;

typedef enum
{
    ANB_CMD_MEDIA_BASE                                  = 0x5000,               //流媒体消息基类
    
    ANB_CMD_MEDIA_OPEN_STREAM_REQ                       = 0x5001,               //打开视频请求
    ANB_CMD_MEDIA_OPEN_STREAM_RSP                       = 0x5002,               //打开视频应答

    ANB_CMD_MEDIA_CLOSE_STREAM_REQ                      = 0x5003,               //打开视频请求
    ANB_CMD_MEDIA_CLOSE_STREAM_RSP                      = 0x5004,               //打开视频应答
}ANB_CMD_MEDIA;

/****************云台控制指令bylanqiushu************************/
#define  ANB_PTZ_STOP                            0x1001        //云台停止
#define  ANB_PTZ_UP                              0x1002        //云台向上
#define  ANB_PTZ_DOWN                            0x1003       //云台向下
#define  ANB_PTZ_LEFT                            0x1004       //云台向左
#define  ANB_PTZ_LEFT_UP                         0x1005       //云台左上
#define  ANB_PTZ_LEFT_DOWN                       0x1006      //云台左下
#define  ANB_PTZ_RIGHT                           0x1007      //云台向右
#define  ANB_PTZ_RIGHT_UP                        0x1008      //云台右上
#define  ANB_PTZ_RIGHT_DOWN                      0x1009      //云台右下
#define  ANB_PTZ_AUTO                            0x100A      //云台自动
#define  ANB_PTZ_PREFAB_BIT_SET                  0x100B      //预置位设置
#define  ANB_PTZ_PREFAB_BIT_DEL                  0x100C      //预置位删除
#define  ANB_PTZ_PREFAB_BIT_RUN                  0x100D      //预置位运行
#define  ANB_PTZ_MODE_SET_START                  0x100E       //模式设置开始
#define  ANB_PTZ_MODE_SET_STOP                   0x100F      //模式设置停止
#define  ANB_PTZ_MODE_RUN                        0x1010     //模式运行
#define  ANB_PTZ_MENU_OPEN                       0x1011     //打开镜头
#define  ANB_PTZ_MENU_EXIT                       0x1012      //关闭镜头
#define  ANB_PTZ_MENU_ENTER                      0x1013       //进入镜头
#define  ANB_PTZ_FLIP                            0x1014     //云台翻转度
#define  ANB_PTZ_START                           0x1015      //云台转至起始位
#define  ANB_TOUR_360                            0x1016     //360度巡航，开始
#define  ANB_TOUR_180                            0x1017    //180度巡航，开始
/***************************end*********************************/


#endif