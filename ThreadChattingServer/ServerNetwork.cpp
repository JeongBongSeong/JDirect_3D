#include "ServerNetwork.h"

//extern std::list<JNetUser> g_Userlist; 

int JServer::SendMsg(SOCKET sock, char* msg, WORD type)
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



DWORD WINAPI JServer::RecvThread(LPVOID param)
{
	if (m_Userlist.size() > 0)
	{
		std::list<JNetUser>::iterator iter;				//�ذ�å : ���� iter�� ���� �̸� �ְ� ���� ?
		for (iter = m_Userlist.begin(); iter != m_Userlist.end(); )
		{

			UPACKET recvPacket;
			int iRet = RecvMsg(recvPacket, iter);
			if (iRet == SOCKET_ERROR)
			{
				std::cout << "RecvMsg Error" << std::endl;
				continue;
			}
			else if (iRet == SOCKET_NOT_RECV)
			{
				iter++;				//Ŭ���̾�Ʈ ���� �� ���� : userlist���� �޾ƿ��� iter�� �����Ǿ� ����� �ٱ� �����̴�.
				continue;
			}


			JPacket data;
			data.m_uPacket = recvPacket;
			JChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			data >> recvdata.index >> recvdata.name
				>> recvdata.damage >> recvdata.msg;

			std::cout << "\n" <<
				"[" << recvdata.name << "]"
				<< recvdata.msg;
		}
	}

	
}

DWORD WINAPI JServer::SendThread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	while(1)//if (m_Userlist.size() > 0)
	{
		EnterCriticalSection(&this->m_CS);
		// send
		std::list<JNetUser>::iterator iter;
		for (iter = m_Userlist.begin();
			iter != m_Userlist.end();)
		{
			JNetUser sock = *iter;
			//int iSendMsgSize = SendMsg(sock.m_Sock, recvPacket.msg, PACKET_CHAT_MSG);
			int iRet = Broadcast(*iter);

			if (iRet <= 0)
			{
				iter = m_Userlist.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		LeaveCriticalSection(&this->m_CS);
	}
}

int JServer::RecvMsg(UPACKET& recvPacket ,std::list<JNetUser>::iterator iter)
{
	JNetUser user = *iter;
	char szRecvBuffer[256] = { 0, };

	
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
			iter = m_Userlist.erase(iter);
			std::cout << user.m_csName << " ���������." << std::endl;
			continue;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				iter = m_Userlist.erase(iter);
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
		/*if (iter != m_Userlist.end())
		{
			iter++;
		}*/
		return SOCKET_NOT_RECV;
	}
	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);

	iRecvSize = 0;

	//������ �ޱ�
	do {
		int iRecvByte = recv(user.m_Sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(user.m_Sock);
			iter = m_Userlist.erase(iter);
			std::cout << user.m_csName << " ���������." << std::endl;
			continue;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				iter = m_Userlist.erase(iter);
				std::cout << user.m_csName << " ������ ���������." << std::endl;
			}
			else
			{
				iter++;
			}
		}
	} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
	return true;
}

int JServer::Broadcast(JNetUser& user)
{
	if (user.m_packetPool.size() > 0)
	{
		std::list<JPacket>::iterator iter;
		for (iter = user.m_packetPool.begin(); iter != user.m_packetPool.end();)
		{
			for (JNetUser& senduser : m_Userlist)
			{
				int iRet = SendMsg(senduser.m_Sock, (*iter).m_uPacket);
				if (iRet <= 0)
				{
					senduser.m_bConnect = false;
				}
			}
			iter = user.m_packetPool.erase(iter);
		}
	}
	return 1;
}

int JServer::InitServer()
{
	
}

int JServer::Run()
{
	
	
	return true;
}
