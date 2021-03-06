#pragma once
#include "JNetUser.h"

class JNetwork
{
public:
	SOCKET  m_Sock;
	std::list<JNetUser> userlist;
	JNetUser   m_PlayerUser;
public:
	bool	InitNetwork();
	bool	CloseNetwork();	
	bool	InitServer(int protocol, int iport, const char* ip=nullptr);
public:
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int SendMsg(SOCKET sock, char* msg, int iSize, WORD type);
	int AddUser(SOCKET sock);
	int RecvUser(JNetUser& user);
};

