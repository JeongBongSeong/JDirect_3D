#pragma once
#include"JThread.h"
#include"JNetUser.h"

class JNetWork : public JThread
{
public:
	SOCKET m_ListenSock;
	std::map<int,JNetUser*> m_UserList;
public:
	JNetWork();
	virtual ~JNetWork();
public:
	int Create(int iPort);
	void AddUser(SOCKET sock, SOCKADDR_IN addr);
	virtual bool Run() override;

};

