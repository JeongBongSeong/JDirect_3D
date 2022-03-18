#pragma once
#include "ServerNetwork.h"
#define MAX_WORKER_THREAD 3
class JLobbyServer : public JServer
{

public:
	HANDLE m_hWorkThread[MAX_WORKER_THREAD];
	HANDLE m_hIOCP;
	HANDLE m_hKillEvent;
	//HANDLE

public:
	JLobbyServer();
	~JLobbyServer();
public:
	bool WorkerThread();
	bool InitServer(int iPort);
	bool Release();

};

