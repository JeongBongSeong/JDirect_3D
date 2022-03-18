#pragma once
#include"ServerNetwork.h"
class JAccepter : public JServer
{
public:
	WSADATA				m_Wsa;			//2,2 버전으로 들어간다.	// wsa로 반환 받는다.
	SOCKADDR_IN m_Sa;
	SOCKET				m_ListenSock;
	SOCKET				m_ClientSock;
	SOCKADDR_IN			m_ClientAddr;
	int					m_iLen;
	int					m_iPort = 10000;	//port 번호
public:
	JAccepter(SOCKADDR_IN& sa);
	
	int Run();

};

