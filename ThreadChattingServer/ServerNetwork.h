#pragma once
#include"JNetUser.h"

#define SOCKET_NOT_RECV 0
#define WSA_ERROR -1
#define SOCKET_RECV_ERROR -3

class JServer
{
public:
	
	std::list<JNetUser> m_Userlist;


	CRITICAL_SECTION	m_CS;
	
	

	

public:
	DWORD WINAPI RecvThread(LPVOID param);
	DWORD WINAPI SendThread(LPVOID param);
	int RecvMsg(UPACKET& recvPacket, std::list<JNetUser>::iterator iter);
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int Broadcast(JNetUser& user);

public:
	int InitServer();
	int Run();
};

