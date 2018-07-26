/****************************************************************************************
*Copyrights  2014，深圳安邦科技有限公司
*All rights reserved.
*
* Filename： AnBErrorCode.h
* Indentifier： 
* Description：定义网络库使用的结构体
* Version：V1.0
* Author:       dengyongjun
* Finished：    2014年08月14日
* History:
******************************************************************************************/

#ifndef _ANB_ERROR_CODE_H_
#define _ANB_ERROR_CODE_H_

typedef enum
{
    ANB_RET_OK = 0x0000,
    ANB_ERROR_FAILED,                   //失败，通用提示，没有具体到什么错误
    ANB_ERRORIMEOUT,                  //通讯超时
    ANB_ERROR_NULLPARAM,                //参数为空
    ANB_ERROR_EXIST,                    //已存在
    ANB_ERROR_PARAMLENERR,              //参数长度异常
    ABN_ERROR_DATA_NOT_EXIST,           //数据不存在

    ABN_ERROR_UNKNOWN_MSG,              //未知消息
}ANB_ERROR;

typedef enum
{
    ANB_ERROR_CENTER_BASE = 0x0100,

    ANB_ERROR_LOGIN_ERROR = 0x0101,    //登陆信息错误

    ANB_ERROR_GET_LENS_ID_ERROR = 0x0102,

    ANB_ERROR_GET_SERVER_SOCKET_ERROR = 0x0103,  //根据服务器ID获取连接中心服务器的SOCKETID失败

    ANB_ERROR_GET_CLIENT_SOCKET_ERROR = 0x0104,  //根据服务器ID获取连接中心服务器的SOCKETID失败

    ANB_ERROR_GET_SERVER_INFOR_ERROR = 0x0105,  //根据镜头ID获取统一接入服务器信息失败

    ANB_ERROR_GET_QUERY_RECORD_ERROR = 0x0106,  //到中心服务器镜头录像记录失败

    ANB_ERROR_START_EVENT_RECORD_ERROR = 0x0107,  //事件录像记录失败

}ANB_ERROR_CENTER;


// 所有接口函数，执行成功时返回0或正值，负值表示错误。

#define ERR_ANB_FUNCTION_NOT_EXIST        -100    // 函数不存在
#define ERR_ANB_PARAMETER                -101    // 参数错误    
#define ERR_ANB_CALL_ORDER                -102    // 调用顺序错误
#define ERR_ANB_HANDLE_EXHAUSTED        -103    // 通讯句柄用尽
#define ERR_ANB_PREVIEW_START            -104    // 预览失败
#define ERR_ANB_DVS_CONNECT                -105    // 连接视频服务器失败
#define ERR_ANB_DVS_AUTH                -106    // 视频服务器验证失败
#define ERR_ANB_DVSYPE_INVALID            -107    // 无效的设备类型
#define ERR_ANB_DVS_STREAM                -108    // 配置视频服务器流失败
#define ERR_ANB_CREATE_DECODE            -109    // 创建解码器失败
#define ERR_ANB_CREATE_DISPLAY            -110    // 创建显示设备失败
#define ERR_ANB_CREATE_AUDIO            -111    // 创建音频设备失败
#define ERR_ANB_SNAP                    -112    // 抓图失败
#define ERR_ANB_RECORD                    -113    // 录像失败
#define ERR_ANB_VOL_SET                    -114    // 设置音频输出音量失败 
#define ERR_ANB_VOL_GET                    -115    // 获取音频输出音量失败
#define ERR_ANB_DRAW_CALLBACK            -116    // 注册显示回调函数失败
#define ERR_ANB_DECODE_CALLBACK            -117    // 注册解码数据回调函数失败
#define ERR_ANB_SEARCH_DVS                -118    // 搜索设备失败
#define ERR_ANB_DVSVER_GET                -119    // 获取设备版本信息失败
#define ERR_ANB_PTZ                        -120    // 云台控制操作失败
#define ERR_ANB_PRESET_GET                -121    // 获取预置位失败
#define ERR_ANB_PRESET_ADD                -122    // 添加预置位失败
#define ERR_ANB_PRESET_DEL                -123    // 删除预置位失败
#define ERR_ANB_PRESET_CALL                -124    // 调用预置位失败
#define ERR_ANB_SENSOROUT_GET            -125    // 获取探头输出开关状态失败
#define ERR_ANB_SENSOROUT_SET            -126    // 设置探头输出开关状态失败
#define ERR_ANB_GUARD_GET                -127    // 获取看守位配置失败
#define ERR_ANB_GUARD_SET                -128    // 设置看守位配置失败
#define ERR_ANB_DEV_VOL_GET                -129    // 获取视频服务器声卡音量失败
#define ERR_ANB_DEV_VOL_SET                -130    // 设置视频服务器声卡音量失败
#define ERR_ANB_DEV_BPS_GET                -129    // 获取视频服务器码率配置失败
#define ERR_ANB_DEV_BPS_SET                -130    // 设置视频服务器码率配置失败
#define ERR_ANB_DEV_COLOR_GET            -131    // 获取视频服务器颜色配置失败
#define ERR_ANB_DEV_COLOR_SET            -132    // 设置视频服务器颜色配置失败
#define ERR_ANB_DEV_COM_GET                -133    // 获取视频服务器串口配置失败
#define ERR_ANB_DEV_COM_SET                -134    // 设置视频服务器串口配置失败
#define ERR_ANB_DEV_MD_GET                -135    // 获取视频服务器移动侦测配置失败
#define ERR_ANB_DEV_MD_SET                -136    // 设置视频服务器移动侦测配置失败
#define ERR_ANB_DEV_NET_GET                -137    // 获取视频服务器网络配置失败
#define ERR_ANB_DEV_NET_SET                -138    // 设置视频服务器网络配置失败
#define ERR_ANB_DEV_WIFI_GET            -139    // 获取视频服务器无线WIFI配置失败
#define ERR_ANB_DEV_WIFI_SET            -140    // 设置视频服务器无线WIFI配置失败
#define ERR_ANB_DEV_OSD_GET                -141    // 获取视频服务器OSD配置失败
#define ERR_ANB_DEV_OSD_SET                -142    // 设置视频服务器OSD配置失败
#define ERR_ANB_DEV_DEFAULT                -143    // 恢复视频服务器出厂默认值失败
#define ERR_ANB_DEV_REBOOT                -144    // 重启视频服务器设备失败
#define ERR_ANB_DEV_RESET                -145    // 重启视频服务器服务失败
#define ERR_ANB_DEV_NAME_GET            -146    // 获取视频服务器设备名称失败
#define ERR_ANB_DEV_NAME_SET            -147    // 设置视频服务器设备名称失败
#define ERR_ANB_DEV_VE_INFO_GET            -148    // 获取视频服务器当前编码信息失败
#define ERR_ANB_DEV_VE_INFO_SET            -149    // 设置视频服务器当前编码信息失败
#define ERR_ANB_CHN_VE_INFO_GET            -150    // 获取视频服务器当前通道编码信息失败
#define ERR_ANB_DEV_PORT_GET            -151    // 获取视频服务器通讯端口失败
#define ERR_ANB_DEV_PORT_SET            -152    // 设置视频服务器通讯端口失败
#define ERR_ANB_DEV_UPNP_GET            -153    // 获取视频服务器UPNP状态失败
#define ERR_ANB_DEV_UPNP_SET            -154    // 设置视频服务器UPNP状态失败
#define ERR_ANB_DEV_PPPOE_GET            -155    // 获取视频服务器PPPOE状态失败
#define ERR_ANB_DEV_PPPOE_SET            -156    // 设置视频服务器PPPOE状态失败
#define ERR_ANB_DEV_DDNS_GET            -157    // 获取视频服务器DDNS失败
#define ERR_ANB_DEV_DDNS_SET            -158    // 设置视频服务器DDNS失败
#define ERR_ANB_DEV_NTP_GET                -159    // 获取视频服务器NTP失败
#define ERR_ANB_DEV_NTP_SET                -160    // 设置视频服务器NTP失败
#define ERR_ANB_DEVIME_GET                -159    // 获取视频服务器时钟失败
#define ERR_ANB_DEVIME_SET                -160    // 设置视频服务器时钟失败
#define ERR_ANB_DEVIMEZONE_SET            -161    // 设置视频服务器时区失败
#define ERR_ANB_DEV_VL_GET                -162    // 获取视频服务器视频丢失配置失败
#define ERR_ANB_DEV_VL_SET                -163    // 设置视频服务器视频丢失配置失败
#define ERR_ANB_DEV_AUTHMODE_GET        -164    // 获取视频服务器用户验证配置失败
#define ERR_ANB_DEV_AUTHMODE_SET        -165    // 设置视频服务器用户验证配置失败
#define ERR_ANB_DEV_USER_GET            -166    // 获取视频服务器用户失败
#define ERR_ANB_DEV_USER_ADD            -167    // 添加用户失败
#define ERR_ANB_DEV_USER_SET            -168    // 修改用户配置失败
#define ERR_ANB_DEV_USER_DEL            -169    // 删除用户失败
#define ERR_ANB_DEV_UPDATE_PACKET        -170    // 升级视频服务器包失败
#define ERR_ANB_DEV_SENSOR_IN_GET        -171    // 获取视频服务器探头报警配置失败
#define ERR_ANB_DEV_SENSOR_IN_SET        -172    // 设置视频服务器探头报警配置失败
#define ERR_ANB_DEV_REC_STATUS_GET        -173    // 获取视频服务器前端录像状态配置失败
#define ERR_ANB_DEV_DISK_STRATEGY_GET    -174    // 获取磁盘管理策略失败
#define ERR_ANB_DEV_DISK_STRATEGY_SET    -175    // 设置磁盘管理策略失败
#define ERR_ANB_DEV_REC_START            -176    // 控制视频服务器前端录像失败
#define ERR_ANB_DEVRACK_GET                -177    // 获取视频服务器轨迹配置失败
#define ERR_ANB_DEVRACK_SET                -178    // 设置视频服务器轨迹配置失败
#define ERR_ANB_DEVRACK_CALL            -179    // 调用轨迹失败
#define ERR_ANB_DEV_SENDP09_CMD            -180    // 发送透明端口指令失败
#define ERR_ANB_DEV_AC_GET                -181    // 获取报警联动报警中心配置失败
#define ERR_ANB_DEV_AC_SET                -182    // 设置报警联动报警中心配置失败
#define ERR_ANB_DEV_EMAIL_GET            -183    // 获取报警联动邮件配置失败
#define ERR_ANB_DEV_EMAIL_SET            -184    // 设置报警联动邮件配置失败
#define ERR_ANB_DEV_FTP_GET                -185    // 获取报警联动FTP配置失败
#define ERR_ANB_DEV_FTP_SET                -186    // 设置报警联动FTP配置失败
#define ERR_ANB_DEV_SENSOROUT_GET        -187    // 获取报警联动探头输出配置失败
#define ERR_ANB_DEV_SENSOROUT_SET        -188    // 设置报警联动探头输出配置失败
#define ERR_ANB_DEV_REC_GET                -189    // 获取报警联动录像配置失败
#define ERR_ANB_DEV_REC_SET                -190    // 设置报警联动录像配置失败
#define ERR_ANB_DEV_SENSORIN_CA_GET        -191    // 获取探头输入报警联动配置失败
#define ERR_ANB_DEV_SENSORIN_CA_SET        -192    // 设置探头输入报警联动配置失败
#define ERR_ANB_DEV_MD_CA_GET            -193    // 获取移动侦测报警联动配置失败
#define ERR_ANB_DEV_MD_CA_SET            -194    // 设置移动侦测报警联动配置失败
#define ERR_ANB_DEV_VL_CA_GET            -195    // 获取视频丢失报警联动配置失败
#define ERR_ANB_DEV_VL_CA_SET            -196    // 设置视频丢失报警联动配置失败
#define ERR_ANB_DEV_VOD_SEARCH_START    -197    // 开始搜索前端录像文件失败
#define ERR_ANB_DEV_VOD_SEARCH_STOP        -198    // 停止搜索前端录像文件失败
#define ERR_ANB_DEV_HS_GET                -199    // 获取HS设备注册配置信息
#define ERR_ANB_DEV_HS_SET                -200    // 设置HS设备注册配置信息
#define ERR_ANB_MPEGPS_CALLBACK            -201    // 注册MPEG-PS回调函数失败
#define ERR_ANB_DEV_VM_GET                -202    // 获取视频服务器视频遮挡配置失败
#define ERR_ANB_DEV_VM_SET                -203    // 设置视频服务器视频遮挡配置失败

#define ERR_ANB_GET_PRESETOUR           -210    //获取预置位巡航失败
#define ERR_ANB_SET_PRESETOUR           -211    //设置预置位巡航失败
#define ERR_ANB_CALL_PRESETOUR          -212    //调用预置位巡航失败
#define ERR_ANB_PLAYBACK                -213    //远程回放失败

    
#define ERR_ANB_CONTROL_PROTOCOL        -400    // 

#endif

