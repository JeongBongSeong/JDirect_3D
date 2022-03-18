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
	JServer* pServer = (JServer*)m_pObject;
	SOCKET sock = pServer->m_ListenSock;
	SOCKADDR_IN			saClientAddr;
	int iLen = sizeof(saClientAddr);
	while (1)
	{
		SOCKET clientSock = accept(sock, (sockaddr*)&saClientAddr, &iLen);	// accept�� �̿��Ͽ� ���� ������ Ȯ���Ѵ�. ������ ����ŷ���� �����߱⿡ ���� �޾� �ٷγѾ ���ŷ�� ��� ����Ѵ�.

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
		else
		{
			pServer->AddUser(clientSock, saClientAddr);
			cout << pServer->m_Userlist.size() << " �� ������.." << endl;
		}
		Sleep(1);
	}
	return 1;
}