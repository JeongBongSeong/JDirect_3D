#include<iostream>
#include<winsock2.h>
#include <conio.h>
#pragma comment (lib, "ws2_32.lib")

int main()
{

	WSADATA wsa;
	//2,2 �������� ����.
	// wsa�� ��ȯ �޴´�.
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}
	SOCKET sock = socket(AF_INET,
		SOCK_STREAM,		// STREAM : TCP , DATAGRAM : UDP
		0);					// IPPROTO_TCP : 0, IPPROTO_UDP : 1 (�Ƹ�?)

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);			//port ��ȣ
	//sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.46");
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");	//���ڿ��� 4����Ʈ�� ��ȯ�ؼ� �����ϴ� ��	�� IP
	int iRet = connect(
		sock,
		(sockaddr*)&sa,
		sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return 0;
	}
	std::cout << "���Ӽ���!" << std::endl;

	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	char szBuffer[256] = { 0, };
	int iEnd = 0;
	while (1)
	{
		
		//std::cin >> szBuffer;	//���� ä���� �� �� ����
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
					if (WSAGetLastError() != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
					{
						std::cout << "������ �����..." << std::endl;
						break;
					}
					//int iError = WSAGetLastError();
					//std::cout << "ErrorCode : " << iError << std::endl;
					//if (iError != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
					//{
					//	std::cout << "������ �����..." << std::endl;
					//	break;
					//}
				}
				iEnd = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else
			{
				szBuffer[iEnd++] = iValue;	//�� ���ھ� ������. ���� ������			
			}
		}
		else 
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(sock, szRecvBuffer, 256, 0);
			
			if (iRecvByte == 0)
			{
				std::cout << "��������� .." << std::endl;
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
				{
					std::cout << "������ �����..." << std::endl;
					break;
				}
			}
			else
			{
				
				std::cout << "���� : " << szRecvBuffer << std::endl;
				ZeroMemory(szRecvBuffer, sizeof(char) * 256);
			}
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}