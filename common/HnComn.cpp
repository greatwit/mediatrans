//#include <afx.h>
//#include "../../../Include/NetComnLib/HnNetComn.h"
//#include "../../../Include/ProtLib/HnCmdCode.h"
//#include "../../../Include/ProtLib/HnErrorCode.h"
//#include "../../../Include/ProtLib/HnComn.h"

#include "HnComn.h"

CHnComn::CHnComn(int mode)
{
	memset(&m_ProtHead, 0, sizeof(m_ProtHead));
	memcpy(&m_ProtHead.head, "$HN$", 4);
	m_ProtHead.ssrc  = 10;
	m_ProtHead.vers1 = 1;
	/*
	m_pNetComn = new CHnNetComn(mode);
	if (m_pNetComn != NULL)
	{
		m_pNetComn->SetDataProc(this, NetCmdProc, NetCmdComb, NetCmdEror);
	}
	*/
}

CHnComn::~CHnComn()
{
	m_CmdList.clear();

}

bool CHnComn::GetCmdHead(HN_PROT_HEAD& head, char* buf, int len, int& pos)
{
	memset(&head, 0, sizeof(head));
	for (pos = 0; pos <= len; pos++)
	{
		if (   buf[pos+0] =='$'
			&& buf[pos+1] =='H'
			&& buf[pos+2] =='N'
			&& buf[pos+3] =='$')
		{
			memcpy(&head, buf+pos, sizeof(head));
			return true;
		}
	}

	return false;
}

bool CHnComn::GetPrtHead(HN_PROT_HEAD& head, char* buf, int len, int& pos)
{
	int				pos1;

	//没有正确的协议头，需要略过缓冲区中这部分数据
	if (!GetCmdHead(head, buf, len, pos))
	{
		return false;
	}

	//协议包长度校验错误，跳过协议标记字节，重新搜索协议头
	if (head.len > sizeof(HN_NETMSG) - sizeof(head))
	{
		pos += 4;
		return false;
	}

	//缓冲区中数据不够一个协议包，需要等待完整数据包的到来
	if (head.len + sizeof(head) > len - pos)
	{
		//HNTRACE("len ===555555555555555============================= %d, pos ========== %d, %d\n", len, pos, head.len);
		return false;
	}

	//缓冲区中数据刚好为一个协议包，正常处理协议包
	if (head.len + sizeof(head) == len - pos)
	{
		return true;
	}

	//缓冲区中数据多于一个协议包，需要作后续包校验
	//校验成功，则为正常协议包，正常处理，否则跳过协议标记字节
	if (head.len + sizeof(head) + pos + 4 > len)
	{
		//协议包后续缓冲不够能确定完整协议包的数据，等待数据足够数据进行分析、处理
		//HNTRACE("len ================================ %d, pos ========== %d, %d\n", len, pos, head.len);
		return false;
	}

	pos1 = len;
	len  = pos + head.len + sizeof(head);
	if (buf[len+0] =='$' && buf[len+1] =='H' && buf[len+2] =='N' && buf[len+3] =='$')
	{		
	//	HNTRACE("len ================================ %d, pos ========== %d, %d\n", pos1, pos, head.len);
		return true;
	}

	pos += 4;
	return false;
}

bool CHnComn::ProcCmdBuf1(HN_CMDBUF& cmd, int tag)
{
	int					pos, len, stat;
	HN_NETMSG			nmsg;

	/*
	len = cmd.len-sizeof(nmsg.head);
	if (len < 0 || m_pNetComn == NULL)
	{
		return false;
	}

	//没有搜索到完整的协议包，需要进行缓冲数据搬移，保证缓冲开头为协议头
	if (!GetPrtHead(nmsg.head, cmd.buf, cmd.len, pos))
	{
		//缓冲开头已经为协议头，说明该协议包不完整，需要等待协议数据
		if (pos == 0)
		{
			return false;
		}

		if (cmd.len <= pos)
		{
			cmd.len = 0;
			return false;
		}

		//缓冲开头不为协议头，还需要继续搜索协议包
		memcpy(cmd.buf, cmd.buf+pos, cmd.len-pos);
		cmd.len -= pos;
		return true;
	}

	len = nmsg.head.len + sizeof(nmsg.head);	
	memcpy(&nmsg, cmd.buf, len);
	cmd.len = cmd.len - len;
	//缓冲区中还存在协议数据，需要进行数据搬移
	if (cmd.len > 0)
	{
		memcpy(cmd.buf, cmd.buf+len, cmd.len);	
	}

	stat = HNCOMSTAT_REFUSE;
	if (nmsg.head.code == HNERROR_OK)
	{
		stat = HNCOMSTAT_ACCEPT;
	}

	len = NetCmdProc(nmsg, tag);
	m_pNetComn->SendNetData(nmsg.head.cmd, tag, (char*)&nmsg, len, stat);
	//HNTRACE("pos = %d, len = %d, cmd =================================== %X\n", pos, len, nmsg.head.cmd);
	*/
	return true;
}

bool CHnComn::ProcCmdBuf(HN_CMDBUF& cmd, int tag)
{
	int					pos, len, stat;
	HN_NETMSG			nmsg;

	/*
	len = cmd.len-sizeof(nmsg.head);
	if (len < 0 || m_pNetComn == NULL)
	{
		return false;
	}

	memset(&nmsg.head, 0, sizeof(nmsg.head));
	for (pos = 0; pos <= len; pos++)
	{
		if (   cmd.buf[pos+0] =='$'
			&& cmd.buf[pos+1] =='H'
			&& cmd.buf[pos+2] =='N'
			&& cmd.buf[pos+3] =='$')
		{			
			memcpy(&nmsg.head, cmd.buf+pos, sizeof(nmsg.head));
			break;
		}
	}

	if (pos > 0)
	{
		cmd.len -= pos;
		memcpy(cmd.buf, cmd.buf+pos, cmd.len-pos);
	}

	len = nmsg.head.len + sizeof(nmsg.head);
	if (len > cmd.len)
	{
		return false;
	}

//	HNTRACE("cmd ======================================= %X\n", nmsg.head.cmd);	
	memcpy(&nmsg, cmd.buf, len);
	cmd.len = cmd.len - len;
	if (cmd.len > 0)
	{
		memcpy(cmd.buf, cmd.buf+len, cmd.len);	
	}

	stat = HNCOMSTAT_REFUSE;
	if (nmsg.head.code == HNERROR_OK)
	{
		stat = HNCOMSTAT_ACCEPT;
	}

	len = NetCmdProc(nmsg, tag);
	m_pNetComn->SendNetData(nmsg.head.cmd, tag, (char*)&nmsg, len, stat);
	*/
//	HNTRACE("pos = %d, len = %d, cmd =================================== %X\n", pos, len, nmsg.head.cmd);
	return true;
}

void CHnComn::CmdBufProc(HN_CMDBUF& cmd, int tag)
{
	int			num;

	num = 0;
	while (true)
	{
		num ++;
		if (num > 20)
		{
			//HNTRACE("int num === %d, cmelen ================================================ %d\n", num, cmd.len);
            break;
		}

		if (!ProcCmdBuf1(cmd, tag))
		{
			break;
		}
	}
}

void CHnComn::NetCmdProc(int tag, char* buf, int len)
{
	HN_CMDLIST::iterator	pi;
	HN_CMDBUF				cmd;

	pi = m_CmdList.find(tag);
	if (pi == m_CmdList.end())
	{
		memset(&cmd, 0, sizeof(cmd));
		m_CmdList[tag] = cmd;
		pi = m_CmdList.find(tag);
	}

//	HNTRACE("len =======================================dddddddddddddddd %d\n", len);
	if (pi->second.len+len > sizeof(cmd.buf))
	{
		//HNTRACEPOINT;
		len = sizeof(cmd.buf) - pi->second.len;
	}

	memcpy(pi->second.buf+pi->second.len, buf, len);
	pi->second.len += len;
	CmdBufProc(pi->second, pi->first);
}

int CHnComn::NetCmdProc(HN_NETMSG& nmsg, int tag)
{
	return 0;
}

int CHnComn::NetCmdComb(int type, char* buf, int len)
{
	return 0;
}

void CHnComn::NetCmdEror(int tag)
{
	HN_CMDLIST::iterator	pi;

	pi = m_CmdList.find(tag);
	if (pi != m_CmdList.end())
	{
		m_CmdList.erase(pi);
	}
}

void CHnComn::NetCmdProc(HN_HAND hHand, int tag, char* buf, int len)
{
	CHnComn*			pComn;

	pComn = (CHnComn*)hHand;
	if (pComn != NULL)
	{
		pComn->NetCmdProc(tag, buf, len);
	}
}
 
int CHnComn::NetCmdComb(HN_HAND hHand, int type, char* buf, int len)
{
	CHnComn*			pComn;

	pComn = (CHnComn*)hHand;
	if (pComn != NULL)
	{
		len = pComn->NetCmdComb(type, buf, len);
	}
	else
	{
		len = 0;
	}

	return len;
}  
 
void CHnComn::NetCmdEror(HN_HAND hHand, int tag)
{
	CHnComn*			pComn;

	pComn = (CHnComn*)hHand;
	if (pComn != NULL)
	{
		pComn->NetCmdEror(tag);
	}
}

void CHnComn::SetPriServer(string server, int port)
{
	/*
	if (m_pNetComn != NULL)
	{
		m_pNetComn->SetPriServer(server, port);
	}
	*/
}

void CHnComn::SetSubServer(string server, int port)
{
	/*
	if (m_pNetComn != NULL)
	{
		m_pNetComn->SetSubServer(server, port);
	}
	*/
}

bool CHnComn::StartNetComn(int port /* = -1 */)
{
	/*
	if (m_pNetComn == NULL)
	{
		return false;
	}

	return m_pNetComn->StartNetComn(port);
	*/
	return true;
}

void CHnComn::CloseNetComn(void)
{
	/*
	if (m_pNetComn == NULL)
	{
		return;
	}

	m_pNetComn->CloseNetComn();
	*/
}

void CHnComn::CloseNetSesn(int tag)
{
	/*
	if (m_pNetComn == NULL)
	{
		return;
	}

	m_pNetComn->CloseNetSesn(tag);
	*/
}

int	CHnComn::GetLastError(void)
{
	return 0;
}

std::string CHnComn::GetConnIP( int sock )
{
	/*
	if (m_pNetComn == NULL)
	{
		return "";
	}

    return m_pNetComn->GetConnIP(sock);
	*/
	return "";
}


bool CHnComn::GetPriServer( string& server, int& port )
{
    //return m_pNetComn->GetPriServer(server, port);
	return false;
}

bool CHnComn::GetCatActive()
{
	/*
    if (m_pNetComn != NULL)
    {
        return m_pNetComn->GetCatActive();
    }
	*/
    return false;
}

void CHnComn::SetCatActive( bool bActive )
{
	/*
    if (m_pNetComn != NULL)
    {
        m_pNetComn->SetCatActive(bActive);
    }
	*/
}

std::string CHnComn::GetCurServer()
{
	/*
	if (m_pNetComn != NULL)
	{
        return m_pNetComn->GetCurServer();
	}
	*/
    return "";
}

void CHnComn::SetProxyServerAndUsrAccount( const char *pProxyIPAddr, int proxyPort, const char *pAccount, const char *pPasswd, bool bIsHttp )
{
	/*
	if (m_pNetComn != NULL)
	{
		m_pNetComn->SetProxyServerAndUsrAccount(pProxyIPAddr, proxyPort, pAccount, pPasswd, bIsHttp);
	}
	*/
}

bool CHnComn::GetIsOpenProxy()
{
	/*
	if (m_pNetComn != NULL)
	{
		return m_pNetComn->GetIsOpenProxy();
	}*/

	return false;
}

bool CHnComn::GetProxyParameter( string& ProxyIPAddr, int& ProxyPort, string& ProxyAccount, string& ProxyPasswd, bool& bIsHttp )
{
	/*
	if (m_pNetComn == NULL)
	{
		return false;
	}
	
    return m_pNetComn->GetProxyParameter(ProxyIPAddr, ProxyPort, ProxyAccount, ProxyPasswd, bIsHttp);
	*/
	return false;
}

void CHnComn::CloseNetSesn2( int tag )
{
	/*
	if (m_pNetComn == NULL)
	{
		return;
	}
	
	m_pNetComn->CloseNetSesn2(tag);
	*/
}

