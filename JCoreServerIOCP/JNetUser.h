#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "JServerObj.h"
#include "JPacket.h"
struct JOV
{
	OVERLAPPED ov;
	int type;
};
class JNetUser : public JServerObj
{
public:
	bool		m_bConnect;
	SOCKET		m_Sock;
	SOCKADDR_IN	m_Addr;
	string	m_csName;
	short		m_iPort;

	//
	JOV m_ovRecv;
	JOV m_ovSend;
	WSABUF m_wsaRecvBuffer;
	WSABUF m_wsaSendBuffer;
	char m_szRecv[256];
	char m_szSend[256];

	//buffer
	char m_szRecvBuffer[2048];


	int m_iPacketPos;
	int m_iWritePos;
	int m_iReadPos;

	list<JPacket> m_packetPool;

	//
	int Recv();
	//

	void set(SOCKET sock, SOCKADDR_IN sockaddr);
	bool DisConnect();
public:
	int Dispatch(DWORD dwTrans, JOV* tov);
	int DispatchRecv(char* szRecvBuffer, int iRecvByte);
	int DispatchSend(DWORD dwTrans);
public:
	JNetUser();
	virtual ~JNetUser();
};