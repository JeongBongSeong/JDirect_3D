#include "JNetWork.h"

JNetWork::JNetWork()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}

JNetWork::~JNetWork()
{
    WSACleanup();
}

int JNetWork::Create(int iPort)
{
    
    m_ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(iPort);
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

bool JNetWork::Run()
{
    SOCKADDR_IN saClientAddr;
    int iLen = sizeof(saClientAddr);
    while (1)
    {
        SOCKET clientSock = accept(m_ListenSock, (sockaddr*)&saClientAddr, &iLen);	// accept를 이용하여 들어온 소켓을 확인한다. 위에서 논블록킹으로 설정했기에 값을 받아 바로넘어감 블록킹의 경우 대기한다.

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
    }
    return true;
}


void JNetWork::AddUser(SOCKET sock,SOCKADDR_IN addr)
{
    m_UserList.insert(std::make_pair(sock, new JNetUser(sock, addr)));
}