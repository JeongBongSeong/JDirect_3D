#include<iostream>
#include<winsock2.h>
#include <conio.h>
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
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP
	int iRet = connect(
		sock,
		(sockaddr*)&sa,
		sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return 0;
	}
	std::cout << "접속성공!" << std::endl;

	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	char szBuffer[256] = { 0, };
	int iEnd = 0;
	while (1)
	{
		
		//std::cin >> szBuffer;	//남의 채팅을 볼 수 없음
		if (_kbhit() == 1)
		{
			int iValue = _getche();
			if (iValue == '\r' && strlen(szBuffer) == 0)
			{
				break;
			}
			if (iValue == '\r')		//enter
			{
				
				int iSendByte = send(sock,
					szBuffer,
					sizeof(szBuffer),
					0);

				if (iSendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
					{
						std::cout << "비정상 종료됨..." << std::endl;
						break;
					}
					//int iError = WSAGetLastError();
					//std::cout << "ErrorCode : " << iError << std::endl;
					//if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
					//{
					//	std::cout << "비정상 종료됨..." << std::endl;
					//	break;
					//}
				}
				iEnd = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else
			{
				szBuffer[iEnd++] = iValue;	//한 문자씩 보낸다. 엔터 전까지			
			}
		}
		else 
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
			
			if (iRecvByte == 0)
			{
				std::cout << "서버종료됨 .." << std::endl;
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
				{
					std::cout << "비정상 종료됨..." << std::endl;
					break;
				}
			}
			else
			{
				
				std::cout << "받음 : " << szRecvBuffer << std::endl;
				ZeroMemory(szRecvBuffer, sizeof(char) * 256);
			}
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}