#pragma once
#include"JServer.h"
#include "JChatUser.h"
class JLobbyServer : public JServer
{
public:
	
	HANDLE m_hWorkThread[MAX_WORKER_THREAD];
	HANDLE m_hIOCP;

public:
	JLobbyServer();
	~JLobbyServer();
public:
	virtual bool InitServer(int iPort);
	virtual bool Run();
	virtual bool Release();
	virtual bool AddUser(SOCKET socr, SOCKADDR_IN clientAddr);

};

