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
	SOCKET sock = socket(AF_INET,
		SOCK_STREAM,		// STREAM : TCP , DATAGRAM : UDP
		0);					// IPPROTO_TCP : 0, IPPROTO_UDP : 1 (아마?)

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);			//port 번호
	//sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.46");
	sa.sin_addr.s_addr = inet_addr("192.168.0.46");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP
	int iRet = connect(
		sock,
		(sockaddr*)&sa,
		sizeof(sa));
	int iSendCount = 3;
	while (iSendCount-- > 0)
	{
		char szBuffer[] = "안녕하세용~\n";
		send(sock,
			szBuffer,
			sizeof(szBuffer),
			0);
		char szRecvBuffer[256] = { 0, };
		int iRecvByte = recv(sock, szRecvBuffer, sizeof(szRecvBuffer), 0);
		std::cout << szRecvBuffer;
		if (iRecvByte == SOCKET_ERROR)
		{
			std::cout << "서버 종료됨.." << std::endl;
		}
		Sleep(1000);
	}
	closesocket(sock);
	WSACleanup();
	return 0;

}