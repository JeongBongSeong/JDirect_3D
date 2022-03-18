#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#include<list>
#include<string>

#include"JPacket.h"
#pragma comment (lib, "ws2_32.lib")


struct JNetUser
{
	SOCKET		m_Sock;
	SOCKADDR_IN	m_Addr;
	std::string	m_csName;
	short		m_iPort;
	void set(SOCKET sock, SOCKADDR_IN sockaddr)//,std::string,short)
	{
		m_Sock = sock;
		m_Addr = sockaddr;
		m_csName = inet_ntoa(m_Addr.sin_addr);
		m_iPort = ntohs(m_Addr.sin_port);
	}
};


int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET packet;
	//ZeroMemory(&packet, sizeof(packet));
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	// 2�� ��Ŷ ����
	// �ü������ 2���� ���۰� ���� 
	// send ���� (short ����Ʈ) send ���۰� ������ ���� �� ����.
	// recv ���� () ��Ŷ�� ��á�� �� �߰��� ���� �����ʹ� ���ۿ� ������ �ȵȴ�.
	// send�� �����°Ծƴϰ� �ü���� sendbuffer�� �����ϰ� ������ �ü���� ������ ���̴�.
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len- iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int SendMsg(SOCKET sock, UPACKET& packet)
{
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}

int main()
{
	WSADATA wsa;
	//2,2 �������� ����.
	// wsa�� ��ȯ �޴´�.
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//���� ������ ����

	SOCKADDR_IN sa;					//���� ������ ������ ���� ����
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;		//TCP
	sa.sin_port = htons(10000);			//port ��ȣ
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // �� ��ǻ�ͷ� ������ IP�� �޾�(INADDR_ANY)  //inet_addr("192.168.0.12");	//���ڿ��� 4����Ʈ�� ��ȯ�ؼ� �����ϴ� ��	�� IP
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(SOCKADDR_IN));	//���ϰ� ������ ���ε�
	if (iRet == SOCKET_ERROR) return 0;

	iRet = listen(ListenSock, SOMAXCONN);		// ������ �����Ѵ�.
	if (iRet == SOCKET_ERROR) return 0;

	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);

	std::cout << "���� ������....." << std::endl;

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);

	std::list<JNetUser> userlist;
	//
	while (1)
	{

		SOCKET clientSock = accept(ListenSock, (sockaddr*)&clientAddr, &iLen);	// accept�� �̿��Ͽ� ���� ������ Ȯ���Ѵ�. ������ ����ŷ���� �����߱⿡ ���� �޾� �ٷγѾ ���ŷ�� ��� ����Ѵ�.

		if (clientSock == SOCKET_ERROR)	//���� ������ ��� (-1)
		{
			int iError = WSAGetLastError();
			//std::cout << "ErrorCode : " << iError << std::endl;
			//�Ʒ� WSA E WOULD BLOCK �� ���� ��û�� ���� ���� ��� ������ ���� 
			if (iError != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
			{
				std::cout << "ErrorCode=" << iError << std::endl;
				break;
			}

		}
		else
		{
			JNetUser	user;
			user.set(clientSock, clientAddr);
			userlist.push_back(user);


			std::cout <<
				"ip = " << inet_ntoa(clientAddr.sin_addr) << std::endl <<
				"port = " << ntohs(clientAddr.sin_port) << std::endl <<
				" " << std::endl;

			u_long on = 1;
			ioctlsocket(clientSock, FIONBIO, &on);
			std::cout << userlist.size() << " �� ������.." << std::endl;

		}
		if (userlist.size() > 0)
		{
			std::list<JNetUser>::iterator iter;
			for (iter = userlist.begin(); iter != userlist.end();)
			{
				JNetUser user = *iter;
				char szRecvBuffer[256] = { 0, };

				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int iRecvSize = 0;

				do {
					//����� �����ŭ �����´�.
					int iRecvByte = recv(user.m_Sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
					//��� �ޱ�
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = userlist.erase(iter);
						std::cout << user.m_csName << " ���������." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							iter = userlist.erase(iter);
							std::cout << user.m_csName << " ������ ���������." << std::endl;
							break;
						}
						else
						{
							break;
						}
					}
				} while (iRecvSize < PACKET_HEADER_SIZE);

				if (iRecvSize == SOCKET_ERROR)
				{
					if (iter != userlist.end())
					{
						iter++;
					}
					continue;
				}
				memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
				
				iRecvSize = 0;
				//������ �ޱ�
				do {
					int iRecvByte = recv(user.m_Sock, recvPacket.msg, recvPacket.ph.len - iRecvSize, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = userlist.erase(iter);
						std::cout << user.m_csName << " ���������." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							iter = userlist.erase(iter);
							std::cout << user.m_csName << " ������ ���������." << std::endl;
						}
						else
						{
							iter++;
						}
					}
				} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
				
				
				JPacket data;
				data.m_uPacket = recvPacket;
				JChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				data >> recvdata.index >> recvdata.name
				>> recvdata.damage >> recvdata.msg;

				std::cout << "\n" <<
				"[" << recvdata.name << "]"
				<< recvdata.msg;



				std::list<JNetUser>::iterator iterSend;
				for (iterSend = userlist.begin();
					iterSend != userlist.end();)
				{
					JNetUser sock = *iterSend;					
					int iSendMsgSize = SendMsg(sock.m_Sock, recvPacket);
					
					if (iSendMsgSize < 0)
					{
						closesocket(sock.m_Sock);
						iterSend = userlist.erase(iterSend);
						std::cout << sock.m_csName << " ������ ���������." << std::endl;
					}
					else
					{
						iterSend++;
					}
				}
				if (iter != userlist.end())
				{
					iter++;
				}

			}
		}
	}
	closesocket(ListenSock);
	WSACleanup();
	return 0;

}