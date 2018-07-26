/****************************************************************************************
*Copyrights  2014�����ڰ���Ƽ����޹�˾
*All rights reserved.
*
* Filename�� AnBCmdCode.h
* Indentifier�� 
* Description���ڲ�������Ϣ������
* Version��V1.0
* Author:       dengyongjun
* Finished��    2014��08��25��
* History:
******************************************************************************************/

#ifndef _ANB_CMD_CODE_H_
#define _ANB_CMD_CODE_H_

//ͨ����Ϣ
typedef enum
{
    ANB_CMD_GENERAL_BASE        = 0x0000,

    ANB_CMD_GENERAL_CENNECT     = 0x0001,               //������Ϣ
    ANB_CMD_GENERAL_HEARBEAT    = 0x0002,               //������Ϣ

}ANB_CMD_GENERAL;


//���ķ�����������Ϣ
typedef enum
{
    ANB_CMD_CENTER_BASE                                 = 0x1000,               //���ķ��������ඨ��

    ANB_CMD_CENTER_LOGIN_REQ                            = 0x1001,               //�ͻ��˵�½���ķ���������
    ANB_CMD_CENTER_LOGIN_RSP                            = 0x1002,               //�ͻ��˵�½���ķ�����Ӧ��

    ANB_CMD_CENTER_LOGOUT_REQ                           = 0x1003,               //�ͻ��˵ǳ����ķ���������
    ANB_CMD_CENTER_LOGOUT_RSP                           = 0x1004,               //�ͻ��˵ǳ����ķ�����Ӧ��

    ANB_CMD_CENTER_GET_LENS_GROUP_LIST_REQ              = 0x1005,               //��ȡ��ͷ���б�����
    ANB_CMD_CENTER_GET_LENS_GROUP_LIST_RSP              = 0x1006,               //��ȡ��ͷ���б�Ӧ��

    ANB_CMD_CENTER_GET_LENS_LIST_REQ                    = 0x1007,               //��ȡ��ͷ�б�����
    ANB_CMD_CENTER_GET_LENS_LIST_RSP                    = 0x1008,               //��ȡ��ͷ�б�Ӧ��

    ANB_CMD_CENTER_GET_MEDIA_INFO_REQ                   = 0x1009,               //��ȡIPC��Ӧ����ý��ת����������Ϣ����
    ANB_CMD_CENTER_GET_MEDIA_INFO_RSP                   = 0x100A,               //��ȡIPC��Ӧ����ý��ת����������ϢӦ��

    ANB_CMD_CENTER_QUERY_REQ                            = 0x100B,               //�ͻ���¼���ѯ�洢����������
    ANB_CMD_CENTER_QUERY_RSP                            = 0x100C,               //�ͻ���¼���ѯ�洢������Ӧ��

    ANB_CMD_CENTER_GET_RECORD_INFO_REQ                   = 0x100D,               //��ȡIPC��Ӧ�Ĵ洢��������Ϣ����
    ANB_CMD_CENTER_GET_RECORD_INFO_RSP                   = 0x100E,               //��ȡIPC��Ӧ�Ĵ洢��������ϢӦ��

}ANB_CMD_CENTER;

//�澯������������Ϣ
typedef enum
{
    ANB_CMD_ALARM_BASE                                  = 0x2000,               //�澯��Ϣ����

    ANB_CMD_ALARM_LOGIN_REQ                             = 0x2001,               //�ͻ��˵�½�澯����������
    ANB_CMD_ALARM_LOGIN_RSP                             = 0x2002,               //�ͻ��˵�½�澯������Ӧ��

    ANB_CMD_ALARM_LOGOUT_REQ                            = 0x2003,               //�ͻ��˵ǳ��澯����������
    ANB_CMD_ALARM_LOGOUT_RSP                            = 0x2004,               //�ͻ��˵ǳ��澯������Ӧ��

    ANB_CMD_ALARM_ALIVE_REQ                                = 0x2005,                //�ͻ�����澯���������������� C====>>S
    ANB_CMD_ALARM_ALIVE_RSP                                = 0x2006,                //�澯��������ͻ��˷�����Ӧ�� C<<====S

    ANB_CMD_ALARM_REPORT_REQ                            = 0x2007,                //�澯��Ϣ�ϱ�����         C====>>S
    ANB_CMD_ALARM_REPORT_RSP                            = 0x2008,                //���ϱ��ĸ澯��Ϣ����Ӧ�� C<<====S

    ANB_CMD_ALARM_LNKINFO_REQ                            = 0x2009,                //�ϱ������ķ��������������� alm_server=====>>center_server
    ANB_CMD_ALARM_LNKINFO_RSP                            = 0x200a,                //���ķ����������������Ӧ�� alm_server<<=====center_server

    ANB_CMD_ALARM_LNKRPT_REQ                            = 0x200b,                //�����������ϱ����û��ͻ��˵����󣨰���������Ϣ�͸澯��Ϣ��alm_server=====>>client
    ANB_CMD_ALARM_LNKRPT_RSP                            = 0x200c,                //�û��ͻ��˶Ա������������ϱ����������Ӧ                    alm_server<<=====client

    ANB_CMD_ALARM_PAYLOAD_REQ                            = 0x200d,                //���ķ������򱨾��������������Ӹ������  alm_server<<=====center_server
    ANB_CMD_ALARM_PAYLOAD_RSP                            = 0x200e,                //���������������ķ������������Ӹ���Ӧ��  alm_server=====>>center_server

    ANB_CMD_ALARM_PAYLOAD_RPT_REQ                        = 0x200f,                //���������������ķ����������ϱ����Ӹ������ alm_server=====>>center_server
    ANB_CMD_ALARM_PAYLOAD_RPT_RSP                        = 0x2010,                //���ķ������Ա��������������ϱ��ĸ�����Ӧ�� alm_server<<=====center_server

}ANB_CMD_ALARM;


typedef enum
{
    ANB_CMD_UNIFORM_BASE                                = 0x3000,               //ͳһ������Ϣ����

    ANB_CMD_UNIFORM_LOGIN_REQ                           = 0x3001,               //�ͻ��˵�½ͳһ�������������
    ANB_CMD_UNIFORM_LOGIN_RSP                           = 0x3002,               //�ͻ��˵�½ͳһ���������Ӧ��

    ANB_CMD_UNIFORM_LOGOUT_REQ                          = 0x3003,               //�ͻ��˵ǳ�ͳһ�������������
    ANB_CMD_UNIFORM_LOGOUT_RSP                          = 0x3004,               //�ͻ��˵ǳ�ͳһ���������Ӧ��

    ANB_CMD_UNIFORM_PTZ_CONTROL_REQ                     = 0x3005,               //�ͻ��˲�����̨����
    ANB_CMD_UNIFORM_PTZ_CONTROL_RSP                     = 0x3006,               //ͳһ�����������Ӧ��̨����Ӧ��

    ANB_CMD_UNIFORM_ADD_PRESET_REQ                      = 0x3007,               //���Ԥ��λ����
    ANB_CMD_UNIFORM_ADD_PRESET_RSP                      = 0x3008,               //���Ԥ��λӦ��

    ANB_CMD_UNIFORM_DEL_PRESET_REQ                      = 0x3009,               //ɾ��Ԥ��λ����
    ANB_CMD_UNIFORM_DEL_PRESET_RSP                      = 0x300A,               //ɾ��Ԥ��λӦ��

    ANB_CMD_UNIFORM_GET_PRESET_REQ                      = 0x300B,               //��ȡԤ��λ����
    ANB_CMD_UNIFORM_GET_PRESET_RSP                      = 0x300C,               //��ȡԤ��λӦ��

    ANB_CMD_UNIFORM_CALL_PRESET_REQ                     = 0x300D,               //����Ԥ��λ����
    ANB_CMD_UNIFORM_CALL_PRESET_RSP                     = 0x300E,               //����Ԥ��λӦ��

    ANB_CMD_UNIFORM_SET_PRESETOUR_REQ                   = 0x3011,               //����Ѳ������
    ANB_CMD_UNIFORM_SET_PRESETOUR_RSP                   = 0x3012,               //����Ѳ��Ӧ��

    ANB_CMD_UNIFORM_GET_PRESETOUR_REQ                   = 0x3013,               //��ȡѲ������
    ANB_CMD_UNIFORM_GET_PRESETOUR_RSP                   = 0x3014,               //��ȡѲ��Ӧ��

    ANB_CMD_UNIFORM_CALL_PRESETOUR_REQ                  = 0x3015,               //����Ѳ������
    ANB_CMD_UNIFORM_CALL_PRESETOUR_RSP                  = 0x3016,               //����Ѳ��Ӧ��

    ANB_CMD_UNIFORM_GET_GUARDER_INFO_REQ                = 0x3017,               //��ȡ����λ����
    ANB_CMD_UNIFORM_GET_GUARDER_INFO_RSP                = 0x3018,               //��ȡ����λӦ��

    ANB_CMD_UNIFORM_SET_GUARDER_INFO_REQ                = 0x3019,               //���ÿ���λ����
    ANB_CMD_UNIFORM_SET_GUARDER_INFO_RSP                = 0x301A,               //���ÿ���λӦ��

    ANB_CMD_UNIFORM_GET_VIDEO_COLOR_REQ                 = 0x3021,               //��ȡ��Ƶɫ������
    ANB_CMD_UNIFORM_GET_VIDEO_COLOR_RSP                 = 0x3022,               //��ȡ��Ƶɫ��Ӧ��

    ANB_CMD_UNIFORM_SET_VIDEO_COLOR_REQ                 = 0x3023,               //������Ƶɫ������
    ANB_CMD_UNIFORM_SET_VIDEO_COLOR_RSP                 = 0x3024,               //������Ƶɫ��Ӧ��

    ANB_CMD_UNIFORM_GET_VIDEO_CONFIG_REQ                 = 0x3025,               //������Ƶ������������
    ANB_CMD_UNIFORM_GET_VIDEO_CONFIG_RSP                 = 0x3026,               //������Ƶ��������Ӧ��

    ANB_CMD_UNIFORM_SET_VIDEO_CONFIG_REQ                 = 0x3027,               //��ȡ��Ƶ������������
    ANB_CMD_UNIFORM_SET_VIDEO_CONFIG_RSP                 = 0x3028,               //��ȡ��Ƶ��������Ӧ��
    
}ANB_CMD_UNIFORM;


typedef enum
{
    ANB_CMD_RECORD_BASE                                = 0x4000,               //ͳһ������Ϣ����

    ANB_CMD_RECORD_LOGIN_REQ                           = 0x4001,               //�ͻ��˵�½�洢����������
    ANB_CMD_RECORD_LOGIN_RSP                           = 0x4002,               //�ͻ��˵�½�洢������Ӧ��

    ANB_CMD_RECORD_LOGOUT_REQ                          = 0x4003,               //�ͻ��˵ǳ��洢����������
    ANB_CMD_RECORD_LOGOUT_RSP                          = 0x4004,               //�ͻ��˵ǳ��洢������Ӧ��

    ANB_CMD_RECORD_QUERY_REQ                           = 0x4005,               //�ͻ���¼���ѯ�洢����������
    ANB_CMD_RECORD_QUERY_RSP                           = 0x4006,               //�ͻ���¼���ѯ�洢������Ӧ��

    ANB_CMD_RECORD_DOWNLOAD_REQ                        = 0x4007,               //�ͻ���¼�����ش洢����������
    ANB_CMD_RECORD_DOWNLOAD_RSP                        = 0x4008,               //�ͻ���¼�����ش洢������Ӧ��

    ANB_CMD_RECORD_PLAYBACK_REQ                        = 0x4009,               //�ͻ���¼��طŴ洢����������
    ANB_CMD_RECORD_PLAYBACK_RSP                        = 0x400A,               //�ͻ���¼��طŴ洢������Ӧ��

    ANB_CMD_RECORD_STOP_REQ                            = 0x400B,               //�ͻ���ֹͣ¼��طŻ������ش洢����������
    ANB_CMD_RECORD_STOP_RSP                            = 0x400C,               //�ͻ���ֹͣ¼��طŻ������ش洢������Ӧ��

    ANB_CMD_RECORD_CTRL_PLAYBACK_REQ                   = 0x400D,               //�ͻ��˿���¼��طŴ洢����������
    ANB_CMD_RECORD_CTRL_PLAYBACK_RSP                   = 0x400E,               //�ͻ��˿���¼��طŴ洢������Ӧ��

    ANB_CMD_RECORD_PAUSE_PLAYBACK_REQ                  = 0x4011,               //�ͻ�����ͣ¼��طŴ洢����������
    ANB_CMD_RECORD_PAUSE_PLAYBACK_RSP                  = 0x4012,               //�ͻ�����ͣ¼��طŴ洢������Ӧ��

    ANB_CMD_RECORD_RESUME_PLAYBACK_REQ                 = 0x4011,               //�ͻ��˻ָ�¼��طŴ洢����������
    ANB_CMD_RECORD_RESUME_PLAYBACK_RSP                 = 0x4012,               //�ͻ��˻ָ�¼��طŴ洢������Ӧ��

    ANB_CMD_RECORD_START_EVENT_RECORD_REQ              = 0x4013,                //��ʼ�¼�¼������
    ANB_CMD_RECORD_START_EVENT_RECORD_RSP               = 0x4014,               //��ʼ�¼�¼��Ӧ��

    ANB_CMD_RECORD_STOP_EVENT_RECORD_REQ                = 0x4015,                //ֹͣ�¼�¼������
    ANB_CMD_RECORD_STOP_EVENT_RECORD_RSP                = 0x4016,               //ֹͣ�¼�¼��Ӧ��
}ANB_CMD_RECORD;

typedef enum
{
    ANB_CMD_MEDIA_BASE                                  = 0x5000,               //��ý����Ϣ����
    
    ANB_CMD_MEDIA_OPEN_STREAM_REQ                       = 0x5001,               //����Ƶ����
    ANB_CMD_MEDIA_OPEN_STREAM_RSP                       = 0x5002,               //����ƵӦ��

    ANB_CMD_MEDIA_CLOSE_STREAM_REQ                      = 0x5003,               //����Ƶ����
    ANB_CMD_MEDIA_CLOSE_STREAM_RSP                      = 0x5004,               //����ƵӦ��
}ANB_CMD_MEDIA;

/****************��̨����ָ��bylanqiushu************************/
#define  ANB_PTZ_STOP                            0x1001        //��ֹ̨ͣ
#define  ANB_PTZ_UP                              0x1002        //��̨����
#define  ANB_PTZ_DOWN                            0x1003       //��̨����
#define  ANB_PTZ_LEFT                            0x1004       //��̨����
#define  ANB_PTZ_LEFT_UP                         0x1005       //��̨����
#define  ANB_PTZ_LEFT_DOWN                       0x1006      //��̨����
#define  ANB_PTZ_RIGHT                           0x1007      //��̨����
#define  ANB_PTZ_RIGHT_UP                        0x1008      //��̨����
#define  ANB_PTZ_RIGHT_DOWN                      0x1009      //��̨����
#define  ANB_PTZ_AUTO                            0x100A      //��̨�Զ�
#define  ANB_PTZ_PREFAB_BIT_SET                  0x100B      //Ԥ��λ����
#define  ANB_PTZ_PREFAB_BIT_DEL                  0x100C      //Ԥ��λɾ��
#define  ANB_PTZ_PREFAB_BIT_RUN                  0x100D      //Ԥ��λ����
#define  ANB_PTZ_MODE_SET_START                  0x100E       //ģʽ���ÿ�ʼ
#define  ANB_PTZ_MODE_SET_STOP                   0x100F      //ģʽ����ֹͣ
#define  ANB_PTZ_MODE_RUN                        0x1010     //ģʽ����
#define  ANB_PTZ_MENU_OPEN                       0x1011     //�򿪾�ͷ
#define  ANB_PTZ_MENU_EXIT                       0x1012      //�رվ�ͷ
#define  ANB_PTZ_MENU_ENTER                      0x1013       //���뾵ͷ
#define  ANB_PTZ_FLIP                            0x1014     //��̨��ת��
#define  ANB_PTZ_START                           0x1015      //��̨ת����ʼλ
#define  ANB_TOUR_360                            0x1016     //360��Ѳ������ʼ
#define  ANB_TOUR_180                            0x1017    //180��Ѳ������ʼ
/***************************end*********************************/


#endif