#pragma once
#include <winsock2.h>

class CServer_UDP
{
public:
	CServer_UDP();
	void SendMsg(const char sendBuf[]);
	void RecMsg();
	~CServer_UDP();

private:
	SOCKET m_sServer;
	struct sockaddr_in m_SocAddrClient;
	bool m_terminal;
};