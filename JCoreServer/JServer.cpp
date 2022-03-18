#include "JServer.h"

int JServer::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	// 2번 패킷 전송
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
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//서버 소켓을 생성
	ZeroMemory(&sa, sizeof(SOCKADDR_IN));

	sa.sin_family = AF_INET;		//TCP
	sa.sin_port = htons(iPort);			//port 번호
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // 내 컴퓨터로 들어오는 IP다 받아(INADDR_ANY)  //inet_addr("192.168.0.12");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP

	int iRet = bind(m_ListenSock, (sockaddr*)&sa, sizeof(SOCKADDR_IN));	//소켓과 정보를 바인딩
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	iRet = listen(m_ListenSock, SOMAXCONN);		// 소켓을 가동한다.
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	//논블럭킹 선언  ( Listen 소켓)
	u_long on = 1;
	ioctlsocket(m_ListenSock, FIONBIO, &on);
	cout << "서버 가동중....." << endl;

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
