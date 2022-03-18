#pragma once
#include"ServerNetwork.h"



int main()
{
	JServer Server;
	
						//���� ������ ������ ���� ����
	SOCKADDR_IN sa;
	int iRet = Server.InitServer(sa);
	if (iRet == SOCKET_ERROR)
	{
		std::cout << "Init Error" << std::endl;
		return 0;
	}
	else if (iRet == (WSA_ERROR))
	{
		std::cout << "WSA_ERROR" << std::endl;
		return 0;
	}

	

	std::cout << "���� ������....." << std::endl;
		
	//
	while (1)
	{
		iRet = Server.MainThread();
		if (iRet == SOCKET_ERROR)
		{
			std::cout << "MainThread Error" << std::endl;
			break;
		}
		else if (iRet == SOCKET_RECV_ERROR)
		{
			std::cout << "SOCKET_RECV_ERROR" << std::endl;
			
		}
		
	}
	closesocket(Server.m_ListenSock);
	WSACleanup();
	return 0;

}