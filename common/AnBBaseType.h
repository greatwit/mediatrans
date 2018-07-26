/****************************************************************************************
 *Copyrights  2014£¨…Ó€⁄∞≤∞Óø∆ºº”–œﬁπ´Àæ
 *All rights reserved.
 *
 * Filename£∫ AnBBaseType.h
 * Indentifier£∫
 * Description£∫SDKƒ⁄≤øÕ®–≈Ω”ø⁄∂®“Â
 * Version£∫V1.0
 * Author:       dengyongjun
 * Finished£∫    2014ƒÍ08‘¬27»’
 * History:
 ******************************************************************************************/

#ifndef		_ANB_BASETYPE_H_
#define		_ANB_BASETYPE_H_




#ifdef WIN32
#define socklen    int
#define close        closesocket
#define strcasecmp    stricmp
#define HNPACKED
#define snprintf    _snprintf
#else
#define HNPACKED        __attribute__((packed, aligned(1)))
#endif

#define ANB_PROT_DATA_LEN       10*1024
#define MAX_NET_MSG_LEN         10*1024


#if defined( _WINDLL)
#define DLL_API  extern "C" __declspec(dllexport)
#elif defined(WIN32)
//#define DLL_API  extern "C" __declspec(dllimport)
#else
#define DLL_API
typedef     unsigned short  WORD;
//typedef     int             LONG;
//typedef     unsigned int    DWORD;
typedef     unsigned int*   LPDWORD;
typedef     char            CHAR;
typedef     int             BOOL;
typedef     unsigned short  USHORT;
typedef     unsigned char   BYTE ;
typedef     unsigned int    UINT;
typedef     void*           LPVOID;
typedef     void*           PVOID;
typedef     void*           HANDLE;
typedef     unsigned long   U32;
typedef     unsigned long long UINT64;
typedef     short           SHORT;
#endif

typedef     void*            ANB_HAND;

#ifndef    TRUE
#define    TRUE     1
#endif
#ifndef    FALSE
#define    FALSE    0
#endif
#ifndef    NULL
#define    NULL     0
#endif

#ifndef    RET_SUCCESS
#define    RET_SUCCESS 0
#endif

#ifndef    RET_FAILED
#define    RET_FAILED -1
#endif

#ifndef __HWND_defined
#define __HWND_defined
#if defined(__linux__) || defined(IOS)
typedef unsigned int HWND;
#else
//typedef void* HWND;
#endif

#endif

typedef unsigned int HWND;

//∏ÊÀﬂ±‡“Î∆˜»°œ˚Ω·ππ‘⁄±‡“Îπ˝≥Ã÷–µƒ”≈ªØ∂‘∆Î,∞¥’’ µº ’º”√◊÷Ω⁄ ˝Ω¯––∂‘∆Î£¨ «GCCÃÿ”–µƒ”Ô∑®
#ifdef WIN32
#pragma  pack(push,1)
#define PACKED
#else
#pragma  pack(push,1)
#define PACKED  __attribute__ ((packed))
#endif

#define     MAX_PTZ_NAME            20              //‘§÷√µ„√˚≥∆◊Ó¥Û≥§∂»
#define     MAX_PRESET              256             //◊Ó¥Û‘§÷√µ„ ˝
#define     MAXOUR                  32              //◊Ó¥Û—≤∫Ω◊È
#define     MAX_LAMP                16              //µ∆øÿ÷∏¡Ó◊Ó¥Û≥§∂»
#define     MAX_PRESET_PROT         16              //‘§÷√µ„œﬁŒªµ„◊Ó¥Û≥§∂»
#define     MAX_COVER_AREA          32              // ”∆µ’⁄µ≤«¯”Ú◊Ó¥Û≥§∂»
#define     MAX_IPV6_LEN            16              //IPV6Ω·ππ◊Ó¥Û≥§∂»
#define     MAC_IP_MAC              6               //MACµÿ÷∑◊Ó¥Û≥§∂»
#define     MAX_SSID_LEN            32              //SSID◊Ó¥Û≥§∂»
#define     MAX_PSK_PWD_LEN         32              //PSK√‹¬Î◊Ó¥Û≥§∂»
#define     MAX_INTEGER_LEN         255             //◊Ó¥Û’˚–Õ≥§∂»
#define     MAX_3G_NAME_LEN         64              //3Gø®”√ªß√˚◊Ó¥Û≥§∂»
#define     MAX_DDSN_LEN            64              //DDSN√˚≥∆∫Õ√‹¬Î◊Ó¥Û≥§∂»
#define     MAX_FTP_URL_LEN         64              //FTPµƒ∑˛ŒÒ∆˜◊Ó¥ÛURL≥§∂»
#define     MAX_NAME_LEN            16              //”√ªß√˚◊Ó¥Û≥§∂»
#define     MAX_PSW_LEN             16              //√‹¬Î◊Ó¥Û≥§∂»
#define     MAX_FTP_DIR_LEN         128             //FTPƒø¬º¬∑æ∂√˚◊Ó¥Û≥§∂»

#define     ANB_SERVER_NUMBER       20              //µ«¬Ω∑µªÿ◊Ó¥Û∑˛ŒÒ∆˜ ˝ƒø
#define     ANB_GROUP_NUMBER        20              //◊È¡–±Ì≥…‘±◊Ó¥Û£¨‘›∂®20∏ˆ

#define     ANB_IP_LEN                  32          //IP◊Ó¥Û≥§∂»
#define     ANB_USERNAME_LEN            32          //◊Ó¥Û”√ªß√˚≥§∂»
#define     ANB_PASSWD_LEN              32          //◊Ó¥Û√‹¬Î≥§∂»
#define     ANB_ID_LEN                  32          //ID◊Ó¥Û≥§∂»
#define     ANB_LENS_NAME               64          //æµÕ∑√˚≥∆
#define     ANB_GROUP_NAME              64          //æµÕ∑√˚≥∆
#define     MAX_LENS_LIST_LEN           256         //◊Ó¥ÛæµÕ∑ ˝
#define     MAX_PATH_LEN                100         //◊Ó¥Û¬∑æ∂◊÷∑˚¥Æ≥§∂»
#define     MAX_RECORD_SERVER_COUNT     20          //¥Ê¥¢∑˛ŒÒ∆˜◊Ó¥Û ˝¡ø
#define     MAX_QUERY_RECORD_RELUST     20          //¥Ê¥¢≤È—Ø◊Ó¥Û∑µªÿ ˝¡ø
#define     MAX_GET_LENS_GOURP_COUNT    40          //ªÒ»°æµÕ∑◊È√˚≥∆◊Ó¥Û ˝¡ø

//∏ÊæØƒ£øÈ∫Í∂®“Â
#define     ANB_OBJID_LEN               32            //∂‘œÛID±Í ∂≥§∂»
#define     ANB_LINKTYPE_MAX            32            //¡™∂Ø¿‡–Õ◊Ó¥Û ˝ƒø
#define     ANBITLENAME_LEN             32            //√˚≥∆ªÚ’ﬂ±ÍÃ‚◊Ó¥Û◊÷∑˚≥§∂»
#define     ANB_SEQUENCE_LEN            32            //≈…µ•¡˜ÀÆ∫≈◊Ó¥Û◊÷∑˚≥§∂»
#define     ANB_PROMPT_LEN              128            //≈…µ•Ã· æ–≈œ¢◊Ó¥Û◊÷∑˚≥§∂»
#define     ANB_CONTEXT_LEN             128            //≈…µ•ªÿ∏¥ƒ⁄»›◊Ó¥Û◊÷∑˚≥§∂»
#define     ANB_LINKOBJ_MAX             32            //“ª∏ˆ±®æØ∂‘œÛµƒ“ª∏ˆ±®æØ¿‡–Õƒ‹—°‘Ò¡™∂Ø∂‘œÛµƒ◊Ó¥Û∏ˆ ˝
#define     ANB_SEQPAGE_MAX_SIZE        100            //∂‘≈…µ•Ω¯––∑÷“≥≤È—Ø ±£¨“ª“≥µƒ◊Ó¥Û‘™Àÿ∏ˆ ˝


//Õ¯¬Áø‚SDKµ«¬Ω–≈œ¢
typedef struct
{
    CHAR        szIP[ANB_IP_LEN];                        //÷––ƒ∑˛ŒÒ∆˜IPµÿ÷∑
    WORD        wPort;                                   //÷––ƒ∑˛ŒÒ∆˜∂Àø⁄∫≈
    CHAR        sUserName[ANB_USERNAME_LEN];             //µ«¬ºµƒ”√ªß√˚
    CHAR        sPassword[ANB_PASSWD_LEN];               //√‹¬Î
}PACKED ANB_LOGININFO,*LPANB_LOGININFO;

typedef enum
{
    ANB_CLIENT  = 0,                                     //øÕªß∂À
    ANB_CENTER_SERVER ,                                 //÷––ƒ∑˛ŒÒ∆˜
    ANB_MEDIA_SERVER,                                   //¡˜√ΩÃÂ∑˛ŒÒ∆˜
    ANB_RECORD_SERVER,                                  //¥Ê¥¢∑˛ŒÒ∆˜
    ANB_ALARM_SERVER,                                   //∏ÊæØ∑˛ŒÒ∆˜
    ANB_UNIFORM_ACC_SERVER,                             //Õ≥“ªΩ”»Î
    ANB_LOG_SERVER,                                     //»’÷æ∑˛ŒÒ∆˜
    ANB_DATABASE_AGENT_SERVER,                          // ˝æ›ø‚¥˙¿Ì∑˛ŒÒ∆˜
    
    MAX_SERVER_NUMBER                                   //◊Ó¥Û∑˛ŒÒ∆˜ ˝ƒø
}ANB_SERVERYPE;

typedef enum
{
    ANB_REAL_PLAY = 1,                                  // µ ±≤•∑≈
    ANB_PALY_BACK
}ANB_PLAY_TYPE;

//∑˛ŒÒ∆˜–≈œ¢
typedef struct
{
    char            szID[ANB_ID_LEN];                   //∑˛ŒÒ∆˜ID
    char            szIP[ANB_IP_LEN];                   //∑˛ŒÒ∆˜IP
    WORD            wPort;                              //∑˛ŒÒ∆˜∂Àø⁄
    WORD            wRtspPort;                          //RTSP∂Àø⁄
    ANB_SERVERYPE        eTYPE;                         //∑˛ŒÒ∆˜¿‡–Õ
}PACKED ANB_SERVERINFO,*LPANB_SERVERINFO;

//µ«¬Ω∑˛ŒÒ∆˜¡–±Ì
typedef struct
{
    char             szUserID[ANB_ID_LEN];              //”√ªßID
    LONG             lServerNum;                        //∑˛ŒÒ∆˜ ˝ƒø
    ANB_SERVERINFO   ServerInfo[ANB_SERVER_NUMBER];     //∑˛ŒÒ∆˜¡–±Ì
}PACKED ANB_LOGINSERVER,*LPANB_LOGINSERVER;

//÷––ƒ∑˛ŒÒ∆˜∫Õ∆‰À˚∑˛ŒÒ∆˜handle”≥…‰πÿœµ
typedef struct
{
    LONG            lHandle;                            //¡¨Ω”æ‰±˙
    ANB_SERVERYPE   eTYPE;                              //∑˛ŒÒ∆˜¿‡–Õ
    char            szID[ANB_ID_LEN];                   //∑˛ŒÒ∆˜ID
}PACKED ANB_LoginHandle,*LPANB_LoginHandle;

//◊È∂®“Â
typedef struct
{
    CHAR             szGroupID[ANB_ID_LEN];             //◊È±Í ∂
    CHAR             szGroupName[ANB_GROUP_NAME];       //◊È√˚
    CHAR             szParentID[ANB_ID_LEN];            //∏∏Ω⁄µ„±Í ∂
}PACKED ANB_GROUP,*LPANB_GROUP;

//◊È¡–±Ì
typedef struct
{
    LONG            lGroupNum;                          //◊ÈΩ⁄µ„ ˝ƒø
    ANB_GROUP       GroupList[ANB_GROUP_NUMBER];        //◊ÈΩ⁄µ„¡–±Ì
}PACKED ANB_GROUPLIST,*LPANB_GROUPLIST;

//æµÕ∑–≈œ¢±Ì
typedef struct
{
    CHAR        szChannelID[ANB_ID_LEN];                    //Õ®µ¿±Í ∂
    CHAR        szChannelName[ANB_LENS_NAME];               //Õ®µ¿√˚≥∆
    CHAR        szHostID[ANB_ID_LEN];                       // ”∆µ÷˜ª˙±Í ∂
    CHAR        szGroupID[ANB_ID_LEN];                      //◊È±Í ∂
    BOOL        IsPTZ;                                      //‘∆Ã®±Í÷æ 0:Œﬁ‘∆Ã® 1:”–‘∆Ã®
}PACKED ANB_LENSINFO,*LPANB_LENSINFO;

//æµÕ∑–≈œ¢¡–±Ì
typedef struct
{
    LONG            lLensNum;                               //æµÕ∑ ˝ƒø
    ANB_LENSINFO    LensInfoList[MAX_LENS_LIST_LEN];        //æµÕ∑–≈œ¢¡–±Ì
}PACKED ANB_LENSINFOLIST,*LPANB_LENSINFOLIST;




// ‘§÷√ŒªΩ·ππ
typedef struct
{
    UINT        nPresetID;                                // ‘§÷√Œªµ„
    char        szPresetName[MAX_PRESET_PROT];            // ‘§÷√Œª√˚≥∆,◊Ó¥Û÷ß≥÷10∏ˆ◊÷∑˚
    UINT        nStayTime;                                // Õ£¡Ù ±º‰
}PACKED ANB_PRESETINFO;

// ‘§÷√ŒªΩ·ππ ˝◊È
typedef struct
{
    LONG                nPresetCount;                   //‘§÷√Œª ˝ƒø
    ANB_PRESETINFO        PresetInfo[MAX_PRESET];         //‘§÷√Œª–≈œ¢¡–±Ì
}PACKED ANB_PRESETINFOLIST,*LPANB_PRESETINFOLIST;


//ø¥ ÿŒª–≈œ¢
typedef struct
{
    BOOL bGuarderEnable;                                // «∑Ò∆Ù”√ø¥ ÿŒª(1Œ™∆Ù”√/0Œªπÿ±’)
    LONG nGuarderTime;                                  //πÈø¥ ÿŒª ±º‰º‰∏Ù(1 ~~ 300 ∑÷÷”)
    LONG nGuarderPreset;                                //ø¥ ÿŒª∂‘”¶µƒ‘§÷√Œª(1 ~~ 256)
}PACKED ANB_GUARDERINFO,*LPANB_GUARDERINFO;


//…´≤ Ω·ππ
typedef struct
{
    long lBrightness ;                                  //¡¡∂»
    long lContrast ;                                    //∂‘±»∂»
    long lSaturation;                                   //±•∫Õ∂»
    long lHue;                                          //…´∂»
}PACKED ANB_VIDEOCOLOR,*LPANB_VIDEOCOLOR;


// ±º‰Õ¨≤Ω∑Ω Ω
typedef enum
{
    SYN_CLOCK_MANUAL=0,                                 // ÷∂ØÕ¨≤Ω ±º‰
    SYN_CLOCK_NET                                       //NTP∑˛ŒÒ∆˜ ±º‰Õ¨≤Ω
}ANB_SYN_CLOCKYPE;

//NTP∑˛ŒÒ∆˜–≈œ¢
typedef struct
{
    CHAR szNtpServerIP[ANB_IP_LEN];                     //NTP∑˛ŒÒ∆˜IP
    LONG lNtpPort;                                      //NTP∑˛ŒÒ∆˜∂Àø⁄
    LONG lSynTimeInterval;                              // ±º‰Õ¨≤Ωº‰∏Ù(µ•Œª:∑÷÷”)
}PACKED ANB_NTPSERVER_INFO,*LPANB_NTPSERVER_INFO;

typedef struct
{
    LONG    lTime;                                      //µ±«∞ ±º‰
    LONG    lTimeZone;                                  //µ±«∞ ±«¯
}PACKED ANBIME_INFO,*LPANBIME_INFO;

typedef struct
{
    ANB_SYN_CLOCKYPE    emClockType;                  // «NET∑˛ŒÒ∆˜
    ANB_NTPSERVER_INFO    NTPServerInfo;                //NTP∑˛ŒÒ∆˜–≈œ¢
    ANBIME_INFO         TimeInfo;                     //µ±«∞ ±º‰–≈œ¢
}PACKED ANBIMEINFO,*LPANBIMEINFO;


typedef enum _LOAD_STATUS
{
    LOAD_ERROR = 1,                                     //load ¥ÌŒÛ
    LOAD_START,                                         //load ø™ º
    LOAD_ING,                                           //load Ω¯––÷–
    LOAD_PAUSE,                                         //load ‘›Õ£
    LOAD_FINISHED,                                      //load ÕÍ≥…
}LOAD_STATUS;

typedef struct _LOAD_SCHEDULE_DATA
{
    long            lNextSectionNO;                     //œ¬“ª∏ˆ∆¨∂Œ±‡∫≈[0, sectioncount]
    unsigned int    uiSendedFrameCount;                 //“—∑¢ÀÕ÷° ˝
    unsigned int    uiSendedStreamSize;                 //“—∑¢ÀÕ ˝æ›¥Û–°£®µ•Œª£∫«ß◊÷Ω⁄£©
    unsigned int    uiNextSecStartTM;                   //œ¬“ª∏ˆ∆¨∂Œµƒµ⁄“ª÷°µƒ ±º‰¥¡£¨ªÿ∑≈Ω· ¯ ±ÃÓ0
    LOAD_STATUS     loadStatus;                         //◊¥Ã¨
}STRUCT_LOAD_SCHEDULE_DATA, *LPSTRUCT_LOAD_SCHEDULE_DATA;



/**************¡˜√ΩÃÂ÷°∑÷∞¸Õ∑Ω·ππÃÂ**********************************************************/
typedef struct
{
    DWORD   FrameID;                                    // ”∆µ÷°–Ú∫≈
    DWORD   FrameLen;                                   // ”∆µ÷°≥§∂»
    BYTE     IsKeyFrame;                                // «∑ÒŒ™πÿº¸÷°£¨«∞∂À÷˜∂ØΩ· ¯√ΩÃÂ¡˜ ±£¨∑¢ÀÕ0xFF
    BYTE     PackID;                                    // ”∆µ÷°÷–∑÷∞¸µƒ∞¸–Ú∫≈£¨–Ú∫≈¥”0ø™ º±‡∫≈°£
    BYTE     PackCount;                                 // ”∆µ÷°÷–∑÷∞¸∏ˆ ˝
    BYTE     Verify;                                    // ˝æ›–£—È¬Î
    WORD    PackDataLen;                                //∑÷∞¸ ˝æ›≥§∂»
}PACKED ANB_PACKHEARD, *LPANB_PACKHEARD;

/**************¡˜√ΩÃÂ–≠“ÈÕ∑Ω·ππÃÂ**********************************************************/
typedef struct
{
    WORD   ProtocolVersion;                             //–≠“È∞Ê±æ
    WORD   VideoFormat;                                 // ”∆µ∏Ò Ω
    //(÷°¥Û–°(≤ª∞¸¿®±æÕ∑≤ø£¨∞¸¿®¡˜√ΩÃÂ÷°Õ∑º∞√ΩÃÂ ˝æ›£¨’‚¿Ô∏√◊÷∂Œ∂®“ÂŒ™2◊÷Ω⁄≥§£¨
    //øº¬À÷°≥§∂»ø…ƒ‹¥Û”⁄65535£¨À˘“‘’‚¿Ô≤ª”√∏√◊÷∂Œ£¨÷±Ω””√¡˜√ΩÃÂ∞¸Õ∑÷–µƒ÷°µƒ≥§∂»)°£)
    WORD    FrameLength;                                //÷°¥Û–°
    DWORD  Sequence;                                    // ”∆µ÷°–Ú∫≈
}PACKED ANB_PROTOCOLHEARD, *LPANB_PROTOCOLHEARD;

// ÷ª˙øÕªß∂ÀÕ®π˝÷––ƒ∑˛ŒÒ∆˜ªÒ»°æµÕ∑¡–±Ì
typedef struct
{
    CHAR    szUserID[ANB_ID_LEN];
}PACKED ANB_GetLensGroupListReq,*LPANB_GetLensGroupListReq;

typedef struct
{
    CHAR    szLensGroupID[ANB_ID_LEN];
    CHAR    szLensGroupName[ANB_GROUP_NAME];
}PACKED ANB_LensGroupInfo,*LPANB_LensGroupInfo;

typedef struct
{
    long lLensGroupListCount;
    ANB_LensGroupInfo LensGroupInfo[MAX_GET_LENS_GOURP_COUNT];
}PACKED ANB_GetLensGroupListRsp,*LPANB_GetLensGroupListRsp;

//∏˘æ›æµÕ∑◊ÈIDªÒ»°æµÕ∑¡–±Ì
typedef struct
{
    CHAR    szLensGroupID[ANB_ID_LEN];
}PACKED ANB_GetLensListReq,*LPGetLensListReq;

typedef struct
{
    CHAR    szLenID[ANB_ID_LEN];
    CHAR    szLensName[ANB_LENS_NAME];
    CHAR    szNvrID[ANB_ID_LEN];
}PACKED ANB_LensInfo,*LPANB_LensInfo;

typedef struct
{
    long lLensGroupListCount;
    ANB_LensInfo LensInfo[MAX_GET_LENS_GOURP_COUNT];
}PACKED ANB_GetLensListRsp,*LPANB_GetLensListRsp;

/**************¡˜√ΩÃÂ÷°Õ∑Ω·ππÃÂ**********************************************************/
typedef struct
{
    WORD   ImageWidth;                                  // ”∆µ÷°øÌ∂»
    WORD    ImageHeight;                                // ”∆µ÷°∏ﬂ∂»
    WORD    VideoFormat;                                // ”∆µ∏Ò Ω
    WORD    Motion;                                     //±£¡Ù£¨ÃÓ≥‰ASCII 0
    DWORD   Id;                                         //±£¡Ù£¨ÃÓ≥‰ADCII 0
    DWORD   VideoSize;                                  // ”∆µ÷° ˝æ›≥§∂»(÷°÷–æª ”∆µ ˝æ›≥§∂»)
    DWORD   TimerTick;                                  // ”∆µ÷° ±º‰¥¡(∫¡√Î£¨¡¨–¯ ±º‰£¨µ´≤ª“™«Û√ø¥Œª·ª∞µƒµ⁄“ªËÂ“ª∂®¥”0ø™ ºº∆ ˝))
    WORD   AudioSize;                                   //“Ù∆µ÷° ˝æ›≥§∂»(÷°÷–æª“Ù∆µ ˝æ›≥§∂»£¨ΩÙ∏˙ ”∆µ ˝æ›£¨‘›Œ¥ π”√)
    BYTE     IsKeyFrame;                                // «∑ÒŒ™πÿº¸÷°
    BYTE     VoIHead;                                   //±£¡Ù£¨ÃÓ≥‰ASCII 0
}PACKED ANB_FRAMEHEARD, *LPANB_FRAMEHEARD;


/**************¡˜√ΩÃÂ∞¸Ω·ππÃÂ**********************************************************/
typedef struct
{
    ANB_PACKHEARD                  *PacketHeard;           //∑÷∞¸Õ∑
    ANB_PROTOCOLHEARD         *ProtocolHead;              //–≠“ÈÕ∑
    ANB_FRAMEHEARD              *FrameHead;             //÷°Õ∑
    BYTE                        *pBuffer;               // ˝æ›ª∫≥Â«¯
}PACKED ANB_STREAMPACKET, *LPANB_STREAMPACKET;

/*
  ˝æ›¿‡–Õ±Ì nType
  ˝æ›¿‡–Õ        ºÚ–¥                        Àµ√˜
 1            CODEC_ID_H264                H264 ”∆µ±‡¬Î ˝æ›
 2            CODEC_ID_MPEG4                MPEG4 ”∆µ±‡¬Î ˝æ›
 3            CODEC_ID_MJPEG                MJPEG ”∆µ±‡¬Î ˝æ›
 10            CODEC_ID_PCM_MULAW            MULAW“Ù∆µ±‡¬Î
 11            CODEC_ID_AMR                AMR“Ù∆µ±‡¬Î
 */
#ifndef _RAW_INFO_
#define _RAW_INFO_
typedef struct
{
    long        nWidth;                // ª≠√ÊøÌ£¨µ•ŒªŒ™œÒÀÿ£¨»Áπ˚ «“Ù∆µ ˝æ›‘ÚŒ™0
    long        nHeight;            // ª≠√Ê∏ﬂ£¨µ•ŒªŒ™œÒÀÿ£¨»Áπ˚ «“Ù∆µ ˝æ›‘ÚŒ™0
    long        nStamp;                //  ±±Í–≈œ¢£¨µ•Œª∫¡√Î
    long        nType;                //  ˝æ›¿‡–Õ  ”∆µ:1 h264 2 mpeg 3 mjpeg “Ù∆µ:11 amr 10 ∆‰À˚
    long        nVideoIFrame;        // µ±«∞÷° «∑ÒŒ™ ”∆µI÷°(1. ∏√≤Œ ˝÷ª”–‘⁄nTypeŒ™ ”∆µ¿‡–Õ ±”––ß 2. ∑«0Œ™I÷°,∑Ò‘ÚŒ™P÷°,ŒﬁB÷°)
    long        nFrameRate;            // ±‡¬Î ±≤˙…˙µƒÕºœÒ÷°¬
}RAW_INFO;
#endif

//Õ¯¬Á√¸¡Ó
typedef struct
{
    int            len;
    char        buf[MAX_NET_MSG_LEN];
}ANB_NETMGR_CMDBUF,*LPANB_NETMGR_CMDBUF;

//typedef map<int, ANB_NETMGR_CMDBUF> ANB_NETMGR_CMDLIST;

//Õ¯¬Áœ˚œ¢Õ∑
//ƒø±ÍID øÕªß∂Àƒ¨»œ∑¢ÀÕµΩ÷––ƒ∑˛ŒÒ∆˜ «0£¨÷––ƒ∑˛ŒÒ∆˜Ω¯––◊™∑¢ ±…Ë÷√µƒsocketID,∑µªÿ–≈œ¢ ±–Ë“™∞—’‚∏ˆ◊÷∂Œ‘≠—˘∑µªÿ
typedef struct _ANB_PROT_HEAD
{
    BYTE    head[4];    //$AB$
    BYTE    vers1;        //÷˜∞Ê±æ∫≈
    BYTE    vers2;        //¥Œ∞Ê±æ∫≈
    WORD    cmd;        //≤Ÿ◊˜÷∏¡Ó
    DWORD    ssrc;        //ª·ª∞∫≈   ”¶¥œ˚œ¢–Ë“™‘≠—˘∑µªÿ
    DWORD    dstid;        //ƒø±ÍID
    short    code;        //¥ÌŒÛ¬Î
    WORD    len;        // ˝æ›≥§∂»
    
}PACKED ANB_PROT_HEAD,*LPANB_PROT_HEAD;

//Õ¯¬Áœ˚œ¢
typedef struct _ANB_NETMSG
{
    ANB_PROT_HEAD    head;
    char            buf[ANB_PROT_DATA_LEN];
    
}PACKED ANB_NETMSG,*LPANB_NETMSG;


//µ«¬Ω–≈œ¢
//ANB_CMD_CENTER_LOGIN_REQ                            = 0x1001,               //øÕªß∂Àµ«¬Ω÷––ƒ∑˛ŒÒ∆˜«Î«Û
typedef struct
{
    int  nType;                             //ANB_SERVERYPE
    char szServerID[ANB_ID_LEN];            //∑˛ŒÒ∆˜ID,øÕªß∂À «USERID
    char szUserName[ANB_USERNAME_LEN];      //”√ªß√˚
    char szPassword[ANB_PASSWD_LEN];        //”√ªß√‹¬Î
}PACKED ANB_LOGINMSG,*LPANB_LOGINMSG;


//ªÒ»°Õ≥“ªΩ”»Î∑˛ŒÒ∆˜æµÕ∑¡–±Ì
typedef struct
{
    char szServerID[ANB_ID_LEN];
}PACKED ANB_SERVERID,*LPANB_SERVERID;

//æµÕ∑ID¡–±Ì
typedef struct
{
    char szLensID[ANB_ID_LEN];
}PACKED ANB_LENSID,*LPANB_LENSID;


//æµÕ∑ID¡–±Ì
typedef struct
{
    int  nState;
    char szLensID[ANB_ID_LEN];
}PACKED ANB_LENSINFOSTATE,*LPANB_LENSINFOSTATE;

//æµÕ∑¡–±Ì
//ANB_CMD_CENTER_GETOTAL_LENS_LIST_REQ              = 0x1005,               //ªÒ»°Õ≥“ªΩ”»Î∑˛ŒÒ∆˜æµÕ∑¡–±Ì«Î«Û
typedef struct
{
    int                 number;
    ANB_LENSINFOSTATE   lensIDList[MAX_LENS_LIST_LEN];
}PACKED ANB_LENSIDLIST,*LPANB_LENSIDLIST;

//ANB_CMD_CENTER_GET_MEDIA_INFO_RSP                   = 0x100A,               //ªÒ»°IPC∂‘”¶µƒ¡˜√ΩÃÂ◊™∑¢∑˛ŒÒ∆˜–≈œ¢”¶¥
typedef struct
{
    ANB_SERVERINFO  MediaServer;                    //¡˜√ΩÃÂ∑˛ŒÒ∆˜
    ANB_SERVERINFO  UniformAccServer;               //Ω”»Î∑˛ŒÒ∆˜
}PACKED ANB_MEDIA_UNIFORMACC_SERVER,*LPANB_MEDIA_UNIFORMACC_SERVER;

typedef enum                                         // ¡¨Ω”…Ë±∏Õ¯¬Á¿‡–Õ
{
    ANB_Connect_Unknown    = -1,
    ANB_Connectcp        = 0,
    ANB_Connect_Udp        = 1,
    ANB_Connect_Mudp    = 2,
    ANB_Connect_Rtp     = 3
}ANB_CONNECTYPE;

typedef enum                                        //¬Î¡˜¿‡–Õ
{
    ANB_STREAM_FIRST    = 1,                            //÷˜¬Î¡˜
    ANB_STREAM_SECOND   = 2,                            //¥Œ¬Î¡˜
    ANB_STREAMHREE    = 3                             //»˝¬Î¡˜
}ANB_STREAMYPE;

typedef struct
{
    char szIPCID[ANB_ID_LEN];                   //IPCID
    char szUniformAccID[ANB_ID_LEN];            //Õ≥“ªΩ”»Î∑˛ŒÒ∆˜ID
    char szIP[ANB_IP_LEN];                      //¡˜√ΩÃÂ∑˛ŒÒ∆˜IP
    char szUserName[ANB_USERNAME_LEN];          //¡˜√ΩÃÂ∑˛ŒÒ∆˜”√ªß√˚
    char szPassword[ANB_PASSWD_LEN];            //¡˜√ΩÃÂ∑˛ŒÒ∆˜√‹¬Î
    int  nPort;                                 //¡˜√ΩÃÂ∂Àø⁄
    HWND            hWndVideo;                    // œ‘ æ ”∆µ¥∞ø⁄æ‰±˙
    ANB_STREAMYPE   emStreamType;             //¡˜¿‡–Õ
    ANB_CONNECTYPE  emConnType;               //¡¨Ω”¿‡–Õ
    
}PACKED ANB_PREVIEW,*LPANB_PREVIEW;

//云台操作
typedef struct
{
    DWORD    dwPTZCommand;
    DWORD    dwSpeed;
}PACKED ANB_PTZCTRLPARA;

//云台操作
//ANB_CMD_UNIFORM_PTZ_CONTROL_REQ                     = 0x3005,               //客户端操作云台请求
typedef struct
{
    ANB_LENSID      lensID;                         //镜头ID
    ANB_PTZCTRLPARA PTZCtrlPara;                    //云台参数
}ANB_PTZCONTROL_INFO,*LPANB_PTZCONTROL_INFO;


// 视频云台控制参数枚举
enum VideoPtzCommand
{
    
    /// <summary>
    /// 云台停止
    /// </summary>
    CameraStop = 0x1001,
    /// <summary>
    /// 云台上仰
    /// </summary>
    CameraUp = 0x1002,
    /// <summary>
    /// 云台下俯
    /// </summary>
    CameraDown = 0x1003,
    
    /// <summary>
    /// 云台左转
    /// </summary>
    CameraLeft = 0x1004,
    
    /// <summary>
    /// 云台左上
    /// </summary>
    CameraLeftUp = 0x1005,
    /// <summary>
    /// 云台左下
    /// </summary>
    CameraLeftDown = 0x1006,
    /// <summary>
    /// 云台右转
    /// </summary>
    CameraRight = 0x1007,
    /// <summary>
    /// 云台右转
    /// </summary>
    CameraRightUp = 0x1008,
    /// <summary>
    /// 云台右转
    /// </summary>
    CameraRightDown = 0x1009,
    /// <summary>
    /// 云台自动
    /// </summary>
    CameraAuto = 0x100A,
    
    /// <summary>
    /// 设置预知位
    /// </summary>
    SetForeknowledgePlace = 0x100B,
    
    /// <summary>
    /// 清除预知位
    /// </summary>
    ClearForeknowledgePlace = 0x100C,
    
    /// <summary>
    /// 转到预知位
    /// </summary>
    GotoForeknowledgePlace = 0x100D,
    
    /// <summary>
    /// 模式设置开始
    /// </summary>
    ModeSetStart = 0x100E,
    /// <summary>
    /// 模式设置停止
    /// </summary>
    ModeSetStop = 0x100F,
    /// <summary>
    /// 模式运行
    /// </summary>
    ModeSetSun = 0x1010,
    
    /// <summary>
    /// 打开镜头菜单
    /// </summary>
    MenuOpen = 0x1011,
    /// <summary>
    /// 关闭镜头菜单
    /// </summary>
    MenuExit = 0x1012,
    /// <summary>
    /// 进入镜头菜单
    /// </summary>
    MenuEnter = 0x1013,
    
    /// <summary>
    /// 云台翻转度
    /// </summary>
    CameraPTZLiip = 0x1014,
    /// <summary>
    /// 云台转至起始位
    /// </summary>
    CameraPTZStart = 0x1015,
    
    /// <summary>
    /// 光圈扩大
    /// </summary>
    LightRingEnlarge = 0x2001,
    
    /// <summary>
    /// 光圈缩小
    /// </summary>
    LightRingLessen = 0x2002,
    /// <summary>
    /// 焦距变大(倍率变大)
    /// </summary>
    FocalEnlarge = 0x2003,
    
    /// <summary>
    /// 缩小焦距
    /// </summary>
    FocalLessen = 0x2004,
    
    /// <summary>
    /// 焦点前调
    /// </summary>
    FocusForthcome = 0x2005,
    
    /// <summary>
    /// 焦点后调
    /// </summary>
    Focusback = 0x2006,
    
    
    
    ///// <summary>
    ///// 开自动焦距(自动倍率)
    ///// </summary>
    //AutoFocal = 17,
    
    
    ///// <summary>
    ///// 开自动调焦
    ///// </summary>
    //AutoFocus = 18,
    
    ///// <summary>
    ///// 自动光圈
    ///// </summary>
    //AutoLightRing = 19,
    
    
    
    ///* 镜头控制，包括光圈、缩放、聚焦*/
    //#define NSS_DEVICE_CONTROL_LENS_APERTURE_OPEN           	0x2001  /* 光圈*/
    //#define NSS_DEVICE_CONTROL_LENS_APERTURE_CLOSE          	0x2002
    //#define NSS_DEVICE_CONTROL_LENS_ZOOM_IN                     0x2003  /* Updated : 2004-6-10 */
    //#define NSS_DEVICE_CONTROL_LENS_ZOOM_OUT                    0x2004
    //#define NSS_DEVICE_CONTROL_LENS_FOCAL_NEAR                  0x2005
    //#define NSS_DEVICE_CONTROL_LENS_FOCAL_FAR                   0x2006
    //             */
};

//‘§÷√Œª–≈œ¢
//ANB_CMD_UNIFORM_ADD_PRESET_REQ                      = 0x3007,               //ÃÌº”‘§÷√Œª«Î«Û
typedef struct
{
    ANB_LENSID          lensID;                         //æµÕ∑ID
    ANB_PRESETINFO      presetInfo;                     //‘§÷√Œª–≈œ¢
}PACKED ANB_PRESET_INFO,*LPANB_PRESET_INFO;

//µ˜”√‘§÷√Œª
//ANB_CMD_UNIFORM_DEL_PRESET_REQ                      = 0x3009,               //…æ≥˝‘§÷√Œª«Î«Û
//ANB_CMD_UNIFORM_CALL_PRESET_REQ                     = 0x300D,               //µ˜”√‘§÷√Œª«Î«Û
typedef struct
{
    ANB_LENSID          lensID;                         //æµÕ∑ID
    UINT                lPresetID;                      //‘§÷√ŒªID
}PACKED ANB_PRESET_IPCID,*LPANB_PRESET_IPCID;

//ANB_CMD_UNIFORM_GET_PRESETOUR_REQ                 = 0x3013,               //ªÒ»°—≤∫Ω«Î«Û
//ANB_CMD_UNIFORM_CALL_PRESETOUR_REQ                = 0x3015,               //µ˜”√—≤∫Ω«Î«Û
typedef struct
{
    ANB_LENSID          lensID;                         //æµÕ∑ID
    UINT                lTrackID;                       //—≤∫ΩID
}PACKED ANBRACK_IPC_ID,*LPANBRACK_IPC_ID;

//IPC∫Õ—≤∫Ω◊È–≈œ¢
//ANB_CMD_UNIFORM_SET_PRESETOUR_REQ                 = 0x3011,               //…Ë÷√—≤∫Ω«Î«Û
typedef struct
{
    ANBRACK_IPC_ID    IPCrackID;
    ANB_PRESETINFOLIST  PresetInfoList;
}PACKED ANB_IPC_PRESETINFOLIST,*LPANB_IPC_PRESETINFOLIST;

//IPC∫Õø¥ ÿŒª–≈œ¢
typedef struct
{
    ANB_LENSID          lensID;                         //æµÕ∑ID
    ANB_GUARDERINFO     GuarderInfo;                    //ø¥ ÿŒª–≈œ¢
}PACKED ANB_IPC_GUARDERINFO,*LPANB_IPC_GUARDERINFO;

//IPC∫Õ…´≤ –≈œ¢
typedef struct
{
    ANB_LENSID          lensID;                         //æµÕ∑ID
    ANB_VIDEOCOLOR      VideoColor;                     //…´≤ –≈œ¢
}PACKED ANB_IPC_VIDEO_COLOR,*LPANB_IPC_VIDEO_COLOR;


/******************************************added end**************************************/

/************************************************************************/
/* ±®æØƒ£øÈ  added by YuShulin 2014.9.16                                */
/************************************************************************/


typedef enum
{
    ALM_LEVEL_FATAL = 0,   //÷¬√¸µƒ
    ALM_LEVEL_SEVERE,      //—œ÷ÿµƒ
    ALM_LEVEL_IMPORTANT,   //÷ÿ“™µƒ
    ALM_LEVEL_NORMAL,      //∆’Õ®µƒ
}ANB_ENUM_ALM_LEVEL; //∏ÊæØµ»º∂

//∏ÊæØ¿‡–Õ
typedef struct
{
    int     nAlmType;                     //∏ÊæØ¿‡–Õ
    char    szName[ANBITLENAME_LEN];    //∏ÊæØ¿‡–Õµƒ√˚≥∆
    int     nInterval;                    //∏ÊæØº‰∏Ù ±º‰
    short   nLevel;                       //∏ÊæØµ»º∂
    short   nDispFlg;                     // «∑Òø…≈…µ•,0:≤ªø…≈…µ•,1:ø…≈…µ•
}ANB_ALMTYPE, *LPANB_ALMTYPE;

//typedef std::list<ANB_ALMTYPE> ALMTYPELIST;
//typedef std::map<int, ANB_ALMTYPE> Type2AlmMap;

//¡™∂Ø≤Ÿ◊˜¿‡–Õ
typedef struct
{
    int     nLinkType;                    //¡™∂Ø≤Ÿ◊˜¿‡–Õ
    char    szName[ANBITLENAME_LEN];    //¡™∂Ø≤Ÿ◊˜¿‡–Õµƒ√˚≥∆
}ANB_ALMLINKTYPE, *LPANB_ALMLINKTYPE;

//typedef std::list<ANB_ALMLINKTYPE> LINKTYPELIST;
//typedef std::map<int, string> LINKTYPEMAP;

//∂‘œÛ¿‡–ÕΩ·ππ
typedef struct
{
    int     nObjType;                   //∂‘œÛ¿‡–Õ
    char    szName[ANBITLENAME_LEN];  //¿‡–Õ√˚≥∆
}ANB_OBJECTTYPE, *LPANB_OBJECTTYPE;

//…œ±®µƒ±®æØ–≈œ¢
typedef  struct
{
    char    szObjID[ANB_OBJID_LEN];  //±®æØ¥•∑¢∂‘œÛ±Í ∂
    char    szObjNm[ANB_OBJID_LEN];     //±®æØ∂‘œÛµƒ…Ë±∏√˚≥∆
    int     nObjType;                //∏ÊæØ¥•∑¢∂‘œÛ¿‡–Õ
    int     nType;                    //±®æØ¿‡–Õ
    int     nTime;                     //±®æØ ±º‰
    int     nStat;                     //±®æØ◊¥Ã¨÷µ
    int     nVal;                     //±®æØ÷µ1
    float   fVal;                    //±®æØ÷µ2
}ANB_ALMREPORT, *LPANB_ALMREPORT;

//typedef std::list<ANB_ALMREPORT>  ANBALMREPORT_LIST;

//±®æØ¡™∂Ø≈‰÷√–≈œ¢
typedef  struct
{
    char    szLinkObjID[ANB_OBJID_LEN];        //¡™∂Ø∂‘œÛ±Í ∂
    int     nLinkObjType;                      //¡™∂Ø∂‘œÛ¿‡–Õ
    int     nLinkOperType;                     //¡™∂Ø≤Ÿ◊˜¿‡–Õ
    char    szLinkOperCtx[ANBITLENAME_LEN];  //¡™∂Ø≤Ÿ◊˜ƒ⁄»›
}ANB_ALMLINKINFO, *LPANB_ALMLINKINFO;

typedef  struct
{
    char            szAlmTrigObjID[ANB_OBJID_LEN]; //∏ÊæØ¥•∑¢∂‘œÛ±Í ∂
    int                nAlmTriggObjType;              //∏ÊæØ¥•∑¢∂‘œÛ¿‡–Õ
    int                nAlmType;                      //∏ÊæØ¿‡–Õ
    ANB_ALMLINKINFO abLinkInfo;                    //¡™∂Ø–≈œ¢
    int                 nLinkInterval;                   //¡™∂Øº‰∏Ù ±º‰
    int                 nLastTime;                       //◊ÓΩ¸“ª¥Œ¡™∂Ø ±º‰
}ANB_ALARMLINK, *LPANB_ALARMLINK;

//“ª∏ˆ¡™∂Ø∂‘œÛø…“‘”–∂‡∏ˆ¡™∂Ø≤Ÿ◊˜¿‡–Õ£¨÷¡∂‡32∏ˆ
//¡™∂Ø≤Ÿ◊˜µƒƒ⁄»›“‘'|'◊˜Œ™∑÷∏Ù∑˚£¨ƒ⁄»›÷–µƒ–°œÓ“‘','◊˜Œ™∑÷∏Ù∑˚,√øœÓ◊Ó∫Û–Ë“™º”…œ∑÷∏Ù∑˚
// æ¿˝“ª:xxxx| ±Ì æ’‚∏ˆ÷–º‰”–“ªœÓ£¨ƒ⁄»› «xxxx
// æ¿˝∂˛:xxxx|aaaa| ±Ì æ”–¡ΩœÓƒ⁄»›£¨∑÷± «xxxx,aaaa
// æ¿˝»˝:a,b,c,|1,2,3,| ”–¡Ω¥ÛœÓƒ⁄»›£¨∑÷± «a,b,c,  1,2,3, ∆‰÷–¥ÛœÓ÷–”÷∑÷–°œÓ»ª∫Û∑÷±Ω‚Œˆ≥ˆ a b c ,1 2 3
typedef struct
{
    int     nLinkOperType;                     //¡™∂Ø≤Ÿ◊˜¿‡–Õ
    char    szLinkOperCtx[ANBITLENAME_LEN];  //¡™∂Ø≤Ÿ◊˜ƒ⁄»›
}ANB_LINKOP, *LPANB_LINKOP;

typedef struct
{
    int     nLinkOperType;                     //¡™∂Ø≤Ÿ◊˜¿‡–Õ
    char    szLinkOperCtx[ANBITLENAME_LEN];  //¡™∂Ø≤Ÿ◊˜ƒ⁄»›
    int        nLinkInterval;                       //¡™∂Øº‰∏Ù ±º‰
    int        nLastTime;                           //◊ÓΩ¸“ª¥Œ¡™∂Ø ±º‰
}ANB_LINKOPINTERVAL, *LPANB_LINKOPINTERVAL;

typedef struct
{
    char            szLinkObjID[ANB_OBJID_LEN];        //¡™∂Ø∂‘œÛ±Í ∂
    int                nLinkObjType;                   //¡™∂Ø∂‘œÛ¿‡–Õ
    int                nCount;                            //¡™∂Ø≤Ÿ◊˜ µº ∏ˆ ˝
    ANB_LINKOP        abLinkOp[ANB_LINKTYPE_MAX];        //¡™∂Ø≤Ÿ◊˜ƒ⁄»› ˝◊È£¨‘™Àÿ∏ˆ ˝÷¡∂‡≤ª≥¨π˝32∏ˆ
}ANB_LINKOBJOP, *LPANB_LINKOBJOP;

//typedef std::vector<ANB_LINKOPINTERVAL> ANB_LINKOPVEC;
//typedef std::map<string, ANB_LINKOPVEC> ANB_LINKOBJOPMAP;  //stringŒ™¡™∂Ø∂‘œÛ±Í ∂+¡™∂Ø∂‘œÛ¿‡–Õ◊È∫œ∂¯≥…µƒæﬂ”–“ª∂®∏Ò Ωµƒ◊÷∑˚¥Æ

//“ª∏ˆ∏ÊæØ∂‘œÛ+“ª∏ˆ∏ÊæØ¿‡–Õø…“‘∂‘”¶∂‡∏ˆ¡™∂Ø∂‘œÛµƒ∂‡∏ˆ¡™∂Ø≤Ÿ◊˜£¨‘⁄¥ÀŒ“√«œﬁ∂®∂‘“ª∏ˆ∏ÊæØ∂‘œÛ+“ª∏ˆ∏ÊæØ¿‡–Õ÷¡∂‡ƒ‹¡™∂Ø32∏ˆ∂‘œÛ°£
typedef struct
{
    char            szAlmTrigObjID[ANB_OBJID_LEN];    //∏ÊæØ¥•∑¢∂‘œÛ±Í ∂
    int                nAlmType;                        //∏ÊæØ¿‡–Õ
    int                nCount;                            // µº ¡™∂Ø∂‘œÛµƒ∏ˆ ˝ //Œ™¡ÀÕ¯¬Á¥´ ‰∑Ω±„£¨Œ“√«“ª¥Œ÷ª∑¢“ª∏ˆ¡™∂Ø∂‘œÛµƒ¡™∂Ø≤Ÿ◊˜ºØ∫œ£¨»Áπ˚”–∂‡∏ˆ¡™∂Ø∂‘œÛ£¨Œ“√«“¿¥Œ±È¿˙∑¢ÀÕ
    ANB_LINKOBJOP    abLinkObjOp[ANB_LINKOBJ_MAX];    //¡™∂Ø∂‘œÛ‘™Àÿ ˝◊È£¨‘™Àÿ∏ˆ ˝÷¡∂‡≤ª≥¨π˝32∏ˆ
}ANB_ALMLINKOBJ, *LPANB_ALMLINKOBJ;

typedef struct
{
    int                nCount;                            // µº ¡™∂Ø∂‘œÛµƒ∏ˆ ˝
    ANB_LINKOBJOP    abLinkObjOp[ANB_LINKOBJ_MAX];    //¡™∂Ø∂‘œÛ‘™Àÿ ˝◊È£¨‘™Àÿ∏ˆ ˝÷¡∂‡≤ª≥¨π˝32∏ˆ
    
}ANB_CENTER_LINKOBJ, *LPANB_CENTER_LINKOBJ;//¥ÀΩ·ππÃÂ◊®√≈”√”⁄∑¢∏¯÷––ƒ∑˛ŒÒ∆˜,∂‘”⁄ƒ≥“ª¥Œ¿¥µƒ∏ÊæØµƒÀ˘”–¡™∂Ø≈‰÷√–≈œ¢

//typedef std::map<string, ANB_LINKOBJOPMAP> ANB_ALMLINKOBJMAP; //stringŒ™∏ÊæØ∂‘œÛ±Í ∂+∏ÊæØ¿‡–Õ◊È∫œ∂¯≥…µƒæﬂ”–“ª∂®∏Ò Ωµƒ◊÷∑˚¥Æ

typedef struct
{
    char            szAlmTrigObjID[ANB_OBJID_LEN];    //∏ÊæØ¥•∑¢∂‘œÛ±Í ∂
    int                nAlmType;                        //∏ÊæØ¿‡–Õ
    
}ANB_ALMLINKQRY, *LPANB_ALMLINKQRY; //∏ÊæØ¡™∂Ø≈‰÷√≤È—ØÃıº˛

//∏ÊæØº‰∏Ù ±º‰≈‰÷√
typedef  struct
{
    char        szAlmObjID[ANB_OBJID_LEN];         //∏ÊæØ∂‘œÛ±Í ∂
    int            nAlmObjType;                    //∏ÊæØ∂‘œÛ¿‡–Õ
    int            nAlmType;                        //∏ÊæØ¿‡–Õ
    int            nAlmInterval;                    //∏ÊæØº‰∏Ù ±º‰
    int            nLastTime;                        //◊ÓΩ¸“ª¥Œ±®æØ ±º‰
}ANB_ALMINTERVALCONF, *LPANB_ALMINTERVALCONF;

typedef  struct
{
    int              nAlmInterval;        //∏ÊæØº‰∏Ù ±º‰
    int              nLastTime;        //◊ÓΩ¸“ª¥Œ±®æØ ±º‰
}ANB_ALMINTERVAL, *LPANB_ALMINTERVAL;

//typedef std::map<std::string, ANB_ALMINTERVAL> ANB_ALMINTERVALMAP; //stringŒ™ANB_ALMINTERVALCONF÷––≈œ¢µƒ∏Ò ΩªØ◊÷∑˚¥Æ ”…∏ÊæØ∂‘œÛ+∏ÊæØ¿‡–Õ

//¡™∂Øº‰∏Ù ±º‰≈‰÷√
typedef  struct
{
    int                 nLinkInterval;        //¡™∂Øº‰∏Ù ±º‰
    int                 nLastTime;            //◊ÓΩ¸“ª¥Œ¡™∂Ø ±º‰
}ANB_LINKINTERVAL, *LPANB_LINKINTERVAL;

//typedef std::map<std::string, ANB_LINKINTERVAL> ANB_LINKINTERVALMAP; //stringŒ™ANB_ALARMLINK÷––≈œ¢µƒ∏Ò ΩªØ◊÷∑˚¥Æ£¨”…∏ÊæØ∂‘œÛ+∏ÊæØ¿‡–Õ+¡™∂Ø∂‘œÛ+¡™∂Ø¿‡–Õ

//”√ªß”Î¡™∂Ø¿‡–Õµƒ∂‘”¶πÿœµ
typedef struct
{
    char    szLinkObjID[ANB_OBJID_LEN];           //¡™∂Ø∂‘œÛ±Í ∂
    int     nLinkOperType;                       //¡™∂Ø≤Ÿ◊˜¿‡–Õ£¨”√ªß◊Ó∂‡ø…◊ˆ32÷÷¿‡–Õµƒ¡™∂Ø≤Ÿ◊˜
    char    szLinkOperCtx[ANBITLENAME_LEN];  //¡™∂Ø≤Ÿ◊˜ƒ⁄»›
}ANB_USRLINK, *LPANB_USRLINK;

typedef  struct
{
    char         szUsrID[ANB_OBJID_LEN];              //”√ªß∂‘œÛ±Í ∂
    int          nCount;                            //∏˘æ›≈‰÷√–≈œ¢∏√”√ªßø…“‘◊ˆ¡™∂Øµƒ◊‹ ˝
    ANB_USRLINK     abUsrLink[ANB_LINKOBJ_MAX];        //”√ªß¡™∂Ø≈‰÷√º«¬ººØ∫œ£¨÷¡∂‡32∏ˆ
}ANB_USRLINKLIST, *LPANB_USRLINKLIST;

//typedef std::vector<ANB_USRLINK> ANB_USRLINKVEC;

typedef struct
{
    char    szLinkObjID[ANB_OBJID_LEN];           //¡™∂Ø∂‘œÛ±Í ∂
    char    szLinkOperCtx[ANBITLENAME_LEN];  //¡™∂Ø≤Ÿ◊˜ƒ⁄»›
}ANB_LINKCTX, *LPANB_LINKCTX;

typedef struct
{
    int                nLinkOpType;                //¡™∂Ø≤Ÿ◊˜¿‡–Õ
    int                nCount;                        //∂‘∏√¡™∂Ø≤Ÿ◊˜¿‡–Õ£¨≈‰÷√µƒ¡™∂Ø∂‘œÛµƒ∏ˆ ˝
    ANB_LINKCTX        abLinkCtx[ANB_LINKOBJ_MAX]; //“‘¡™∂Ø∂‘œÛ”Î¡™∂Øƒ⁄»›Œ™‘™Àÿ£¨÷¡∂‡≤ª≥¨π˝32∏ˆ
}ANB_LINKTYPECTX, *LPANB_LINKTYPECTX;

//øÕªß∂À ’µΩ±®æØ∑˛ŒÒ∆˜…œ±®π˝¿¥µƒ±®æØ ˝æ›£¨∞¸∫¨∏ÊæØ–≈œ¢∫Õ¡™∂Ø–≈œ¢
typedef  struct
{
    ANB_ALMREPORT     abAlmReport;                    //±®æØ–≈œ¢
    int                  nCount;                          //∏˘æ›≈‰÷√–≈œ¢π˝¬«∫Û£¨∫ÛÃ®»œŒ™∏√”√ªßø…“‘◊ˆµ√¡™∂Øµƒ◊‹ ˝
    ANB_USRLINK          abLinkInfo[ANB_LINKTYPE_MAX];   //¡™∂Ø¡–±Ì£¨”√ªß◊Ó∂‡ø…◊ˆ32∏ˆ¡™∂Ø£¨Œﬁ¬€ «“ª∏ˆ¡™∂Ø∂‘œÛ◊ˆ32∏ˆ≤Ÿ◊˜£¨ªπ «32∏ˆ¡™∂Ø∂‘œÛ◊ˆ“ª∏ˆ≤Ÿ◊˜£¨’‚∂ºÀ„◊ˆ32Ãı¡™∂Ø≈‰÷√º«¬º
    
}ANB_USRALMLINKINFO, *LPANB_USRALMLINKINFO;

/***********∏ÊæØ≈…µ•ƒ£øÈ***************/

typedef enum
{
    DISPLIST_STATE_WAIT_FOR_RECEIVE = 0, //µ»¥˝Ω” ’
    DISPLIST_STATE_WAIT_FOR_REPLY,       //µ»¥˝ªÿ∏¥
    DISPLIST_STATE_WAIT_FOR_ARCHIVE,     //µ»¥˝πÈµµ
    DISPLIST_STATE_HAVE_ARCHIVED,        //“—æ≠πÈµµ
}ANB_ENUM_DIPATCHLIST_STATE;

//∏ÊæØ≈…µ•–≈œ¢
typedef  struct
{
    int            nState;                                //≈…µ•◊¥Ã¨( 0£∫µ»¥˝Ω” ’£¨1:µ»¥˝ªÿ∏¥£¨2£∫µ»¥˝πÈµµ£¨3£∫“—æ≠πÈµµ)
    int            nAutoFlag;                            //∏√≈…µ• «∑ÒŒ™◊‘∂Ø≈…µ•£¨0: ÷∂Ø≈…µ•, 1:◊‘∂Ø≈…µ•
    char        szTitle[ANBITLENAME_LEN];          //≈…µ•±ÍÃ‚
    char        szSquence[ANB_SEQUENCE_LEN];         //≈…µ•¡˜ÀÆ∫≈
    char        szAlmObjID[ANB_OBJID_LEN];            //±®æØ∂‘œÛID
    char        szDepartment[ANBITLENAME_LEN];    //æ÷√˚ªÚÀ˘ Ù«¯”Ú√˚
    char        szDevName[ANBITLENAME_LEN];        //…Ë±∏√˚≥∆£¨º¥∏ÊæØ∂‘œÛ±Í ∂µƒæﬂÃÂ√˚≥∆
    char        szAlmInfo[ANBITLENAME_LEN];       //∏ÊæØ–≈œ¢£¨º¥∏√∏ÊæØ¿‡–Õµƒ√˚≥∆
    int         nPreProcTm;                         //≈…µ•‘§¥¶¿Ì∆⁄œﬁ£¨≤…”√œ‡∂‘ ±º‰£¨“‘∑¢ÀÕ≈…µ• ±º‰Œ™∆ ºª˘◊º
    int         nAlmType;                           //∏ÊæØ¿‡–Õ
    int            nLevel;                                //∏ÊæØº∂±
    int            nAlmTm;                                //∏ÊæØø™ º ±º‰
    char        szCallType[4];                        //4÷÷—∞∫Ù∑Ω Ω£∫szCallType[0]±Ì æ ÷ª˙∂Ã–≈£¨0Œ¥ø™∆Ù£¨1ø™∆Ù,szCallType [1]±Ì æ” º˛£¨0Œ¥ø™∆Ù£¨1ø™∆Ù
    //szCallType[3]∫ÕszCallType[4]‘› ±Œ¥”√£¨±£¡Ù◊÷∂Œ°£
    char        szReminder[ANB_PROMPT_LEN];            //≈…µ•Ã· æ£¨÷¡∂‡128∏ˆ◊÷∑˚
    char        szSender[ANBITLENAME_LEN];           //≈…µ•∑¢ÀÕ»À
    int            nSendTm;                            //≈…µ•∑¢ÀÕ ±º‰
    int         nCancelledTm;                       //≈…µ•◊¢œ˙ ±º‰
    
    //    char        szReply[ANBITLENAME_LEN];            //ªÿ∏¥»À
    char        szRepairDept[ANBITLENAME_LEN];    //Œ¨–ﬁ≤ø√≈
    int            nRepairTm;                            //Œ¨–ﬁ ±º‰
    char        szFaultType[ANBITLENAME_LEN];      //π ’œ¿‡–Õ
    int            nRepairReplyTm;                     //ªÿ∏¥ ±º‰
    int            nAcceptTm;                          //≈…µ•±ªΩ” ‹ ±º‰
    int            nReplyType;                            //ªÿ∏¥◊¥Ã¨, 0£∫Ω” ‹£¨1£∫æ‹æ¯
    char        szRepairResult[ANB_CONTEXT_LEN];    //ªÿ∏¥µƒŒ¨–ﬁΩ·π˚ªÚ≈…µ•±ªæ‹æ¯µƒ¿Ì”…£¨÷¡∂‡256∏ˆ◊÷∑˚
    
    int            nRecvTm;                            //≈…µ•÷˜Ω” ’»ÀΩ” ’≈…µ•µƒ ±º‰
    int            nRecvCount;                            //≈…µ•Ω” ’»À ˝ƒø£¨÷¡∂‡4∏ˆ
    char        szMasterRecv[ANBITLENAME_LEN];    //≈…µ•÷˜Ω” ’»À
    char        szSlaveRecv1[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À1
    char        szSlaveRecv2[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À2
    char        szSlaveRecv3[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À3
}ANB_DISPATCHINFO, *LPANB_DISPATCHINFO;

//∏ÊæØ◊‘∂Ø≈…µ•πÊ‘Ú
typedef struct
{
    int        nRuleID;            //πÊ‘ÚID
    char    szRule[32];         //πÊ‘Ú√˚≥∆
    int        nAlmType;           //±®æØ¿‡–Õ
    int        nAlmLevel;          //±®æØµ»º∂
    char    szDept[32];         //æ÷√˚ªÚÀ˘ Ù«¯”Ú
    int        nDelayTm;           //≈…µ•—” ±£¨≤…”√œ‡∂‘ ±º‰£¨“‘Ω” ’µΩ∏ÊæØµƒ ±º‰Œ™∆ ºª˘◊º, Œ™0‘Ú±Ì æ≤ª—” ±£¨¡¢º¥≈…µ•
}ANB_RULE, *LPANB_RULE; //ø…“‘Õ®π˝°∞±®æØ¿‡–Õ°±+ °∞æ÷√˚ªÚÀ˘ Ù«¯”Ú°±¿¥»∑∂®“ªÃıπÊ‘Ú£®πÊ‘ÚID£©

//∏ÊæØ◊‘∂Ø≈…µ•≤ﬂ¬‘
typedef  struct
{
    int        nRuleID;                            //πÊ‘ÚID
    char    szSender[ANBITLENAME_LEN];        //≈…µ•∑¢ÀÕ»À
    int        nReceiveCount;                        //Ω” ’»À ˝ƒø
    char    szMasterRecv[ANBITLENAME_LEN];    //≈…µ•÷˜Ω” ’»À
    char    szSlaveRecv1[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À1
    char    szSlaveRecv2[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À2
    char    szSlaveRecv3[ANBITLENAME_LEN];    //≈…µ•∏±Ω” ’»À3
}ANB_AUTODSPCONF, *LPANB_AUTODSPCONF;

//≈…µ•∑¢ÀÕ«Èøˆº«¬º£¨÷˜“™‘⁄ª∫¥Ê÷– π”√
typedef struct
{
    char    szAlmObjID[ANB_OBJID_LEN]; //±®æØ∂‘œÛID
    int        nAlmType;                  //±®æØ¿‡–Õ
}ANB_DISPKEY, *LPANB_DISPKEY;

typedef struct
{
    char    szSquence[ANB_SEQUENCE_LEN];         //≈…µ•¡˜ÀÆ∫≈
    int     nDispSndTm;                         //≈…µ•∑¢ÀÕ ±º‰ªÚ’ﬂÃ· æ–≈œ¢ ±º‰
}ANB_DISPVAL, *LPANB_DISPVAL;

//typedef std::map<string, ANB_DISPVAL>  ANB_DISPRECORDMAP;//stringŒ™±®æØ∂‘œÛID+±®æØ¿‡–Õ◊È∫œ∂¯≥…µƒ◊÷∑˚¥Æ

typedef struct
{
    int            nState;                                //≈…µ•◊¥Ã¨( 0£∫µ»¥˝Ω” ’£¨1:µ»¥˝ªÿ∏¥£¨2£∫µ»¥˝πÈµµ£¨3£∫“—æ≠πÈµµ)
    int         nPreProcTm;                         //≈…µ•‘§¥¶¿Ì∆⁄œﬁ£¨≤…”√œ‡∂‘ ±º‰£¨“‘∑¢ÀÕ≈…µ• ±º‰Œ™∆ ºª˘◊º
    char        szMasterRecv[ANBITLENAME_LEN];    //≈…µ•÷˜Ω” ’»À
    
}ANB_DISPTCHELEM, *LPANB_DISPTCHELEM;

typedef struct
{
    char    szEmail[64];        //”√ªßµƒ” º˛µÿ÷∑
    char    szMobil[16];        //”√ªßµƒ ÷ª˙∫≈¬Î
}ANB_USERINFO, *LPANB_USERINFO;

typedef struct
{
    int            pageno;        //≤È—Ø“≥∫≈
    int            pagesize;    //“ª“≥ ˝æ›Ãı ˝
    int            nState;        //≤È—ØÃıº˛£¨≈…µ•◊¥Ã¨
}ANB_SQUENCE_QUERY, *LPANB_SQUENCE_QUERY;

typedef struct
{
    char        szAlmObjID[ANB_OBJID_LEN];        //±®æØ∂‘œÛID
    int            nAlmType;                        //±®æØ¿‡–Õ
    char        szSquence[ANB_SEQUENCE_LEN];     //≈…µ•¡˜ÀÆ∫≈
}ANB_SQUENCEELEM, *LPANB_SQUENCEELEM;

typedef struct
{
    int                allpage; //∑˚∫œ≤È—ØÃıº˛µƒ◊‹“≥ ˝
    int                pageno;  //≤È—Ø“≥∫≈
    int                itemnum; //∏√“≥µƒ µº ‘™Àÿ∏ˆ ˝
    ANB_SQUENCEELEM    item[ANB_SEQPAGE_MAX_SIZE];
}ANB_SQUENCEELEM_PAGE, *LPANB_SQUENCEELEM_PAGE;

typedef enum
{
    ANB_OBJTYPE_IPC = 0x01,        //IPC
    ANB_OBJTYPE_NVR,            //NVR
    ANB_OBJTYPE_DVS,            //DVS
    ANB_OBJTYPE_DVR,            //DVR
    ANB_OBJTYPE_VIDEO_CHANN,    // ”∆µÕ®µ¿
    ANB_OBJTYPE_IO_OU_CHANN,    //IO ‰≥ˆÕ®µ¿
    ANB_OBJTYPE_IO_IN_CHANN,    //IO ‰»ÎÕ®µ¿
    ANB_OBJTYPE_CLIENT,            //øÕªß∂À
    ANB_OBJTYPE_SERVER,            //∑˛ŒÒ∆˜
    ANB_OBJTYPE_POWER_DEV,        //∂Ø¡¶…Ë±∏
    ANB_OBJTYPE_ENVIR_DEV,        //ª∑æ≥…Ë±∏
    ANB_OBJTYPE_DOOR_GUARD,        //√≈Ω˚
}ANB_ENUM_OBJECTTYPE;

typedef enum
{
    ANB_LINKTYPE_START_RECORD    = 0x01, //¡™∂Øø™ º¬ºœÒ
    ANB_LINKTYPE_END_RECORD,             //¡™∂ØΩ· ¯¬ºœÒ
    ANB_LINKTYPE_SNAPSHOT,              //¡™∂Ø◊•≈ƒ
    ANB_LINKTYPE_EMAIL,                 //¡™∂Ø∑¢” º˛
    ANB_LINKTYPE_MESSAGE,               //¡™∂Ø∑¢∂Ãœ¢
    ANB_LINKTYPE_PTZPRESET,             //¡™∂Ø‘∆Ã®‘§÷√µ„
    ANB_LINKTYPE_PTZTOUR,               //¡™∂Ø‘∆Ã®—≤∫Ω
    ANB_LINKTYPE_PTZGUARDER,            //¡™∂Ø‘∆Ã®ø¥ ÿŒª
    ANB_LINKTYPE_OPEN_AC,               //¡™∂Ø¥Úø™ø’µ˜
    ANB_LINKTYPE_CLOSE_AC,              //¡™∂Øπÿ±’ø’µ˜
    ANB_LINKTYPE_OPEN_OTHER,            //¡™∂Ø¥Úø™∆‰À˚∂Ø¡¶œµÕ≥
    ANB_LINKTYPE_CLOSE_OTHER,           //¡™∂Øπÿ±’∆‰À˚∂Ø¡¶œµÕ≥
}ANB_ENUM_LINKTYPE;

/**************¬ºœÒŒƒº˛ ±º‰–≈œ¢Ω·ππÃÂ**********************************************************/
typedef struct
{
    DWORD  dwYear;                                      //ƒÍ
    DWORD  dwMonth;                                     //‘¬
    DWORD  dwDay;                                       //»’
    DWORD  dwHour;                                      // ±
    DWORD  dwMinute;                                    //∑÷
    DWORD  dwSecond;                                    //√Î
}PACKED ANBIME,*LPANBIME;

/**************¬ºœÒ–≈œ¢Ω·ππÃÂ**********************************************************/
typedef struct
{
    ANBIME  strutStartTime;                            //¬ºœÒµƒø™ º ±º‰
    ANBIME  strutStoptime;                             //¬ºœÒµƒΩ· ¯ ±º‰
}PACKED ANBTIME_SECTION_DATA,*LPANBTIME_SECTION_DATA;

//¬ºœÒ≤È—Ø«Î«ÛΩ·ππÃÂ
typedef struct
{
    CHAR    szChannelID[ANB_ID_LEN];                    //Õ®µ¿±Í ∂
    unsigned long ulRecordType;                         //¥Ê¥¢¿‡–Õ 1:∂® ±¬ºœÒ 2: ¬º˛¬ºœÒ
    ANBIME    StartTime;
    ANBIME    StopTime;
}PACKED ANB_QueryRecordREQ,*LPANB_QueryRecordREQ;

//œÚ¥Ê¥¢∑˛ŒÒ∆˜∑¢ÀÕ≤È—Ø¬ºœÒµƒ∑µªÿ–≈œ¢
typedef struct
{
    ANBTIME_SECTION_DATA sectionData;
    CHAR    szSerID[ANB_ID_LEN];            // ∑˛ŒÒ∆˜ID
    CHAR    szFilePath[MAX_PATH_LEN];        // µ„≤•µƒŒƒº˛¬∑æ∂
}PACKED ANB_QueryRecordInfo, *LPANB_QueryRecordInfo;

typedef struct
{
    long plQueryRecordCount;
    ANB_QueryRecordInfo QueryRecordInfoList[MAX_QUERY_RECORD_RELUST];
}PACKED ANB_QueryRecordRSP,*LPANB_QueryRecordRSP;

//œÚ÷––ƒ∑˛ŒÒ∆˜∑¢ÀÕ≤È—Ø¬ºœÒ∑µªÿ–≈œ¢
typedef struct
{
    long lCenterQueryRecordCount;
    ANB_SERVERID   SereverIDList[MAX_RECORD_SERVER_COUNT];
}PACKED ANB_CenterQueryRecordRsp,*LPANB_CenterQueryRecordRsp;

typedef struct
{
    WORD         wStreamClass;            //¬Î¡˜¿‡±, 1 -µ⁄“ª¬Î¡˜£ª2 -µ⁄∂˛¬Î¡˜£ª3 -µ⁄»˝¬Î¡˜
    WORD         wStreamType;             //¬Î¡˜¿‡–Õ 0 - ”∆µ¡˜, 1 -∏¥∫œ¡˜, ±Ì æ ¬º˛—πÀı≤Œ ˝ ±◊Ó∏ﬂŒª±Ì æ «∑Ò∆Ù”√—πÀı≤Œ ˝
    BYTE         byResolution;            //∑÷±Ê¬
    WORD         wBitRateType;            //¬Î¬ ¿‡–Õ 0:±‰¬Î¬ , 1:∂®¬Î¬
    DWORD        dwBitRate;               //¬Î¬
    SHORT        sFrameRate;              //÷°¬ £¨∆‰÷–25±Ì æ25£¨-2±Ì æ1 / 2£¨-16±Ì æ1 / 16,“‘¥À¿‡Õ∆
    WORD         wPicQuality;             //ÕºœÒ÷ ¡ø£∫1 -◊Ó∏ﬂ£¨2 -Ωœ∏ﬂ£¨3 -÷–µ»£¨4 -µÕ£¨5 -ΩœµÕ£¨6 -◊ÓµÕ
    BYTE         byVideoEncType;          // ”∆µ±‡¬Î¿‡–Õ
    DWORD        dwFrameInterval;         //I÷°º‰∏Ù
}PACKED ANB_VIDEOCFG, *LPANB_VIDEOCFG;

//IPC∫Õ±‡¬Î≈‰÷√
typedef struct
{
    ANB_LENSID          lensID;                       //æµÕ∑ID
    ANB_VIDEOCFG        VideoCfg;                     //±‡¬Î≈‰÷√
}PACKED ANB_IPC_VIDEO_CFG,*LPANB_IPC_VIDEO_CFG;

//ª÷∏¥∂‘∆Î◊¥Ã¨
#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack(pop)
#endif

#endif
