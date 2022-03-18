#include<iostream>
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")

int main()
{

	WSADATA wsa;
	//2,2 버전으로 들어간다.
	// wsa로 반환 받는다.
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);			//port 번호
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // 내 컴퓨터로 들어오는 IP다 받아(INADDR_ANY)  //inet_addr("192.168.0.12");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(SOCKADDR_IN));
	if (iRet == SOCKET_ERROR) return 0;

	iRet = listen(ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return 0;

	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);

	while (1)
	{
		
		SOCKET clientSock = accept(ListenSock, (sockaddr*)&clientAddr, &iLen);

		//if (clientSock == SOCKET_ERROR)
		//{
		//	int iError = WSAGetLastError();
		//	std::cout << "ErrorCode : " << iError << std::endl;
		//	if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
		//	{
		//		break;
		//	}
		//	continue;
		//}

		std::cout <<
			"ip = " << inet_ntoa(clientAddr.sin_addr) << std::endl <<
			"port = " << ntohs(clientAddr.sin_port) << std::endl <<
			"" << std::endl;
		u_long on = 1;
		ioctlsocket(clientSock, FIONBIO, &on);
		while (1)
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(clientSock, szRecvBuffer, sizeof(szRecvBuffer), 0);
			if (iRecvByte == 0)
			{
				std::cout <<
					"ip = " << inet_ntoa(clientAddr.sin_addr) << std::endl <<
					"port = " << ntohs(clientAddr.sin_port) << std::endl <<
					"==>logout" << std::endl;
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				int iError = WSAGetLastError();
				std::cout << "ErrorCode : " << iError << std::endl;
				if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
				{
					break;
				}
			}
			std::cout << szRecvBuffer << " : 받음" << std::endl;
			int iSendByte = send(clientSock, szRecvBuffer, sizeof(szRecvBuffer), 0);
			std::cout << iSendByte << " : 보냄" << std::endl;
		}
		closesocket(clientSock);
	}
	


	/*int iRet = connect(
		sock,
		(sockaddr*)&sa,
		sizeof(sa));
	char szBuffer[] = "안녕하세용~\n";
	send(sock,
		szBuffer,
		sizeof(szBuffer),
		0);
	char szRecvBuffer[256] = { 0, };
	int iRecvByte = recv(sock, szRecvBuffer, sizeof(szRecvBuffer), 0);
	std::cout << szRecvBuffer;*/

	WSACleanup();
	return 0;

}