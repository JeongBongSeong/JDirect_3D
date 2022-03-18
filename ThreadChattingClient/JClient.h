#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include "JPacket.h"
#include<string>
#pragma comment	(lib, "ws2_32.lib")

class JClient
{
public:
	SOCKET m_Sock;
	HANDLE m_hSendThread;
	HANDLE m_hRecvThread;
	DWORD m_hSendThreadID;
	DWORD m_hRecvThreadID;


public:
	JClient() {};
	~JClient();
	void InitClient();
	void Run();
	void Release();
};

