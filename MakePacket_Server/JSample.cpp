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

	// 2번 패킷 전송
	// 운영체제에는 2가지 버퍼가 존재 
	// send 버퍼 (short 바이트) send 버퍼가 꽉차면 보낼 수 없다.
	// recv 버퍼 () 패킷이 꽉찼을 때 추가로 들어온 데이터는 버퍼에 저장이 안된다.
	// send는 보내는게아니고 운영체제에 sendbuffer의 저장하고 빠르게 운영체제가 보내는 것이다.
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
	//2,2 버전으로 들어간다.
	// wsa로 반환 받는다.
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//서버 소켓을 생성

	SOCKADDR_IN sa;					//값을 정보를 저장할 변수 선언
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;		//TCP
	sa.sin_port = htons(10000);			//port 번호
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // 내 컴퓨터로 들어오는 IP다 받아(INADDR_ANY)  //inet_addr("192.168.0.12");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(SOCKADDR_IN));	//소켓과 정보를 바인딩
	if (iRet == SOCKET_ERROR) return 0;

	iRet = listen(ListenSock, SOMAXCONN);		// 소켓을 가동한다.
	if (iRet == SOCKET_ERROR) return 0;

	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);

	std::cout << "서버 가동중....." << std::endl;

	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);

	std::list<JNetUser> userlist;
	//
	while (1)
	{

		SOCKET clientSock = accept(ListenSock, (sockaddr*)&clientAddr, &iLen);	// accept를 이용하여 들어온 소켓을 확인한다. 위에서 논블록킹으로 설정했기에 값을 받아 바로넘어감 블록킹의 경우 대기한다.

		if (clientSock == SOCKET_ERROR)	//서버 에러일 경우 (-1)
		{
			int iError = WSAGetLastError();
			//std::cout << "ErrorCode : " << iError << std::endl;
			//아래 WSA E WOULD BLOCK 은 연결 요청을 받지 않을 경우 나오는 에러 
			if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
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
			std::cout << userlist.size() << " 명 접속중.." << std::endl;

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
					//헤더의 사이즈만큼 가져온다.
					int iRecvByte = recv(user.m_Sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
					//헤더 받기
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = userlist.erase(iter);
						std::cout << user.m_csName << " 접속종료됨." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							iter = userlist.erase(iter);
							std::cout << user.m_csName << " 비정상 접속종료됨." << std::endl;
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
				//데이터 받기
				do {
					int iRecvByte = recv(user.m_Sock, recvPacket.msg, recvPacket.ph.len - iRecvSize, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = userlist.erase(iter);
						std::cout << user.m_csName << " 접속종료됨." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							iter = userlist.erase(iter);
							std::cout << user.m_csName << " 비정상 접속종료됨." << std::endl;
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
						std::cout << sock.m_csName << " 비정상 접속종료됨." << std::endl;
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