#include "JServer.h"

int JServer::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET packet;
	//ZeroMemory(&packet, sizeof(packet));
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	// 2번 패킷 전송
	// 운영체제에는 2가지 버퍼가 존재 
	// send 버퍼 (short 바이트) send 버퍼가 꽉차면 보낼 수 없다.
	// recv 버퍼 () 패킷이 꽉찼을 때 추가로 들어온 데이터는 버퍼에 저장이 안된다.
	// send는 보내는게아니고 운영체제에 sendbuffer의 저장하고 빠르게 운영체제가 보내는 것이다.
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


//
//DWORD WINAPI RecvThread(LPVOID param)
//{
//	if (m_Userlist.size() > 0)
//	{
//		list<JNetUser*>::iterator iter;				//해결책 : 다음 iter의 값을 미리 넣고 삭제 ?
//		for (iter = m_Userlist.begin(); iter != m_Userlist.end(); )
//		{
//
//			UPACKET recvPacket;
//			int iRet = RecvMsg(recvPacket, iter);
//			if (iRet == SOCKET_ERROR)
//			{
//				cout << "RecvMsg Error" << endl;
//				continue;
//			}
//			else if (iRet == SOCKET_NOT_RECV)
//			{
//				iter++;				//클라이언트 종료 시 에러 : userlist에서 받아오는 iter가 삭제되어 사이즈가 줄기 때문이다.
//				continue;
//			}
//
//
//			JPacket data;
//			data.m_uPacket = recvPacket;
//			JChatMsg recvdata;
//			ZeroMemory(&recvdata, sizeof(recvdata));
//			data >> recvdata.index >> recvdata.name
//				>> recvdata.damage >> recvdata.msg;
//
//			cout << "\n" <<
//				"[" << recvdata.name << "]"
//				<< recvdata.msg;
//		}
//	}
//
//	
//}
//
//DWORD WINAPI SendThread(LPVOID param)
//{
//	SOCKET sock = (SOCKET)param;
//	while(1)//if (m_Userlist.size() > 0)
//	{
//		EnterCriticalSection(&m_CS);
//		// send
//		list<JNetUser*>::iterator iter;
//		for (iter = m_Userlist.begin();
//			iter != m_Userlist.end();)
//		{
//			JNetUser* sock = *iter;
//			//int iSendMsgSize = SendMsg(sock.m_Sock, recvPacket.msg, PACKET_CHAT_MSG);
//			int iRet = Broadcast(*iter);
//
//			if (iRet <= 0)
//			{
//				iter = m_Userlist.erase(iter);
//			}
//			else
//			{
//				iter++;
//			}
//		}
//		LeaveCriticalSection(&m_CS);
//	}
//}

//int JServer::RecvMsg(UPACKET& recvPacket ,list<JNetUser*>::iterator iter)
//{
//	JNetUser* user = *iter;
//	char szRecvBuffer[256] = { 0, };
//
//	
//	ZeroMemory(&recvPacket, sizeof(recvPacket));
//	int iRecvSize = 0;
//
//	do {
//		//헤더의 사이즈만큼 가져온다.
//		int iRecvByte = recv(user->m_Sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
//		//헤더 받기
//		iRecvSize += iRecvByte;
//		if (iRecvByte == 0)
//		{
//			closesocket(user->m_Sock);
//			iter = m_Userlist.erase(iter);
//			cout << user->m_csName << " 접속종료됨." << endl;
//			continue;
//		}
//		if (iRecvByte == SOCKET_ERROR)
//		{
//			int iError = WSAGetLastError();
//			if (iError != WSAEWOULDBLOCK)
//			{
//				iter = m_Userlist.erase(iter);
//				cout << user->m_csName << " 비정상 접속종료됨." << endl;
//				break;
//			}
//			else
//			{
//				break;
//			}
//		}
//	} while (iRecvSize < PACKET_HEADER_SIZE);
//
//	if (iRecvSize == SOCKET_ERROR)
//	{
//		/*if (iter != m_Userlist.end())
//		{
//			iter++;
//		}*/
//		return SOCKET_NOT_RECV;
//	}
//	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
//
//	iRecvSize = 0;
//
//	//데이터 받기
//	do {
//		int iRecvByte = recv(user->m_Sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
//		iRecvSize += iRecvByte;
//		if (iRecvByte == 0)
//		{
//			closesocket(user->m_Sock);
//			iter = m_Userlist.erase(iter);
//			cout << user->m_csName << " 접속종료됨." << endl;
//			continue;
//		}
//		if (iRecvByte == SOCKET_ERROR)
//		{
//			int iError = WSAGetLastError();
//			if (iError != WSAEWOULDBLOCK)
//			{
//				iter = m_Userlist.erase(iter);
//				cout << user->m_csName << " 비정상 접속종료됨." << endl;
//			}
//			else
//			{
//				iter++;
//			}
//		}
//	} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
//	return true;
//}

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
