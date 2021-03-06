#ifndef HNCOMN_H_H_H_H_H_H
#define HNCOMN_H_H_H_H_H_H
//#include "../../Include/NetComnLib/HnNetComnType.h"
//#include "HnNetProt.h"
//#include "HnProtDefine.h"

#include "HnProto.h"
#include <string>
#include <map>
#define  HN_HAND int

using namespace std;


typedef map<int, HN_CMDBUF>		HN_CMDLIST;

class CHnNetComn;
class CHnComn
{
public:
    CHnComn(int mode);
    virtual ~CHnComn();

	void	SetProxyServerAndUsrAccount(const char *pProxyIPAddr, int proxyPort, 
			const char *pAccount, const char *pPasswd, bool bIsHttp); //added by yushulin 2012.12.4

	void	SetPriServer(string server, int port);
	void	SetSubServer(string server, int port);
	bool	StartNetComn(int port = -1);
	void	CloseNetComn(void);
	void	CloseNetSesn(int tag);
	void	CloseNetSesn2(int tag); //added by yushulin 2013.7.28
	int		GetLastError(void);
    bool    GetPriServer(string& server, int& port);
    string  GetCurServer();
	bool    GetIsOpenProxy(); //added by yushulin 2012.12.4
	bool    GetProxyParameter(string& ProxyIPAddr, int& ProxyPort, string& ProxyAccount, 
			string& ProxyPasswd, bool& bIsHttp); //added by yushulin 2012.12.4


protected:
	void			NetCmdProc(int  tag, char* buf, int len);	
	virtual int		NetCmdComb(int type, char* buf, int len);
	virtual void 	NetCmdEror(int tag);
	virtual int		NetCmdProc(HN_NETMSG& nmsg, int tag);
	void			CmdBufProc(HN_CMDBUF&  cmd, int tag);
	bool			ProcCmdBuf(HN_CMDBUF&  cmd, int tag);
	bool			GetCmdHead(HN_PROT_HEAD& head, char* buf, int len, int& pos);
	bool			GetPrtHead(HN_PROT_HEAD& head, char* buf, int len, int& pos);
	bool			ProcCmdBuf1(HN_CMDBUF&  cmd, int tag);
    std::string     GetConnIP(int sock);
    bool            GetCatActive();
    void            SetCatActive(bool bActive);

private:
	static void		NetCmdProc(HN_HAND hHand, int  tag, char* buf, int len);
	static int		NetCmdComb(HN_HAND hHand, int type, char* buf, int len);
	static void		NetCmdEror(HN_HAND hHand, int tag);        
	
protected:
	HN_CMDLIST		m_CmdList;
	HN_PROT_HEAD	m_ProtHead;
	//CHnNetComn*		m_pNetComn;
};

#endif
