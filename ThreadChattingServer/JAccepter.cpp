#include "JAccepter.h"

JAccepter::JAccepter(SOCKADDR_IN& sa)
{
	m_Sa = sa;
}

int JAccepter::Join()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0)
	{
		return WSA_ERROR;
	}
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//서버 소켓을 생성
	ZeroMemory(&m_Sa, sizeof(SOCKADDR_IN));

	m_Sa.sin_family = AF_INET;		//TCP
	m_Sa.sin_port = htons(m_iPort);			//port 번호
	m_Sa.sin_addr.s_addr = htonl(INADDR_ANY); // 내 컴퓨터로 들어오는 IP다 받아(INADDR_ANY)  //inet_addr("192.168.0.12");	//문자열을 4바이트로 변환해서 저장하는 것	들어갈 IP

	int iRet = bind(m_ListenSock, (sockaddr*)&m_Sa, sizeof(SOCKADDR_IN));	//소켓과 정보를 바인딩
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	iRet = listen(m_ListenSock, SOMAXCONN);		// 소켓을 가동한다.
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;
	
	m_iLen = sizeof(m_ClientAddr);

	//논블럭킹 선언  ( Listen 소켓)
	u_long on = 1;
	ioctlsocket(m_ListenSock, FIONBIO, &on);
	return true;
}

int JAccepter::Run()
{
	m_ClientSock = accept(m_ListenSock, (sockaddr*)&m_ClientAddr, &m_iLen);	// accept를 이용하여 들어온 소켓을 확인한다. 위에서 논블록킹으로 설정했기에 값을 받아 바로넘어감 블록킹의 경우 대기한다.

	if (m_ClientSock == SOCKET_ERROR)	//서버 에러일 경우 (-1)
	{
		int iError = WSAGetLastError();
		//std::cout << "ErrorCode : " << iError << std::endl;
		//아래 WSA E WOULD BLOCK 은 연결 요청을 받지 않을 경우 나오는 에러 
		if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
		{
			std::cout << "ErrorCode=" << iError << std::endl;
			return false;
		}

	}
	else
	{
		JNetUser user;
		user.set(m_ClientSock, m_ClientAddr);
		m_Userlist.push_back(user);

		std::cout <<
			"ip = " << inet_ntoa(m_ClientAddr.sin_addr) << std::endl <<
			"port = " << ntohs(m_ClientAddr.sin_port) << std::endl <<
			" " << std::endl;

		//논블럭킹 선언  ( Client 소켓 )
		u_long on = 1;
		ioctlsocket(m_ClientSock, FIONBIO, &on);

		std::cout << m_Userlist.size() << " 명 접속중.." << std::endl;

	}
}