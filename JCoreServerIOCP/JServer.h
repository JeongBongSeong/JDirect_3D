#pragma once
#include"JNetUser.h"



class JServer : public JServerObj
{
public:
	
	list<JNetUser*>	m_Userlist;
	SOCKET					m_ListenSock;
	//CRITICAL_SECTION	m_CS;

public:
	//int RecvMsg(UPACKET& recvPacket, list<JNetUser*>::iterator iter);
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int Broadcast(JNetUser* user);
	virtual bool AddUser(SOCKET sock, SOCKADDR_IN clientAddr);
public:
	virtual bool InitServer(int iPort);
	virtual bool Run();
	virtual bool Release();
	
};

