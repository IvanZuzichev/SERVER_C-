#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CServer_UDP.h"

#include <iostream>

#pragma comment(lib, "ws2_32.lib")

struct Calculator
{
	int one;
	int two;
};
CServer_UDP::CServer_UDP() :m_terminal(false)
{
	//������ ���� ��������������� ��������� �������, ����� socket() ������ ������ 10093.
	//������������� WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //������������� ws2_32.dll ����� �������
	{
		std::cout << "������������� WSA �� �������!" << std::endl;
		return;
	}
	//������������� UDP ������
	m_sServer = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in m_SocAddrserver;
	m_SocAddrserver.sin_addr.S_un.S_addr = 0;//htonl(INADDR_ANY);
	m_SocAddrserver.sin_family = AF_INET;
	m_SocAddrserver.sin_port = htons(8090);

	//�������� ������ ���������� � ������
	int ret = bind(m_sServer, (sockaddr*)&m_SocAddrserver, sizeof(m_SocAddrserver));
	if (ret == -1)
	{
		std::cout << "�������� �� �������!" << std::endl;
		WSACleanup();
	}
	else
	{
		//������ ���� ��������� ��������� ��������, ����� ������ �� ������ ��������� ���������.
		int len_Client = sizeof(sockaddr);
		char recBuf[1025];
		int len = recvfrom(m_sServer, recBuf, 1024, 0, (sockaddr*)&m_SocAddrClient, &len_Client);
		if (len > 0)
		{
			recBuf[len] = '\0';
			std::cout << "������ ������:" << recBuf << std::endl;
		}
	}


}
void CServer_UDP::SendMsg(const char sendBuf[])
{
	int ret = sendto(m_sServer, sendBuf, strlen(sendBuf), 0, (sockaddr*)&m_SocAddrClient, sizeof(m_SocAddrClient));
	if (ret == -1)
	{
		std::cout << "�������� � �������" << std::endl;
		std::cout << GetLastError() << std::endl;
	}
}
void CServer_UDP::RecMsg()
{
	char recBuf[1025];
	while (!m_terminal)
	{
		try {
			Calculator calc;
			int slen = sizeof(m_SocAddrClient);
			int len = recvfrom(m_sServer, (char*)&calc, sizeof(calc), 0, (struct sockaddr*)&m_SocAddrClient, &slen);

			std::cout << calc.one << " + " << calc.two << " = " << calc.one + calc.two << std::endl;

		}
		catch (_exception)
		{
			int len = recvfrom(m_sServer, recBuf, 1025, 0, 0, 0);
			if (len > 0)
			{
				std::cout << recBuf << std::endl;
			}
		}
	}
}
CServer_UDP::~CServer_UDP()
{
	closesocket(m_sServer);
	WSACleanup();
}