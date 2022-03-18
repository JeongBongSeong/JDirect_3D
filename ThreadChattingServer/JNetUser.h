#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#include<list>
#include<string>
#include"JPacket.h"
#pragma comment (lib, "ws2_32.lib")

struct TOV
{
	OVERLAPPED ov;
	int type;
};
class JNetUser
{
public:
	bool		m_bConnect;
	SOCKET		m_Sock;
	SOCKADDR_IN	m_Addr;
	std::string	m_csName;
	short		m_iPort;

	//
	TOV m_ovRecv;
	TOV m_ovSend;
	WSABUF m_wsaRecvBuffer;
	WSABUF m_wsaSendBuffer;
	char m_szRecv[256];
	char m_szSend[256];

	//buffer
	char m_szRecvBuffer[2048];


	int m_iPacketPos;
	int m_iWritePos;
	int m_iReadPos;
	std::list<JPacket> m_packetPool;
	//
	int Recv();
	//

	void set(SOCKET sock, SOCKADDR_IN sockaddr);//,std::string,short)
	int DispatchRead(char* szRecvBuffer, int iRecvByte);
};