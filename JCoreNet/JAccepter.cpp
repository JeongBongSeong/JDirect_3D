#include "JAccepter.h"
#include "JServer.h"

JAccepter::JAccepter()
{
}

JAccepter::JAccepter(LPVOID value) 
	:JThread(value)
{
//	m_pObject = value;
}

bool JAccepter::Run()
{
	JServer* pServer = (JServer*)m_pObject;			//로비서버로 오버라이딩
	SOCKET sock = pServer->m_ListenSock;
	SOCKADDR_IN			saClientAddr;
	int iLen = sizeof(saClientAddr);
	while (1)
	{
		SOCKET clientSock = accept(sock, (sockaddr*)&saClientAddr, &iLen);	// accept를 이용하여 들어온 소켓을 확인한다. 위에서 논블록킹으로 설정했기에 값을 받아 바로넘어감 블록킹의 경우 대기한다.

		if (clientSock == SOCKET_ERROR)	//서버 에러일 경우 (-1)
		{
			int iError = WSAGetLastError();
			//cout << "ErrorCode : " << iError << endl;
			//아래 WSA E WOULD BLOCK 은 연결 요청을 받지 않을 경우 나오는 에러 
			if (iError != WSAEWOULDBLOCK)	//직전 에러 (리시브 함수의 에러일 것)	WSA E WOULD BLOCK // 이 에러가 뜨면 정상 // 아니면 오류인 것
			{
				cout << "ErrorCode=" << iError << endl;
				break;
			}

		}
		else
		{
			pServer->AddUser(clientSock, saClientAddr);
			cout << pServer->m_Userlist.size() << " 명 접속중.." << endl;
		}
		Sleep(1);
	}
	return 1;
}