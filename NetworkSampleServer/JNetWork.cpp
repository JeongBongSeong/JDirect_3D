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

bool JNetWork::Run()
{
    SOCKADDR_IN saClientAddr;
    int iLen = sizeof(saClientAddr);
    while (1)
    {
        SOCKET clientSock = accept(m_ListenSock, (sockaddr*)&saClientAddr, &iLen);	// accept�� �̿��Ͽ� ���� ������ Ȯ���Ѵ�. ������ ����ŷ���� �����߱⿡ ���� �޾� �ٷγѾ ���ŷ�� ��� ����Ѵ�.

        if (clientSock == SOCKET_ERROR)	//���� ������ ��� (-1)
        {
            int iError = WSAGetLastError();
            //cout << "ErrorCode : " << iError << endl;
            //�Ʒ� WSA E WOULD BLOCK �� ���� ��û�� ���� ���� ��� ������ ���� 
            if (iError != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
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