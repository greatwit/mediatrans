/****************************************************************************************
*Copyrights  2014�����ڰ���Ƽ����޹�˾
*All rights reserved.
*
* Filename�� AnBErrorCode.h
* Indentifier�� 
* Description�����������ʹ�õĽṹ��
* Version��V1.0
* Author:       dengyongjun
* Finished��    2014��08��14��
* History:
******************************************************************************************/

#ifndef _ANB_ERROR_CODE_H_
#define _ANB_ERROR_CODE_H_

typedef enum
{
    ANB_RET_OK = 0x0000,
    ANB_ERROR_FAILED,                   //ʧ�ܣ�ͨ����ʾ��û�о��嵽ʲô����
    ANB_ERRORIMEOUT,                  //ͨѶ��ʱ
    ANB_ERROR_NULLPARAM,                //����Ϊ��
    ANB_ERROR_EXIST,                    //�Ѵ���
    ANB_ERROR_PARAMLENERR,              //���������쳣
    ABN_ERROR_DATA_NOT_EXIST,           //���ݲ�����

    ABN_ERROR_UNKNOWN_MSG,              //δ֪��Ϣ
}ANB_ERROR;

typedef enum
{
    ANB_ERROR_CENTER_BASE = 0x0100,

    ANB_ERROR_LOGIN_ERROR = 0x0101,    //��½��Ϣ����

    ANB_ERROR_GET_LENS_ID_ERROR = 0x0102,

    ANB_ERROR_GET_SERVER_SOCKET_ERROR = 0x0103,  //���ݷ�����ID��ȡ�������ķ�������SOCKETIDʧ��

    ANB_ERROR_GET_CLIENT_SOCKET_ERROR = 0x0104,  //���ݷ�����ID��ȡ�������ķ�������SOCKETIDʧ��

    ANB_ERROR_GET_SERVER_INFOR_ERROR = 0x0105,  //���ݾ�ͷID��ȡͳһ�����������Ϣʧ��

    ANB_ERROR_GET_QUERY_RECORD_ERROR = 0x0106,  //�����ķ�������ͷ¼���¼ʧ��

    ANB_ERROR_START_EVENT_RECORD_ERROR = 0x0107,  //�¼�¼���¼ʧ��

}ANB_ERROR_CENTER;


// ���нӿں�����ִ�гɹ�ʱ����0����ֵ����ֵ��ʾ����

#define ERR_ANB_FUNCTION_NOT_EXIST        -100    // ����������
#define ERR_ANB_PARAMETER                -101    // ��������    
#define ERR_ANB_CALL_ORDER                -102    // ����˳�����
#define ERR_ANB_HANDLE_EXHAUSTED        -103    // ͨѶ����þ�
#define ERR_ANB_PREVIEW_START            -104    // Ԥ��ʧ��
#define ERR_ANB_DVS_CONNECT                -105    // ������Ƶ������ʧ��
#define ERR_ANB_DVS_AUTH                -106    // ��Ƶ��������֤ʧ��
#define ERR_ANB_DVSYPE_INVALID            -107    // ��Ч���豸����
#define ERR_ANB_DVS_STREAM                -108    // ������Ƶ��������ʧ��
#define ERR_ANB_CREATE_DECODE            -109    // ����������ʧ��
#define ERR_ANB_CREATE_DISPLAY            -110    // ������ʾ�豸ʧ��
#define ERR_ANB_CREATE_AUDIO            -111    // ������Ƶ�豸ʧ��
#define ERR_ANB_SNAP                    -112    // ץͼʧ��
#define ERR_ANB_RECORD                    -113    // ¼��ʧ��
#define ERR_ANB_VOL_SET                    -114    // ������Ƶ�������ʧ�� 
#define ERR_ANB_VOL_GET                    -115    // ��ȡ��Ƶ�������ʧ��
#define ERR_ANB_DRAW_CALLBACK            -116    // ע����ʾ�ص�����ʧ��
#define ERR_ANB_DECODE_CALLBACK            -117    // ע��������ݻص�����ʧ��
#define ERR_ANB_SEARCH_DVS                -118    // �����豸ʧ��
#define ERR_ANB_DVSVER_GET                -119    // ��ȡ�豸�汾��Ϣʧ��
#define ERR_ANB_PTZ                        -120    // ��̨���Ʋ���ʧ��
#define ERR_ANB_PRESET_GET                -121    // ��ȡԤ��λʧ��
#define ERR_ANB_PRESET_ADD                -122    // ���Ԥ��λʧ��
#define ERR_ANB_PRESET_DEL                -123    // ɾ��Ԥ��λʧ��
#define ERR_ANB_PRESET_CALL                -124    // ����Ԥ��λʧ��
#define ERR_ANB_SENSOROUT_GET            -125    // ��ȡ̽ͷ�������״̬ʧ��
#define ERR_ANB_SENSOROUT_SET            -126    // ����̽ͷ�������״̬ʧ��
#define ERR_ANB_GUARD_GET                -127    // ��ȡ����λ����ʧ��
#define ERR_ANB_GUARD_SET                -128    // ���ÿ���λ����ʧ��
#define ERR_ANB_DEV_VOL_GET                -129    // ��ȡ��Ƶ��������������ʧ��
#define ERR_ANB_DEV_VOL_SET                -130    // ������Ƶ��������������ʧ��
#define ERR_ANB_DEV_BPS_GET                -129    // ��ȡ��Ƶ��������������ʧ��
#define ERR_ANB_DEV_BPS_SET                -130    // ������Ƶ��������������ʧ��
#define ERR_ANB_DEV_COLOR_GET            -131    // ��ȡ��Ƶ��������ɫ����ʧ��
#define ERR_ANB_DEV_COLOR_SET            -132    // ������Ƶ��������ɫ����ʧ��
#define ERR_ANB_DEV_COM_GET                -133    // ��ȡ��Ƶ��������������ʧ��
#define ERR_ANB_DEV_COM_SET                -134    // ������Ƶ��������������ʧ��
#define ERR_ANB_DEV_MD_GET                -135    // ��ȡ��Ƶ�������ƶ��������ʧ��
#define ERR_ANB_DEV_MD_SET                -136    // ������Ƶ�������ƶ��������ʧ��
#define ERR_ANB_DEV_NET_GET                -137    // ��ȡ��Ƶ��������������ʧ��
#define ERR_ANB_DEV_NET_SET                -138    // ������Ƶ��������������ʧ��
#define ERR_ANB_DEV_WIFI_GET            -139    // ��ȡ��Ƶ����������WIFI����ʧ��
#define ERR_ANB_DEV_WIFI_SET            -140    // ������Ƶ����������WIFI����ʧ��
#define ERR_ANB_DEV_OSD_GET                -141    // ��ȡ��Ƶ������OSD����ʧ��
#define ERR_ANB_DEV_OSD_SET                -142    // ������Ƶ������OSD����ʧ��
#define ERR_ANB_DEV_DEFAULT                -143    // �ָ���Ƶ����������Ĭ��ֵʧ��
#define ERR_ANB_DEV_REBOOT                -144    // ������Ƶ�������豸ʧ��
#define ERR_ANB_DEV_RESET                -145    // ������Ƶ����������ʧ��
#define ERR_ANB_DEV_NAME_GET            -146    // ��ȡ��Ƶ�������豸����ʧ��
#define ERR_ANB_DEV_NAME_SET            -147    // ������Ƶ�������豸����ʧ��
#define ERR_ANB_DEV_VE_INFO_GET            -148    // ��ȡ��Ƶ��������ǰ������Ϣʧ��
#define ERR_ANB_DEV_VE_INFO_SET            -149    // ������Ƶ��������ǰ������Ϣʧ��
#define ERR_ANB_CHN_VE_INFO_GET            -150    // ��ȡ��Ƶ��������ǰͨ��������Ϣʧ��
#define ERR_ANB_DEV_PORT_GET            -151    // ��ȡ��Ƶ������ͨѶ�˿�ʧ��
#define ERR_ANB_DEV_PORT_SET            -152    // ������Ƶ������ͨѶ�˿�ʧ��
#define ERR_ANB_DEV_UPNP_GET            -153    // ��ȡ��Ƶ������UPNP״̬ʧ��
#define ERR_ANB_DEV_UPNP_SET            -154    // ������Ƶ������UPNP״̬ʧ��
#define ERR_ANB_DEV_PPPOE_GET            -155    // ��ȡ��Ƶ������PPPOE״̬ʧ��
#define ERR_ANB_DEV_PPPOE_SET            -156    // ������Ƶ������PPPOE״̬ʧ��
#define ERR_ANB_DEV_DDNS_GET            -157    // ��ȡ��Ƶ������DDNSʧ��
#define ERR_ANB_DEV_DDNS_SET            -158    // ������Ƶ������DDNSʧ��
#define ERR_ANB_DEV_NTP_GET                -159    // ��ȡ��Ƶ������NTPʧ��
#define ERR_ANB_DEV_NTP_SET                -160    // ������Ƶ������NTPʧ��
#define ERR_ANB_DEVIME_GET                -159    // ��ȡ��Ƶ������ʱ��ʧ��
#define ERR_ANB_DEVIME_SET                -160    // ������Ƶ������ʱ��ʧ��
#define ERR_ANB_DEVIMEZONE_SET            -161    // ������Ƶ������ʱ��ʧ��
#define ERR_ANB_DEV_VL_GET                -162    // ��ȡ��Ƶ��������Ƶ��ʧ����ʧ��
#define ERR_ANB_DEV_VL_SET                -163    // ������Ƶ��������Ƶ��ʧ����ʧ��
#define ERR_ANB_DEV_AUTHMODE_GET        -164    // ��ȡ��Ƶ�������û���֤����ʧ��
#define ERR_ANB_DEV_AUTHMODE_SET        -165    // ������Ƶ�������û���֤����ʧ��
#define ERR_ANB_DEV_USER_GET            -166    // ��ȡ��Ƶ�������û�ʧ��
#define ERR_ANB_DEV_USER_ADD            -167    // ����û�ʧ��
#define ERR_ANB_DEV_USER_SET            -168    // �޸��û�����ʧ��
#define ERR_ANB_DEV_USER_DEL            -169    // ɾ���û�ʧ��
#define ERR_ANB_DEV_UPDATE_PACKET        -170    // ������Ƶ��������ʧ��
#define ERR_ANB_DEV_SENSOR_IN_GET        -171    // ��ȡ��Ƶ������̽ͷ��������ʧ��
#define ERR_ANB_DEV_SENSOR_IN_SET        -172    // ������Ƶ������̽ͷ��������ʧ��
#define ERR_ANB_DEV_REC_STATUS_GET        -173    // ��ȡ��Ƶ������ǰ��¼��״̬����ʧ��
#define ERR_ANB_DEV_DISK_STRATEGY_GET    -174    // ��ȡ���̹������ʧ��
#define ERR_ANB_DEV_DISK_STRATEGY_SET    -175    // ���ô��̹������ʧ��
#define ERR_ANB_DEV_REC_START            -176    // ������Ƶ������ǰ��¼��ʧ��
#define ERR_ANB_DEVRACK_GET                -177    // ��ȡ��Ƶ�������켣����ʧ��
#define ERR_ANB_DEVRACK_SET                -178    // ������Ƶ�������켣����ʧ��
#define ERR_ANB_DEVRACK_CALL            -179    // ���ù켣ʧ��
#define ERR_ANB_DEV_SENDP09_CMD            -180    // ����͸���˿�ָ��ʧ��
#define ERR_ANB_DEV_AC_GET                -181    // ��ȡ��������������������ʧ��
#define ERR_ANB_DEV_AC_SET                -182    // ���ñ�������������������ʧ��
#define ERR_ANB_DEV_EMAIL_GET            -183    // ��ȡ���������ʼ�����ʧ��
#define ERR_ANB_DEV_EMAIL_SET            -184    // ���ñ��������ʼ�����ʧ��
#define ERR_ANB_DEV_FTP_GET                -185    // ��ȡ��������FTP����ʧ��
#define ERR_ANB_DEV_FTP_SET                -186    // ���ñ�������FTP����ʧ��
#define ERR_ANB_DEV_SENSOROUT_GET        -187    // ��ȡ��������̽ͷ�������ʧ��
#define ERR_ANB_DEV_SENSOROUT_SET        -188    // ���ñ�������̽ͷ�������ʧ��
#define ERR_ANB_DEV_REC_GET                -189    // ��ȡ��������¼������ʧ��
#define ERR_ANB_DEV_REC_SET                -190    // ���ñ�������¼������ʧ��
#define ERR_ANB_DEV_SENSORIN_CA_GET        -191    // ��ȡ̽ͷ���뱨����������ʧ��
#define ERR_ANB_DEV_SENSORIN_CA_SET        -192    // ����̽ͷ���뱨����������ʧ��
#define ERR_ANB_DEV_MD_CA_GET            -193    // ��ȡ�ƶ���ⱨ����������ʧ��
#define ERR_ANB_DEV_MD_CA_SET            -194    // �����ƶ���ⱨ����������ʧ��
#define ERR_ANB_DEV_VL_CA_GET            -195    // ��ȡ��Ƶ��ʧ������������ʧ��
#define ERR_ANB_DEV_VL_CA_SET            -196    // ������Ƶ��ʧ������������ʧ��
#define ERR_ANB_DEV_VOD_SEARCH_START    -197    // ��ʼ����ǰ��¼���ļ�ʧ��
#define ERR_ANB_DEV_VOD_SEARCH_STOP        -198    // ֹͣ����ǰ��¼���ļ�ʧ��
#define ERR_ANB_DEV_HS_GET                -199    // ��ȡHS�豸ע��������Ϣ
#define ERR_ANB_DEV_HS_SET                -200    // ����HS�豸ע��������Ϣ
#define ERR_ANB_MPEGPS_CALLBACK            -201    // ע��MPEG-PS�ص�����ʧ��
#define ERR_ANB_DEV_VM_GET                -202    // ��ȡ��Ƶ��������Ƶ�ڵ�����ʧ��
#define ERR_ANB_DEV_VM_SET                -203    // ������Ƶ��������Ƶ�ڵ�����ʧ��

#define ERR_ANB_GET_PRESETOUR           -210    //��ȡԤ��λѲ��ʧ��
#define ERR_ANB_SET_PRESETOUR           -211    //����Ԥ��λѲ��ʧ��
#define ERR_ANB_CALL_PRESETOUR          -212    //����Ԥ��λѲ��ʧ��
#define ERR_ANB_PLAYBACK                -213    //Զ�̻ط�ʧ��

    
#define ERR_ANB_CONTROL_PROTOCOL        -400    // 

#endif

