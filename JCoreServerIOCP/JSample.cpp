#pragma once
#include"JLobbyServer.h"
#include "JAccepter.h"
int main()
{
	JLobbyServer server;
	//JServer server;
	
						//���� ������ ������ ���� ����
	//int iRet = 
	server.InitServer(10000);
	//if (iRet == SOCKET_ERROR)
	//{
	//	cout << "Init Error" << endl;
	//	return 0;
	//}
	//else if (iRet == (WSA_ERROR))
	//{
	//	cout << "WSA_ERROR" << endl;
	//	return 0;
	//}

	JAccepter accept(&server);
	accept.Detach();
	server.Run();
	server.Release();
	

	return 0;

}