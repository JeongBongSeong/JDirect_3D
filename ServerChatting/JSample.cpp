#include<iostream>
#include<winsock2.h>
#include<list>
#include<string>
#pragma comment (lib, "ws2_32.lib")


struct JNetUser
{
	SOCKET		m_Sock;
	SOCKADDR_IN	m_Addr;
	std::string	m_csName;
	short		m_iPort;
	void set(SOCKET sock,SOCKADDR_IN sockaddr)//,std::string,short)
	{
		m_Sock = sock;
		m_Addr = sockaddr;
		m_csName = inet_ntoa(m_Addr.sin_addr);
		m_iPort = ntohs(m_Addr.sin_port);
	}
};

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
				int iRecvByte = recv(user.m_Sock, szRecvBuffer, 256, 0);
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
				else
				{
					std::list<JNetUser>::iterator iterSend;
					for (iterSend = userlist.begin();
						iterSend != userlist.end();)
					{
						JNetUser sock = *iterSend;
						if (sock.m_Sock == user.m_Sock)
						{
							std::cout << "같은 소켓 패스" << std::endl;
							iterSend++;
							continue;
						}
						std::cout << szRecvBuffer << "받음" << std::endl;
						int iSendByte = send(sock.m_Sock, szRecvBuffer, iRecvByte, 0);
						std::cout << sock.m_Sock << " : " << iSendByte << " 보냄." << std::endl;
						if (iSendByte == SOCKET_ERROR)
						{
							int iError = WSAGetLastError();
							if (iError != WSAEWOULDBLOCK)
							{
								closesocket(user.m_Sock);
								iterSend = userlist.erase(iterSend);
								std::cout << user.m_csName << " 비정상 접속종료됨." << std::endl;
							}
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
	}
	closesocket(ListenSock);
	WSACleanup();
	return 0;

}