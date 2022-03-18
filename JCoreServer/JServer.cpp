#include "JServer.h"

int JServer::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	// 2�� ��Ŷ ����
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
int JServer::SendMsg(SOCKET sock, UPACKET& packet)
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


int JServer::Broadcast(JNetUser* user)
{
	if (user->m_packetPool.size() > 0)
	{
		list<JPacket>::iterator iter;
		for (iter = user->m_packetPool.begin(); iter != user->m_packetPool.end();)
		{
			for (JNetUser* senduser : m_Userlist)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet <= 0)
				{
					senduser->m_bConnect = false;
				}
			}
			iter = user->m_packetPool.erase(iter);
		}
	}
	return 1;
}

bool JServer::InitServer(int iPort)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return WSA_ERROR;
	}
	SOCKADDR_IN sa;
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//���� ������ ����
	ZeroMemory(&sa, sizeof(SOCKADDR_IN));

	sa.sin_family = AF_INET;		//TCP
	sa.sin_port = htons(iPort);			//port ��ȣ
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // �� ��ǻ�ͷ� ������ IP�� �޾�(INADDR_ANY)  //inet_addr("192.168.0.12");	//���ڿ��� 4����Ʈ�� ��ȯ�ؼ� �����ϴ� ��	�� IP

	int iRet = bind(m_ListenSock, (sockaddr*)&sa, sizeof(SOCKADDR_IN));	//���ϰ� ������ ���ε�
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	iRet = listen(m_ListenSock, SOMAXCONN);		// ������ �����Ѵ�.
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	//���ŷ ����  ( Listen ����)
	u_long on = 1;
	ioctlsocket(m_ListenSock, FIONBIO, &on);
	cout << "���� ������....." << endl;

	return true;
}

bool JServer::Run()
{

	return true;
}

bool JServer::Release()
{
	closesocket(m_ListenSock);
	WSACleanup();
	return true;
}

bool JServer::AddUser(SOCKET sock, SOCKADDR_IN clientAddr)
{
	return true;
}
